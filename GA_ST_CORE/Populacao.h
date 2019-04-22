#ifndef POPULACAO_H
#define POPULACAO_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "Individuo.h"

using namespace std;

class Populacao {
	private:
		vector<Individuo> individuo;						// Individuos da população
		unsigned int qtdIndividuos = 0;				        // Número de indivíduos da população
	public:
		void addIndividuo(Individuo individuo);			    // Adiciona Indivíduo
		void remIndividuo(unsigned int indice);				// Remove Indivíduo
		const unsigned int getQtdIndividuos();				// Retorna quantidade de indivíduos
		Individuo &getIndividuo(unsigned int indice);		// Retorna Indivíduo
		const unsigned int getDominante();					// Retorna indivíduo mais apto
		const unsigned int getPior();                       // Retorna indivíduo menos apto
		const double getDesvioPadrao();						// Retorna desvio padrão da população
		const void printIndividuo(unsigned int indice, bool exibirPtSt = true, bool exibirCrom = true);	    // Mostra dados do indivíduo (ind, exibir pontos steiner, exibir cromossomo)
		const string getLogIndividuo(unsigned int indice, bool exibirPtSt = true, bool exibirCrom = true);  // Retorna uma string contendo dados do individuo (fitnes, pontos steiner, cromossomo)
};

#endif // POPULACAO_H
