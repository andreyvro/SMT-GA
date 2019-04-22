#ifndef GAAMS_H
#define GAAMS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <omp.h>
#include "Populacao.h"
#include "Individuo.h"
#include "Aux.h"

using namespace std;

class GA {
	private:
		Populacao *populacaoAGM;                                                // População para gerar árvores geradores
		Populacao *populacaoAMS;                                                // População para gerar a árvore mńima de Steiner
		float indCruzamento;                                                    // Índice de Cruzamento
		float indMutacao;                                                       // Índice de Mutação
		double fitAtingir;
		string log;                                                             // Log de execução

		void criarArvorePrimRst(Individuo &ind);                                // Cria árvore geradora
		void criarArvorePrim(Individuo &ind, unsigned int gan);                 // Cria árvore geradora
		void criarArvoreRandWalkRST(Individuo &ind);

		const unsigned int getSelecao(Populacao *&pop, const unsigned int naoSelecionar = -1);           // Seleção por torneio

		Individuo setCruzPrimRst(Individuo &ind1, Individuo &ind2);                                     // Cruzamento
		Individuo setCruzPrimRstHeuristico(Individuo &ind1, Individuo &ind2);                           // Cruzamento
		Individuo setCruzPrimRstHeuristicoPlus(Individuo &ind1, Individuo &ind2, unsigned int gan);     // Cruzamento
		Individuo setCruzKruskalHeuristicoPlus(Individuo &ind1, Individuo &ind2);                       // Cruzamento

		Individuo setMutDesconectaHeuristico(Individuo &ind, unsigned int gan);                         // Mutação
		Individuo setMutConectaAleatorio(Individuo &ind);                                               // Mutação
		Individuo setMutConectaHeuristico(Individuo &ind);                                              // Mutação
		Individuo setMutConectaAdjAleatorio(Individuo &ind);                                            // Mutação
		Individuo setMutConectaAdjHeuristico(Individuo &ind);                                           // Mutação
		Individuo setMutConectaAdj2H(Individuo &ind);                                           // Mutação
		Individuo setMutConectaAdjHeuristicoPlus(Individuo &ind);                                       // Mutação
		Individuo setMutGrau1Aleatorio(Individuo &ind);                                                 // Mutação
		Individuo setMutGrau1Heuristico(Individuo &ind);                                                // Mutação

		unsigned int addPontoSteiner(Individuo &ind, unsigned int v1, unsigned int v2, unsigned int v3);            // Insere ponto Steiner através de v1-v2, v1-v3
		void remPontoSteiner(Individuo &ind, unsigned int s1, unsigned int v1, unsigned int v2, unsigned int v3);   // Remove ponto Steiner e une v1-v2, v1-v3
        void criarArvoreSteiner(Individuo &ind, double prec = 0.001);                              // Cria árvore de Steiner através de árvore geradora mínima
		void reposicionaPontos(Individuo &individuo);                                              // Reposiciona pontos Steiner em suas posições ideais
		void reposicionaPontosSmith(Individuo &individuo, double prec = 0.001);
		double length(Individuo &ind, vector< vector<unsigned int> > &lstAdj, vector< vector< double > > &lstDist);
		double error(Individuo &ind, vector< vector<unsigned int> > &lstAdj, vector< vector< double > > &lstDist);
		void optimize(Individuo &ind, vector< vector<unsigned int> > &lstAdj, vector< vector< double > > &lstDist, double tol);
		void removePontosSobrepostos(Individuo &ind);                                               // Remove pontos Steiner que estajam sobre pontos fixos

	public:
		GA(Populacao *popAGM, Populacao *popAMS, unsigned int qtdInd, float indCruz, float indMut, double fitAt);   // Cria uma população inicial
		void iniciarGA(unsigned int numIteracoes, bool exibirInfo);                                                 // Inicia Algoritmo
		string getLog();                                                                                            // Retorna melhor fitness das gerações
};

#endif // GAAMS_H
