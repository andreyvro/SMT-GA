#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <omp.h>
#include "Vertice.h"
#include "Aux.h"

using namespace std;

class Grafo {
	private:
        static Grafo *instancia;                                                // Armazenará a instância (Singleton)
        Grafo();                                                                // Construtor para evitar instância
		vector<Vertice> grafo;					                                // Conjunto de vertices
		unsigned int qtdVertices = 0;				                            // Número de vértices do grafo
		vector< vector<double> > distancia;                                      // Matriz de distâncias
		void setDistancia();                                                    // Cria matriz de distâncias
	public:
        static Grafo *getInstancia();                                           // Método de acesso estático
		void abrirGrafo(string arquivo);		                                // Importa grafo de arquivo.txt
		const unsigned int getQtdVertices();	                                // Retorna a quantidade de vertices
		const double getDistancia(unsigned int indice1, unsigned int indice2);   // Retorna distância
		Vertice &getVertice(unsigned int indice);                               // Retorna um vertice do grafo
};

#endif // GRAFO_H
