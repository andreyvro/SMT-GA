#include "Aux.h"

const double Aux::ang120 = 2.0944;   // Valor de 120º em radianos

Aux::Aux() {}

double Aux::doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}

void Aux::setTitulo() {
    /*cout << "\033[1m\033[32m"; // Verde
    cout << "    ___                                     __   " << endl;
    cout << "   /   |  ______   ______ ________     ____/ /__ " << endl;
    cout << "  / /| | / ___/ | / / __\\/ ___/ _ \\   / __  / _ \\" << endl;
    cout << " / ___ |/ /   | |/ / /_// /  /  __/  / /_/ /  __/" << endl;
    cout << "/_/  |_/_/    |___/\\___/_/   \\___/   \\__,_/\\___/ " << endl;
    cout << "                                                  " << endl;
    cout << "   _____ __       _                " << endl;
    cout << "  / ___// /____  (_)___  ___  _____" << endl;
    cout << "  \\__ \\/ __/ _ \\/ / __ \\/ _ \\/ ___/" << endl;
    cout << " ___/ / /_/  __/ / / / /  __/ /    " << endl;
    cout << "/____/\\__/\\___/_/_/ /_/\\___/_/     " << endl << endl;
    cout << "  Algoritmo Genético - Andrey de Oliveira - 2018" << endl << endl;
    cout << "==================================================" << endl;
    cout << "\033[0m";  // Reseta Cor*/
    cout << "\033[1m\033[32m" << "Árvore de Steiner" << endl << "\033[0m";
}

void Aux::setModoUso() {
    cout << "Modo de Usar: " << endl << "./GA_SMT_CORE arqGrafo qtdInd indCruz indMut qtdIter fitness arqSaida sementeRnd" << endl << endl;

    cout << "Entrada:" << endl;
    cout << "\tarqGrafo   (str)  = Endereço do arquivo de grafo a ser processado." << endl;

    cout << "Arvore mínima de Steiner:" << endl;
    cout << "\tqtdInd  (int)  = Quantidade de indivíduos." << endl;
    cout << "\tindCruz (real) = Percentual de cruzamento." << endl;
    cout << "\tindMut  (real) = Percentual de mutação." << endl;
    cout << "\tqtdIter (int)  = Quantidade de gerações." << endl;
    cout << "\tfitness (real)  = Fitness a ser atingido." << endl;

    cout << "Opcional:" << endl;
    cout << "\tarqSaida  (str)  = Arquivo de saída da arvore mínima de steiner." << endl;
    cout << "\tsementeRnd  (int)  = Semente para gerador de números aleatórios." << endl;
    cout << "\t                     Se omitido adotará valor padrão (time(0))." << endl;
}

void Aux::setArqSaida(string arquivo, string texto) {
    ofstream meuArq (arquivo.c_str());
    if (meuArq.is_open()) {
        meuArq << texto;
        meuArq.close();
    } else {
        cout << "Não foi possível abrir o arquivo de saída!" << endl;
		cout << "Arquivo: " << arquivo << endl;
    }
}

double Aux::getDistancia(const double &x1, const double &y1, const double &x2, const double &y2) {
    double x = x1 - x2;
    double y = y1 - y2;
    return sqrt((x * x) + (y * y));
}

double Aux::getAngulo(const double &x1, const double &y1,
                     const double &x2, const double &y2,
                     const double &x3, const double &y3) {
    double ladoA = getDistancia(x1, y1, x2, y2);    // aresta adjacente a v1
    double ladoB = getDistancia(x1, y1, x3, y3);    // aresta adjacente a v1
    double ladoC = getDistancia(x2, y2, x3, y3);    // aresta oposta a v1
    return acos(((ladoA * ladoA) + (ladoB * ladoB) - (ladoC * ladoC)) / (2 * ladoA * ladoB));    // Ângulo em radianos
}

void Aux::getPtTorricelli(const double &x1, const double &y1,
                          const double &x2, const double &y2,
                          const double &x3, const double &y3,
                          double &retX, double &retY) {
    if (getAngulo(x1, y1, x2, y2, x3, y3) >= ang120) {
        retX = x1;
        retY = y1;
    } else if (getAngulo(x2, y2, x1, y1, x3, y3) >= ang120) {
        retX = x2;
        retY = y2;
    } else if (getAngulo(x3, y3, x1, y1, x2, y2) >= ang120) {
        retX = x3;
        retY = y3;
    } else {
        double oetx1, oety1, oetx2, oety2;
        oetx1 = oety1 = oetx2, oety2 = 0.0;
        if (orientacao(x1, y1, x2, y2, x3, y3) == -1) { // Lado direito
            criarTrianguloEquilatero(x1, y1, x2, y2, oetx1, oety1);
            criarTrianguloEquilatero(x2, y2, x3, y3, oetx2, oety2);
        } else {
            criarTrianguloEquilatero(x2, y2, x1, y1, oetx1, oety1);
            criarTrianguloEquilatero(x3, y3, x2, y2, oetx2, oety2);
        }
        pontoDeInterseccao(oetx1,oety1,x3,y3,oetx2,oety2,x1,y1,retX,retY);
    }
}

int Aux::orientacao(const double &x1, const double &y1,
                    const double &x2, const double &y2,
                    const double &x3, const double &y3) {
    const double orin = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

    if (orin > 0.0)      return +1;       // Orientação para o lado esquerdo
    else if (orin < 0.0) return -1;       // Orientação para o lado direito
    else                 return 0;        // Orientação neutra, ou seja, colinear
}

void Aux::criarTrianguloEquilatero(const double &x1, const double &y1,
                                   const double &x2, const double &y2,
                                   double &x3, double &y3) {
    const double sin60 = 0.86602540378443864676372317075294;
    const double cos60 = 0.50000000000000000000000000000000;

    // Translação para x1,y1 para a origem
    const double tx = x2 - x1;
    const double ty = y2 - y1;

    // Roda 60 graus e efetua translação de volta
    x3 = ((tx * cos60) - (ty * sin60)) + x1;
    y3 = ((ty * cos60) + (tx * sin60)) + y1;
}

void Aux::pontoDeInterseccao(const double &x1, const double &y1, const double &x2, const double &y2,
                             const double &x3, const double &y3, const double &x4, const double &y4,
                             double &ix, double &iy) {
    const double dx1 = x2 - x1;
    const double dx2 = x4 - x3;
    const double dx3 = x1 - x3;

    const double dy1 = y2 - y1;
    const double dy2 = y1 - y3;
    const double dy3 = y4 - y3;

    double ratio = dx1 * dy3 - dy1 * dx2;

    if (ratio != 0.0) {
        ratio = (dy2 * dx2 - dx3 * dy3) / ratio;
        ix    = x1 + ratio * dx1;
        iy    = y1 + ratio * dy1;
    } else {
        if ((dx1 * -dy2) == (-dx3 * dy1)) {
            ix = x3;
            iy = y3;
        } else {
            ix = x4;
            iy = y4;
        }
    }
}
