#include "Populacao.h"

void Populacao::addIndividuo(Individuo individuo) {
	this->individuo.push_back(individuo);			// Insere indivíduo na população
	this->qtdIndividuos++;
}

void Populacao::remIndividuo(unsigned int indice) {
	this->individuo.erase(this->individuo.begin() + indice);	// Remove do vetor
	this->qtdIndividuos--;
}

const unsigned int Populacao::getQtdIndividuos() {
	return this->qtdIndividuos;
}

Individuo &Populacao::getIndividuo(unsigned int indice) {
    return this->individuo.at(indice);
}

const unsigned int Populacao::getDominante() {
	unsigned int melhorInd = 0;
	double melhorFitness = this->individuo.at(melhorInd).getFitness();
	for (unsigned int i = 1; i < this->qtdIndividuos; i++) {
		double fitness = this->individuo.at(i).getFitness();
		if (fitness <= melhorFitness) {
			melhorInd = i;
			melhorFitness = fitness;
		}
	}
	return melhorInd;
}

const unsigned int Populacao::getPior() {
	unsigned int piorInd = 0;
	double piorFitness = this->individuo.at(piorInd).getFitness();
	for (unsigned int i = 1; i < this->qtdIndividuos; i++) {
		double fitness = this->individuo.at(i).getFitness();
		if (fitness > piorFitness) {
			piorInd = i;
			piorFitness = fitness;
		}
	}
	return piorInd;
}

const double Populacao::getDesvioPadrao() {
	double media = 0.0, variancia = 0.0;
	for (unsigned int i = 0; i < this->qtdIndividuos; i++) {
		media += this->individuo.at(i).getFitness();
	}
	media /= this->qtdIndividuos;
	for (unsigned int i = 0; i < this->qtdIndividuos; i++) {
        double v = this->individuo.at(i).getFitness() - media;
		variancia += v * v; // Eleva ao quadrado
	}
	variancia /= this->qtdIndividuos;
	return sqrt(variancia);		// Desvio padrão
}

const void Populacao::printIndividuo(unsigned int indice, bool exibirPtSt, bool exibirCrom) {
	Individuo ind = this->individuo.at(indice);
	stringstream fitness;
    fitness << fixed << setprecision(9) << ind.getFitness();
	cout << "Individuo (" << indice << "): " << fitness.str() << endl;

    unsigned int qtdVerticesTotal = ind.getQtdPtTotal();
    if (exibirPtSt == true) {
        unsigned int qtdVerticesGrafo = ind.getQtdPtFixo();
        cout << "\tPontos Steiner:" << endl;
        for (unsigned int i = qtdVerticesGrafo; i < qtdVerticesTotal; i++) {
            cout << "\t\tPonto (" << i - qtdVerticesGrafo << "):" << endl;
            cout << "\t\t\tX:" << ind.getVertice(i).getX() << endl;
            cout << "\t\t\tY:" << ind.getVertice(i).getY() << endl;
        }
	}

	if (exibirCrom == true) {
        cout << "\tCromossomo:" << endl;
        for (unsigned int i = 0; i < qtdVerticesTotal; i++) {
            cout << "\t\t|";
            for (unsigned int j = 0; j < qtdVerticesTotal; j++) {
                cout<< ind.getGene(i, j) << "|";
            }
            cout << endl;
        }
	}

	cout << endl;
}

const string Populacao::getLogIndividuo(unsigned int indice, bool exibirPtSt, bool exibirCrom) {
    Individuo ind = this->individuo.at(indice);

    stringstream fitness;
    fitness << fixed << setprecision(9) << ind.getFitness();
    string ret = fitness.str() + "\n";

    unsigned int qtdVerticesTotal = ind.getQtdPtTotal();
    if (exibirPtSt == true) {
        ret += to_string(ind.getQtdPtSteiner()) + "\n";         // Qtd de pontos steiner
        unsigned int qtdVerticesGrafo = ind.getQtdPtFixo();
        for (unsigned int i = qtdVerticesGrafo; i < qtdVerticesTotal; i++) {
            ret += to_string(ind.getVertice(i).getX()) + " " + to_string(ind.getVertice(i).getY()) + "\n";
        }
	}

	if (exibirCrom == true) {
        ret += to_string(qtdVerticesTotal) + "\n";                         // Tamanho do cromossomo
        for (unsigned int i = 0; i < qtdVerticesTotal - 1; i++) {
            for (unsigned int j = i + 1; j < qtdVerticesTotal; j++) {
                ret += to_string(ind.getGene(i, j));
            }
            ret += "\n";
        }
	}
	return ret;
}
