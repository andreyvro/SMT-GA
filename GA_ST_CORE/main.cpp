#include <iostream>
#include <chrono>
#include "Grafo.h"
#include "Populacao.h"
#include "GA.h"

using namespace std;

int main(int argc, char* argv[]) {
    Aux::setTitulo();
    if (argc < 6) {
        Aux::setModoUso();                           // Se não forem passados 9 parametros obrigatórios, exibe "Modo de usar"
        return 1;
    }
    string arqGrafo = argv[1];                                          // Arquivo do Grafo a ser resolvido

    unsigned int qtdInd = atoi(argv[2]);                                // Quantidade de Indivíduos
    float indCruz = atof(argv[3]);                                      // Índice de Cruzamento
    float indMut = atof(argv[4]);                                       // Índice de Mutação
    unsigned int qtdIter = atoi(argv[5]);                               // Quantidade de Iterações
    double fitAtingir = atof(argv[6]);                                  // Fitness a ser atingido, se não possui enviar zero

    string arqSaida = (argc > 7) ? argv[7] : "";                        // Arquivo de Saída do GA (AMS)

    unsigned int sementeRnd = (argc > 8) ? atoi(argv[8]) : time(0);     // Semente para gerador de números aleatórios

// Inicio
    srand(sementeRnd);                                                  // Inicia gerador de números aleatórios
    auto start = std::chrono::high_resolution_clock::now();

	Grafo *grafo = Grafo::getInstancia();
	grafo->abrirGrafo(arqGrafo);                                        // Abre arquivo de grafo

// Arvore Mínima de Steiner
    cout << "Iniciando Algoritmo Genético para AMS." << endl << endl;
    Populacao *popAGM = new Populacao;                                  // População vazia para a árvore geradora mínima
    Populacao *popAMS = new Populacao;                                  // População para a árvore mínima de Steiner
    GA ga(popAGM, popAMS, qtdInd, indCruz, indMut, fitAtingir);         // Constrói população
    ga.iniciarGA(qtdIter, false);                                       // GA para criar arvore mínima de steiner

// Fim
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << "Tempo de execução (s): " << elapsed.count() << endl << endl;

// Log
    bool exibirInfo = (arqSaida == "") ? true : false;
    cout << "Melhor árvore geradora (" << qtdIter << " gerações):" << endl;
    unsigned int melhorInd = popAGM->getDominante();
    popAGM->printIndividuo(melhorInd, exibirInfo, exibirInfo);          // Exibe dados da melhor árvore geradora
    cout << "Melhor árvore de Steiner:" << endl;
    melhorInd = popAMS->getDominante();
    popAMS->printIndividuo(melhorInd, exibirInfo, exibirInfo);          // Exibe dados da melhor árvore de Steiner

    if (arqSaida != "") {
        string log = arqGrafo + "\n";
        log += to_string(elapsed.count()) + "\n";                       // Tempo de execução
        log += to_string(qtdInd) + " " + to_string(indCruz) + " " + to_string(indMut) + " " + to_string(qtdIter) + " "+ to_string(sementeRnd) + "\n";
        log += popAMS->getLogIndividuo(melhorInd);                      // Fitness, Pontos Steiner, Cromossomo
        log += ga.getLog();                                             // Fitness em cada iteração
        Aux::setArqSaida(arqSaida, log);                                // Grava arquivo em disco
    }

    return 0;
}
