#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <vector>
#include <algorithm>
#include <omp.h>
#include "Grafo.h"
#include "Aux.h"

using namespace std;

class Individuo {
    private:
        Grafo *grafo;
        unsigned int qtdPontosSteiner = 0;                          // Quantidade de Pontos steiner
		vector<Vertice> pontoSteiner;                               // Armazena vértices (grafo e steiner)
		vector< vector<bool> > matrizAdj;                           // Matriz de adjacencia
		double fitness;                                             // Fitness do indivíduo
	public:
		Individuo();						                        // Inicia cromossomo zerado

		const unsigned int getQtdPtFixo();                          // Retorna a quantidade de vertices do grafo
		const unsigned int getQtdPtSteiner();                       // Retorna quantidade de pontos steiner
		const unsigned int getQtdPtTotal();                         // Retorna tamanho do cromossomo
		const unsigned int getQtdMaxSteiner();                      // Retorna a quantidade máxima de pontos steiner

		void addPontoSteiner(Vertice pontoSteiner);                 // Adiciona um ponto Steiner
		void remPontoSteiner(unsigned int indice);	                // Remove um ponto Steiner (indice do ponto steiner)

        Vertice &getVertice(unsigned int indice);                   // Retorna Vértice (grafo e steiner)
        double getDistancia(unsigned int indice1, unsigned int indice2);     // Retorna distancia entre dois vértices
        double getAngulo(unsigned int indice1, unsigned int indice2, unsigned int indice3);

		void setGene(unsigned int x, unsigned int y, bool valor);	// Altera gene
		const bool getGene(unsigned int x, unsigned int y);			// Retorna gene

        // Retorna lista de vertices que são adjacêntes, Se (ordenado == true), retorna vértices ordenados por menor distância
		void getPtsAdjacentes(unsigned int vertice, vector<unsigned int> &adj, bool ordenar = false);

        void calcularFitness();                                     // Calcula e seta valor de fitness
		void setFitness(double fitness);							// Seta valor de Fitness
		const double getFitness();									// Retorna fitness do indivíduo
};
#endif // INDIVIDUO_H
