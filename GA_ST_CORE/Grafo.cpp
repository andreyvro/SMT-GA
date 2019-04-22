#include "Grafo.h"

Grafo *Grafo::instancia = 0;

Grafo *Grafo::getInstancia() {
    if (instancia == 0) {
        instancia = new Grafo();
    }
    return instancia;
}

Grafo::Grafo() {}

void Grafo::abrirGrafo(string arquivo) {
    this->qtdVertices = 0;
	ifstream meuArq (arquivo.c_str(), ios::in);
	if (meuArq.is_open()) {
        string qtdVertStr;
        getline(meuArq, qtdVertStr);                                    // 1° Linha = Nº de vértices
        this->qtdVertices = stoi(qtdVertStr);

        if (this->qtdVertices < 3) {
            cout << "Abra um arquivo de grafo com mais de 2 vértices!" << endl;
            meuArq.close();
            exit(EXIT_FAILURE);
		}

        cout << "Abrindo Arquivo de Grafo (" << qtdVertStr << " vértices)." << endl;
        string linha[this->qtdVertices];
        for (unsigned int i = 0; i < this->qtdVertices; i++) {          // Lê posição dos pontos
            getline(meuArq, linha[i]);
        }
        meuArq.close();

        this->grafo.resize(this->qtdVertices, Vertice(0.0, 0.0));
        #pragma omp parallel for
        for (unsigned int i = 0; i < this->qtdVertices; i++) {          // Converte em double
            int delim = linha[i].find(" ");
            double x = stof(linha[i].substr(0, delim));
			double y = stof(linha[i].substr(delim + 1));
			this->grafo.at(i).setX(x);
			this->grafo.at(i).setY(y);
        }

		setDistancia();		                                            // Seta Matriz de Distância
    } else {
		cout << "Não foi possível abrir o arquivo de grafo!" << endl;
		cout << "Arquivo: " << arquivo << endl;
		exit(EXIT_FAILURE);
	}
}

void Grafo::setDistancia() {		// Private
    // Cria matriz de distâncias
    this->distancia.resize(this->qtdVertices, vector<double>(this->qtdVertices));
    #pragma omp parallel for
    for (unsigned int i = 0; i < this->qtdVertices - 1; i++) {
        #pragma omp parallel for
        for (unsigned int j = i + 1; j < this->qtdVertices; j++) {
            Vertice &v1 = this->grafo.at(i);
            Vertice &v2 = this->grafo.at(j);
            double dist = Aux::getDistancia(v1.getX(), v1.getY(), v2.getX(), v2.getY());
            // Matriz de Distância
            this->distancia[i][j] = dist;
            this->distancia[j][i] = dist;
        }
    }
}

const unsigned int Grafo::getQtdVertices() {
	return this->qtdVertices;
}

Vertice &Grafo::getVertice(unsigned int indice) {
	return this->grafo.at(indice);
}

const double Grafo::getDistancia(unsigned int indice1, unsigned int indice2) {
    return this->distancia[indice1][indice2];
}
