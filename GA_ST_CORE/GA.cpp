#include "GA.h"
// Árvore Geradora Steady State
GA::GA(Populacao *popAGM, Populacao *popAMS, unsigned int qtdInd, float indCruz, float indMut, double fitAt) {
	this->populacaoAGM = popAGM;
	this->populacaoAMS = popAMS;
	this->indCruzamento = indCruz;
	this->indMutacao = indMut;
	this->fitAtingir = fitAt;
	// Constrói população
	for (unsigned int i = 1; i <= qtdInd; i++) {
		Individuo individuo;                            // Cria individuo com matriz de adjascência para a quantidade de verties do grafo
        //this->criarArvorePrim(individuo, 2);
        this->criarArvorePrimRst(individuo);
        //this->criarArvoreRandWalkRST(individuo);

        Individuo indSMT = individuo;
        this->criarArvoreSteiner(indSMT);
        individuo.setFitness(indSMT.getFitness());

		this->populacaoAGM->addIndividuo(individuo);    // Adiciona Indivíduo à população
	}
}

void GA::criarArvorePrimRst(Individuo &ind) {		        // Private
// Cria uma arvore válida, ligando vertices a uma arvore
	unsigned int qtdPtFixo = ind.getQtdPtFixo();        // Total de vertices do grafo
	vector<unsigned int> vertFora;							// Lista de vertices que não estão na arvore
	for (unsigned int i = 0; i < qtdPtFixo; i++) {
		vertFora.push_back(i);
	}
	random_shuffle(vertFora.begin(), vertFora.end());       // Mistura indices

	// Insere vertice aleatório para iniciar arvore
	vector<unsigned int> arvore;							// Lista de vertices que estão na arvore
	arvore.push_back(vertFora.at(0));                       // Insere um vértice para inicia a árvore
    vertFora.erase(vertFora.begin());                       // Remove da lista de vértices que estão fora da árvore
    // Adiciona os vértices que estão fora da árvore conectando-os aos que estão.
	while (vertFora.size() > 0) {
		// Vertice aleatório que está na arvore
		unsigned int rndArvore = rand() % arvore.size();	// Um vertice aleatório da arvore
		unsigned int vlArvore = arvore.at(rndArvore);		// Valor do vértice

		// Vertice mais próximo que ainda não está na arvore
		/*unsigned int iMelhorVert = 0;
		unsigned int vlMelhorVert = vertFora.at(iMelhorVert);   // Um vertice que não está na arvore
		double distMelhorVert = ind.getDistancia(vlArvore, vlMelhorVert);
		for (unsigned int i = 1; i < vertFora.size(); i++) {
            unsigned int vlVert = vertFora.at(i);		// Um vertice que não está na arvore
            double distVert = ind.getDistancia(vlArvore, vlVert);
            if (distVert < distMelhorVert) {
                iMelhorVert = i;
                vlMelhorVert = vlVert;
                distMelhorVert = distVert;
            }
		}*/

		unsigned int iMelhorVert = rand() % vertFora.size();
		unsigned int vlMelhorVert = vertFora.at(iMelhorVert);

		arvore.push_back(vlMelhorVert);						        // Adiciona vertice a árvore
		vertFora.erase(vertFora.begin() + iMelhorVert);              // Remove vértice da lista de vertices
		// Adiciona aresta na matriz de adjascencia
		ind.setGene(vlArvore, vlMelhorVert, true);	    // Seta valor no cromossomo (matriz de adjacência)
	}
}

void GA::criarArvorePrim(Individuo &ind, unsigned int gan) {	// Private
// Cria uma arvore válida, através do algoritmo de Prim
	unsigned int qtdPtFixo = ind.getQtdPtFixo();            // Total de vertices do grafo
	vector<unsigned int> vertFora;							// Lista de vertices que não estão na arvore
	for (unsigned int i = 0; i < qtdPtFixo; i++) {
		vertFora.push_back(i);
	}

	// Insere vertice aleatório para iniciar arvore
	vector<unsigned int> arvore;							// Lista de vertices que estão na arvore
	unsigned int rndFora = rand() % vertFora.size();
	arvore.push_back(vertFora.at(rndFora));                 // Insere um vértice para inicia a árvore
    vertFora.erase(vertFora.begin() + rndFora);             // Remove da lista de vértices que estão fora da árvore
    // Adiciona os vértices que estão fora da árvore conectando-os aos que estão.
	while (vertFora.size() > 0) {
        // Cria vetor de distâncias
        vector< vector< double >> distancia;        // (distância, indiceVertArvore, indiceVertFora)
		for (unsigned int i = 0; i < arvore.size(); i++) {
            for (unsigned int j = 0; j < vertFora.size(); j++) {
                double distVert = ind.getDistancia(arvore.at(i), vertFora.at(j));
                vector<double> dist = {distVert, (double)i, (double)j};
                distancia.push_back(dist);
            }
        }

        unsigned int rndMenor = (rand() % gan) + 1;     // iº menor valor
        if (rndMenor > distancia.size()) {
            rndMenor = distancia.size() - 1;
        }
        unsigned int iMelhorArv, iMelhorVert;           // vértice dentro, vértice fora

        for (unsigned int iter = 0; iter < rndMenor; iter++) {
            unsigned int iMenor = 0;
            double vlMenor = distancia[0][0];
            for (unsigned int i = 1; i < distancia.size(); i++) {
                if (distancia[i][0] < vlMenor) {
                    iMenor = i;
                    vlMenor = distancia[i][0];
                }
            }
            iMelhorArv = distancia[iMenor][1];
            iMelhorVert = distancia[iMenor][2];
            distancia.erase(distancia.begin() + iMenor);
        }

        unsigned int vlMelhorArv = arvore.at(iMelhorArv);
		unsigned int vlMelhorVert = vertFora.at(iMelhorVert);

		arvore.push_back(vlMelhorVert);                     // Adiciona vertice a árvore
		vertFora.erase(vertFora.begin() + iMelhorVert);     // Remove vértice da lista de vertices
		// Adiciona aresta na matriz de adjascencia
		ind.setGene(vlMelhorArv, vlMelhorVert, true);	    // Seta valor no cromossomo (matriz de adjacência)
	}
}

void GA::criarArvoreRandWalkRST(Individuo &ind) {		        // Private
// Cria uma arvore válida, ligando vertices a uma arvore (RandWalkRST)
	unsigned int qtdPtFixo = ind.getQtdPtFixo();        // Total de vertices do grafo
	vector<unsigned int> vertFora;							// Lista de vertices que não estão na arvore
	for (unsigned int i = 0; i < qtdPtFixo; i++) {
		vertFora.push_back(i);
	}
	random_shuffle(vertFora.begin(), vertFora.end());       // Mistura indices

	// Insere vertice aleatório para iniciar arvore
	vector<unsigned int> arvore;							// Lista de vertices que estão na arvore
	arvore.push_back(vertFora.at(0));                       // Insere um vértice para inicia a árvore
    vertFora.erase(vertFora.begin());                       // Remove da lista de vértices que estão fora da árvore
    // Adiciona os vértices que estão fora da árvore conectando-os aos que estão.
	while (vertFora.size() > 0) {
		// Vertice aleatório que está na arvore
		unsigned int iArvore = arvore.size() - 1;	        // Ultimo vertice adicionado na arvore
		unsigned int vlArvore = arvore.at(iArvore);		    // Valor do vértice
		// Vertice aleatório que ainda não está na arvore
		unsigned int vlVertice = vertFora.at(0);		    // Um vertice aleatório que não está na arvore
		arvore.push_back(vlVertice);						// Adiciona vertice a árvore
		vertFora.erase(vertFora.begin());		            // Remove vértice da lista de vertices
		// Adiciona aresta na matriz de adjascencia
		ind.setGene(vlArvore, vlVertice, true);	    // Seta valor no cromossomo (matriz de adjacência)
	}
}

void GA::iniciarGA(unsigned int numIteracoes, bool exibirInfo) {
    this->log = "";
    double epsilon = 0.000005;

	unsigned int melhorInd = this->populacaoAGM->getDominante();             // Índice do melhor indivíduo da população
	Individuo melhor = this->populacaoAGM->getIndividuo(melhorInd);
    double melhorFit = melhor.getFitness();                                  // Fitness do melhor indivíduo

    unsigned int qtdStag = 0;
    unsigned int qtdStagSai = 0;
    double melhorFitAnt = melhorFit;

    unsigned int qtdInd = this->populacaoAGM->getQtdIndividuos();
    unsigned int qtdCruz = (qtdInd * this->indCruzamento) / 100;
    //unsigned int qtdMut = (qtdInd * this->indMutacao) / 100;    // Qtd de individuos a remover no reset

    unsigned int iInd1, iInd2;
    Individuo ind1, ind2;

    Individuo melhorGlob = melhor;
    double melhorFitGlob = melhorFit;

    unsigned int qtdMaxStag = 10;//(numIteracoes * 2) / 100;        // 10% das iterações
    unsigned int qtdMaxStagSai = 50;//(numIteracoes * 20) / 100;    // 20% das iterações
    double desvioPadrao = this->populacaoAGM->getDesvioPadrao();

    for (unsigned int iter = 1; iter <= numIteracoes; iter++) {
        if (qtdStagSai == qtdMaxStagSai) {     // Sem reset = 50; com reset = 75
            break;
        }
        //if (desvioPadrao < 0.01) {
        if (qtdStag == qtdMaxStag) {
            //cout << "Reset\n";
            //for(unsigned int i = 0; i < qtdInd; i++) {
                //this->populacaoAGM->remIndividuo(0);
            //}
            //this->populacaoAGM->addIndividuo(melhor);
            this->populacaoAGM->remIndividuo(melhorInd);
            //for(unsigned int i = 1; i < qtdInd; i++) {
                Individuo individuo;
                this->criarArvorePrimRst(individuo);
                //this->criarArvoreRandWalkRST(individuo);

                Individuo indSMT = individuo;
                this->criarArvoreSteiner(indSMT);
                individuo.setFitness(indSMT.getFitness());
                this->populacaoAGM->addIndividuo(individuo);
            //}

            qtdStag = 0;
        }
        // Aplica cruzamento e mutação
        for (unsigned int i = 0; i < qtdCruz; i++) {
        //if ((rand() % 100) < this->indCruzamento) {
            iInd1 = this->getSelecao(this->populacaoAGM);
            iInd2 = this->getSelecao(this->populacaoAGM, iInd1);
            ind1 = populacaoAGM->getIndividuo(iInd1);
            ind2 = populacaoAGM->getIndividuo(iInd2);

            Individuo filho;
            //filho = this->setCruzPrimRst(ind1, ind2);
            //if (i % 2 == 0) {
                filho = this->setCruzPrimRstHeuristicoPlus(ind1, ind2, 2);  // Prim
            //} else {
                //filho = this->setCruzKruskalHeuristicoPlus(ind1, ind2);   // Kruskal
            //}

            filho = this->setMutConectaAdjHeuristico(filho);            // Adj
            filho = this->setMutDesconectaHeuristico(filho, 2);         // Rem

            //filho = this->setMutGrau1Heuristico(filho);
            //filho = this->setMutConectaHeuristico(filho);
            //filho = this->setMutConectaAdjAleatorio(filho);

            /*if (ind1.getFitness() > ind2.getFitness()) {
                populacaoAGM->remIndividuo(iInd1);
            } else {
                populacaoAGM->remIndividuo(iInd2);
            }*/
            //  Calcula fitness do filho
            Individuo indSMT = filho;
            this->criarArvoreSteiner(indSMT);
            filho.setFitness(indSMT.getFitness());

            if (!isnan(filho.getFitness())) {
                this->populacaoAGM->remIndividuo(this->populacaoAGM->getPior());
                this->populacaoAGM->addIndividuo(filho);
            }
        }

		melhorInd = this->populacaoAGM->getDominante();
		melhor = this->populacaoAGM->getIndividuo(melhorInd);
        melhorFit = melhor.getFitness();

        if (fabs(melhorFit - melhorFitAnt) < 0.0000000001) {
            qtdStag++;
            qtdStagSai++;
        } else {
            melhorFitAnt = melhorFit;
            qtdStag = 0;
            qtdStagSai = 0;
        }

        if (melhorFit < melhorFitGlob) {
            melhorFitGlob = melhorFit;
            melhorGlob = melhor;
        }

        // Armazena Log
        stringstream fitness;
        fitness << fixed << setprecision(9) << melhorFit;
        this->log += fitness.str() + "\n";
		//if (exibirInfo == true) {
            desvioPadrao = this->populacaoAGM->getDesvioPadrao();
            //cout << "Geração " << iter << "\tDesvio Padrão: " << desvioPadrao;
            //cout << "\tMelhor Fitness: " << this->populacaoAGM->getIndividuo(melhorInd).getFitness() << endl;
		//}

		//cout << setprecision(10) << melhorFit << " " << this->fitAtingir << endl;
		if (fabs(melhorFit - this->fitAtingir) < epsilon) {
		//if (melhorFit <= this->fitAtingir) {
            break;
		}
    }

    // Gera árvores de Steiner através das árvores geradoras
    Individuo indSMT = melhorGlob;
	this->criarArvoreSteiner(indSMT, 0.000009);//, 0.000009
    //populacaoAMS->addIndividuo(melhorGlob);
    populacaoAMS->addIndividuo(indSMT);
}

const unsigned int GA::getSelecao(Populacao *&pop, const unsigned int naoSelecionar) {
	// Seleção por torneio
	unsigned int qtdIndiv, ultimoInd, rndIndA, rndIndB;
	qtdIndiv = pop->getQtdIndividuos();
	ultimoInd = qtdIndiv - 1;                           // Indice do ultimo indivíduo da população

	rndIndA = rand() % qtdIndiv;
	if (rndIndA == naoSelecionar) {
        rndIndA = (rndIndA == ultimoInd) ? rndIndA - 1 : rndIndA + 1;
	}
	rndIndB = rand() % qtdIndiv;
	if (rndIndB == naoSelecionar) {
        rndIndB = (rndIndB == ultimoInd) ? rndIndB - 1 : rndIndB + 1;
	}

	if ((pop->getIndividuo(rndIndA).getFitness()) < (pop->getIndividuo(rndIndB).getFitness())) {
        return rndIndA;
	} else {
        return rndIndB;
	}
}

Individuo GA::setCruzPrimRst(Individuo &ind1, Individuo &ind2) {
// PrimRST
    Individuo ind[2] = {ind1, ind2};    // Pais
    Individuo filho;
    unsigned int qtdPtFixo = ind[0].getQtdPtFixo();
    vector<unsigned int> fora;      // Vértices que ainda não estão na arvore
    vector<unsigned int> arvore;    // Vértices que foram adicionados na arvore
    // Cria lista de adjacencias
    vector< vector<unsigned int> > lstAdj;          // Lista de adjacencias
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        lstAdj.push_back(vector<unsigned int>());   // Adiciona uma linha vazia
    }
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        ind[0].getPtsAdjacentes(i, lstAdj[i]);          // Adiciona vértices adjacentes do indivíduo1 em adj
        ind[1].getPtsAdjacentes(i, lstAdj[i]);          // Adiciona vértices adjacentes do ind2 em adj
        sort(lstAdj[i].begin(), lstAdj[i].end());                                       // Ordena lista de adjacência
        lstAdj[i].erase(unique(lstAdj[i].begin(), lstAdj[i].end()), lstAdj[i].end());   // Remove elementos duplicados da lista de adjacencia
        fora.push_back(i);                             // Adiciona indice a lista de vértices que ainda não estão na árvore
    }
    // Insere um vértice aleatório na arvore
    unsigned int item = rand() % qtdPtFixo;
    arvore.push_back(fora.at(item));
    fora.erase(fora.begin() + item);
    // Inicia busca
    while (fora.size() > 0) {
        // Vértice aleatório da arvore
        unsigned int tamArv = arvore.size();
        if (tamArv > 0) {
            unsigned int ivertArv = rand() % tamArv;     // Indice do ultimo elemento da arvore
            unsigned int vertArv = arvore.at(ivertArv);         // Valor do ultimo elemento da arvore
            // Adjacente de menor distância
            unsigned int rndAdj = rand() % lstAdj[vertArv].size();
            unsigned int adj = lstAdj[vertArv][rndAdj];
            lstAdj[vertArv].erase(lstAdj[vertArv].begin() + rndAdj);
            // Busca adj em fora
            auto iFora = find(fora.begin(), fora.end(), adj);
            if (iFora != fora.end()) {              // Se encontrou
                arvore.push_back(adj);
                filho.setGene(vertArv, adj, true);  // Adiciona adjacencia em filho
                fora.erase(iFora);
            }
            // Remove da arvore se não há mais adjacencias
            if (lstAdj[vertArv].size() == 0) {              // Se não tem adjacencias
                arvore.erase(arvore.begin() + ivertArv);    // Remove da arvore
            }
        } else {
            cout << "PrimRst - Não ha mais vértices na árvore" << endl;
            break;
        }
    }
    // Calcula fitness do filho, e o retorna
    /*Individuo indSMT = filho;
	this->criarArvoreSteiner(indSMT);
	filho.setFitness(indSMT.getFitness());*/
	return filho;
}

Individuo GA::setCruzPrimRstHeuristico(Individuo &ind1, Individuo &ind2) {
// PrimRST*
    Individuo ind[2] = {ind1, ind2};    // Pais
    Individuo filho;
    unsigned int qtdPtFixo = ind[0].getQtdPtFixo();
    vector<unsigned int> fora;      // Vértices que ainda não estão na arvore
    vector<unsigned int> arvore;    // Vértices que foram adicionados na arvore
    // Cria lista de adjacencias
    vector< vector<unsigned int> > lstAdj;          // Lista de adjacencias
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        lstAdj.push_back(vector<unsigned int>());   // Adiciona uma linha vazia
    }
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        ind[0].getPtsAdjacentes(i, lstAdj[i]);          // Adiciona vértices adjacentes do indivíduo1 em adj
        ind[1].getPtsAdjacentes(i, lstAdj[i]);          // Adiciona vértices adjacentes do ind2 em adj
        sort(lstAdj[i].begin(), lstAdj[i].end());                                       // Ordena lista de adjacência
        lstAdj[i].erase(unique(lstAdj[i].begin(), lstAdj[i].end()), lstAdj[i].end());   // Remove elementos duplicados da lista de adjacencia
        fora.push_back(i);                             // Adiciona indice a lista de vértices que ainda não estão na árvore
    }
    // Insere um vértice aleatório na arvore
    unsigned int item = rand() % qtdPtFixo;
    arvore.push_back(fora.at(item));
    fora.erase(fora.begin() + item);
    // Inicia busca
    while (fora.size() > 0) {
        unsigned int tamArv = arvore.size();
        if (tamArv > 0) {
            // Vértice aleatório da arvore
            unsigned int ivertArv = rand() % tamArv;     // Indice do ultimo elemento da arvore
            unsigned int vertArv = arvore.at(ivertArv);         // Valor do ultimo elemento da arvore
            // Torneio entre dois adjacentes (distânica menor ganha)
            unsigned int qtdAdj = lstAdj[vertArv].size();
            unsigned int iAdj, adj;                     // Vértice vencedor do torneio
            unsigned int rndAdj1 = rand() % qtdAdj;
            unsigned int adj1 = lstAdj[vertArv][rndAdj1];
            if (qtdAdj >= 2) {
                double dist1 = ind[0].getDistancia(vertArv, adj1);
                unsigned int rndAdj2 = rand() % qtdAdj;
                unsigned int adj2 = lstAdj[vertArv][rndAdj2];
                double dist2 = ind[0].getDistancia(vertArv, adj2);
                if (dist1 < dist2) {
                    iAdj = rndAdj1;
                    adj = adj1;
                } else {
                    iAdj = rndAdj2;
                    adj = adj2;
                }
            } else {
                iAdj = rndAdj1;
                adj = adj1;
            }

            lstAdj[vertArv].erase(lstAdj[vertArv].begin() + iAdj);
            // Busca adj em fora
            auto iFora = find(fora.begin(), fora.end(), adj);
            if (iFora != fora.end()) {              // Se encontrou
                arvore.push_back(adj);
                filho.setGene(vertArv, adj, true);  // Adiciona adjacencia em filho
                fora.erase(iFora);
            }
            // Remove da arvore se não há mais adjacencias
            if (lstAdj[vertArv].size() == 0) {              // Se não tem adjacencias
                arvore.erase(arvore.begin() + ivertArv);    // Remove da arvore
            }
        } else {
            cout << "PrimRstHeuristico - Não ha mais vértices na árvore" << endl;
            break;
        }
    }
    // Calcula fitness do filho e o retorna
    /*Individuo indSMT = filho;
	this->criarArvoreSteiner(indSMT);
	filho.setFitness(indSMT.getFitness());*/
	return filho;
}

Individuo GA::setCruzPrimRstHeuristicoPlus(Individuo &ind1, Individuo &ind2, unsigned int gan) {
// PrimRST**
    Individuo ind[2] = {ind1, ind2};    // Pais
    Individuo filho;
    unsigned int qtdPtFixo = ind[0].getQtdPtFixo();
    vector<unsigned int> fora;      // Vértices que ainda não estão na arvore
    vector<unsigned int> arvore;    // Vértices que foram adicionados na arvore
    // Cria lista de adjacencias
    vector< vector< unsigned int > > lstAdj(qtdPtFixo, vector<unsigned int>(0));   // Lista de adjacencias
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        ind[0].getPtsAdjacentes(i, lstAdj[i]);          // Adiciona vértices adjacentes do indivíduo1 em adj
        ind[1].getPtsAdjacentes(i, lstAdj[i]);          // Adiciona vértices adjacentes do ind2 em adj
        sort(lstAdj[i].begin(), lstAdj[i].end());                                       // Ordena lista de adjacência
        lstAdj[i].erase(unique(lstAdj[i].begin(), lstAdj[i].end()), lstAdj[i].end());   // Remove elementos duplicados da lista de adjacencia
        fora.push_back(i);                             // Adiciona indice a lista de vértices que ainda não estão na árvore
    }
    // Insere um vértice aleatório na arvore
    unsigned int item = rand() % qtdPtFixo;
    unsigned int vlFora = fora.at(item);
    arvore.push_back(vlFora);
    fora.erase(fora.begin() + item);
    // Remove vértice da lista de adjacenciaa
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        for(unsigned int j = 0; j < lstAdj[i].size(); j++) {
            if (lstAdj[i][j] == vlFora) {
                lstAdj[i].erase(lstAdj[i].begin() + j);
                break;
            }
        }
    }

    // Inicia busca
    while (fora.size() > 0) {
        // Cria vetor de distâncias
        vector< vector< double >> distancia;        // (distância, indiceVertArvore, indiceVertFora)
        for (unsigned int iArv = 0; iArv < arvore.size(); iArv++) {
            unsigned int vlArv = arvore.at(iArv);
            for (unsigned int iAdj = 0; iAdj < lstAdj[vlArv].size(); iAdj++) {
                unsigned int vlAdj = lstAdj[vlArv][iAdj];
                double distVert = ind[0].getDistancia(vlArv, vlAdj);
                vector<double> dist = {distVert, (double)vlArv, (double)vlAdj};
                distancia.push_back(dist);
            }
        }

        unsigned int arvMelhor, foraMelhor;                     // Vértices escolhidos

        unsigned int tamDist = distancia.size();
        if (tamDist > 0) {                                      // Lista de distâncias possui elementos
            unsigned int ganancia = gan;
            if (tamDist < ganancia) {
                ganancia = tamDist;
            }
            unsigned int rndMenor = (rand() % ganancia) + 1;    // iº menor valor
            // Busca por iº menor valor
            for (unsigned int iter = 0; iter < rndMenor; iter++) {
                unsigned int iMenor = 0;
                double vlMenor = distancia[0][0];
                for (unsigned int i = 1; i < tamDist; i++) {
                    if (distancia[i][0] < vlMenor) {
                        iMenor = i;
                        vlMenor = distancia[i][0];
                    }
                }
                arvMelhor = distancia[iMenor][1];
                foraMelhor = distancia[iMenor][2];
                distancia.erase(distancia.begin() + iMenor);
                tamDist--;
            }
            // Remove ForaMelhor da lista de adjacência
            for (unsigned int i = 0; i < qtdPtFixo; i++) {
                for(unsigned int j = 0; j < lstAdj[i].size(); j++) {
                    if (lstAdj[i][j] == foraMelhor) {
                        lstAdj[i].erase(lstAdj[i].begin() + j);
                        break;
                    }
                }
            }
            // Busca ForaMelhor em fora e o remove;
            fora.erase(remove(fora.begin(), fora.end(), foraMelhor), fora.end());
            arvore.push_back(foraMelhor);

            filho.setGene(arvMelhor, foraMelhor, true);	    // Seta valor no cromossomo (matriz de adjacência)
        } //else { cout << "Fuuuuuu" << endl; }
    }

    // Calcula fitness do filho e o retorna
    /*Individuo indSMT = filho;
	this->criarArvoreSteiner(indSMT);
	filho.setFitness(indSMT.getFitness());*/
    return filho;
}

Individuo GA::setCruzKruskalHeuristicoPlus(Individuo &ind1, Individuo &ind2) {
// Representa Disjoint Sets
struct DisjointSets {
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n) {
        // Allocate memory
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        // Initially, all vertices are in different sets and have rank 0.
        for (int i = 0; i <= n; i++) {
            rnk[i] = 0;
            parent[i] = i;  //every element is parent of itself
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u) {
        /* Make the parent of the nodes in the path from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y) {
        x = find(x), y = find(y);

        /* Make tree with smaller height a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

    Individuo pai[2] = {ind1, ind2};    // Pais
    unsigned int qtdPtFx = pai[0].getQtdPtFixo();

    Individuo filho;
    DisjointSets ds(qtdPtFx);   // Cria conjuntos disjuntos

    vector< vector< vector<unsigned int> > > arestasPais(2, vector< vector<unsigned int> >());

    unsigned int set_u, set_v;
    for (unsigned int i = 0; i < qtdPtFx; i++) {			    // Linha da meia matriz de adjacência
		for (unsigned int j = i + 1; j < qtdPtFx; j++) {        // Coluna da meia matriz de adjacência
            bool g1 = pai[0].getGene(i, j);
            bool g2 = pai[1].getGene(i, j);
            vector<unsigned int> aresta { i, j};

            if (g1 == true && g2 == true) {                     // Se há adjacencia nos dois pais
                set_u = ds.find(i);
                set_v = ds.find(j);
                //if (set_u != set_v) {                         // Se não forma ciclo
                ds.merge(set_u, set_v);                         // Junta dois conjuntos
                filho.setGene(i, j, true);                      // Insere arestas em comum
                //}
            } else if (g1 == true) {
                arestasPais[0].push_back(aresta);
            } else if (g2 == true) {
                arestasPais[1].push_back(aresta);
            }
		}
    }

    while ((arestasPais[0].size() > 0) || (arestasPais[1].size() > 0)) {    // Enquanto houver arestas para processar
        unsigned int arPAi, arAresta;

        if ((arestasPais[0].size() > 0) && (arestasPais[1].size() > 0)) {   // Se os dois pais possuem arestas, torneio entre arestas
            unsigned int rndAresta0 = rand() % arestasPais[0].size();
            unsigned int rndAresta1 = rand() % arestasPais[1].size();
            double distP0 = pai[0].getDistancia(arestasPais[0][rndAresta0][0], arestasPais[0][rndAresta0][1]);
            double distP1 = pai[1].getDistancia(arestasPais[1][rndAresta1][0], arestasPais[1][rndAresta1][1]);
            if (distP0 <= distP1) {
            //if ((rand() % 100) < 50) {
                arPAi = 0;
                arAresta = rndAresta0;
            } else {
                arPAi = 1;
                arAresta = rndAresta1;
            }
        } else if (arestasPais[0].size() > 0) {                           // Se somente o pai1 possui arestas, escolhe ultima aresta de pai0
            arPAi = 0;
            arAresta = 0;
        } else {                                                          // Se somente o pai2 possui arestas, escolhe ultima aresta de pai1
            arPAi = 1;
            arAresta = 0;
        }

        unsigned int u = arestasPais[arPAi][arAresta][0];
        unsigned int v = arestasPais[arPAi][arAresta][1];

        set_u = ds.find(u);
        set_v = ds.find(v);

        if (set_u != set_v) {                                   // Se não forma ciclo
            ds.merge(set_u, set_v);                             // Junta dois conjuntos
            filho.setGene(u, v, true);
        }

        arestasPais[arPAi].erase(arestasPais[arPAi].begin() + arAresta);
    }

// Calcula fitness do filho e o retorna
    /*Individuo indSMT = filho;
	this->criarArvoreSteiner(indSMT);
	filho.setFitness(indSMT.getFitness());*/
    return filho;
}

Individuo GA::setMutDesconectaHeuristico(Individuo &ind1, unsigned int gan) {
    // Escolhe um vértice aleatório, e o desconecta de um de seus adjacentes
    // Usa busca em largura a partir dos dois vértices para mapear dois lados da árvore
    // Remove vértice inicial das árvores se cada possui mais de um vértice
    // Crie vetor com distância da combinação entre vértices dos dois lados
    // Escolhe uma combinação até 0 5º menor
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

//for (unsigned int qtdExec = 0; qtdExec < 2; qtdExec++) {

    // Escolhe um vértice aleatório e um adjacente aleatório
    unsigned int vertIni[2];
    vertIni[0] = rand() % qtdPtFixo;
    vector<unsigned int> adj;
    ind.getPtsAdjacentes(vertIni[0], adj);      // Obtem pontos adjacentes
    vertIni[1] = adj.at(rand() % adj.size());

    // Desconecta os dois vértices
    ind.setGene(vertIni[0], vertIni[1], false);

    // Lista vértices dos dois lados através de busca em largura
    vector< vector< unsigned int > > visitado(2, vector<unsigned int>(0));   // Vértices visitados

    for (unsigned int i = 0; i < 2; i++) {          // Percorre lados a partir dos vértices iniciais
        vector <unsigned int> fila;
        fila.push_back(vertIni[i]);

        while (fila.size() > 0) {
            unsigned int vertFila = fila.at(0);     // Processa 1° da fila

            vector<unsigned int> adj;
            ind.getPtsAdjacentes(vertFila, adj);    // Obtem pontos adjacentes

            // Remove da lista de adjacentes se já foi visitado
            unsigned int iAdj = 0;
            while (iAdj < adj.size()) {
                auto iVis = find(visitado[i].begin(), visitado[i].end(), adj.at(iAdj));
                if (iVis != visitado[i].end()) {            // Se encontrou
                    adj.erase(adj.begin() + iAdj);          // Remove vértice da lista de adjacencia
                } else {
                    iAdj++;
                }
            }
            // Adiciona adjacentes em fila
            unsigned int tam = adj.size();
            for (iAdj = 0; iAdj < tam; iAdj++) {
                fila.push_back(adj.at(iAdj));
            }

            // Adiciona vértice em visitados em retira da fila
            visitado[i].push_back(vertFila);
            fila.erase(fila.begin());
        }
    }
    // Exclui pontos iniciais da listagem
    /*for (unsigned int i = 0; i < 2; i++) {
        if (visitado[i].size() > 1) {
            visitado[i].erase(visitado[i].begin());
        }
    }*/

    // Cria vetor de distâncias
    vector< vector< double >> distancia;        // (distância, indiceVertArvore, indiceVertFora)
    unsigned int tam1 = visitado[0].size();
    unsigned int tam2 = visitado[1].size();
    for (unsigned int i = 0; i < tam1; i++) {
        for (unsigned int j = 0; j < tam2; j++) {
            if (!(i == 0 && j == 0)) {
                double distVert = ind.getDistancia(visitado[0][i], visitado[1][j]);
                vector<double> dist = {distVert, (double)visitado[0][i], (double)visitado[1][j]};
                distancia.push_back(dist);
            }
        }
    }

    unsigned int ganancia = gan;
    if (distancia.size() < ganancia) {
        ganancia = distancia.size();
    }
    unsigned int rndMenor = (rand() % ganancia) + 1;    // iº menor valor
    unsigned int iMelhor, jMelhor;                      // Vértices escolhidos

    for (unsigned int iter = 0; iter < rndMenor; iter++) {
        unsigned int iMenor = 0;
        double vlMenor = distancia[0][0];
        for (unsigned int i = 1; i < distancia.size(); i++) {
            if (distancia[i][0] < vlMenor) {
                iMenor = i;
                vlMenor = distancia[i][0];
            }
        }
        iMelhor = distancia[iMenor][1];
        jMelhor = distancia[iMenor][2];
        distancia.erase(distancia.begin() + iMenor);
    }
    ind.setGene(iMelhor, jMelhor, true);	    // Seta valor no cromossomo (matriz de adjacência)
//}

    // Randômico
    /*unsigned int iMelhor = rand() % visitado[0].size();
    unsigned int jMelhor = rand() % visitado[1].size();
    ind.setGene(visitado[0][iMelhor], visitado[1][jMelhor], true);*/
    // Substitui na população
    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutConectaAleatorio(Individuo &ind1) {
    // Escolhe dois vértices aleatoreamente (v1 e v2) e os conecta
    // Escolhe v1 ou v2 aleatoreamente para iniciar uma busca
    // Efetua uma busca em largura afim de encontrar um vértice gerador de ciclo
    // Remove o vértice gerador de ciclos
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    // Escolhe dois vértice aleatoreamente e os conecta
    vector< unsigned int > fora;
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        fora.push_back(i);
    }
    unsigned int rndVert = rand() % fora.size();
    unsigned int vlVert1 = fora.at(rndVert);
    fora.erase(fora.begin() + rndVert);
    rndVert = rand() % fora.size();
    unsigned int vlVert2 = fora.at(rndVert);

    ind.setGene(vlVert1, vlVert2, true);        // Conecta dois vértices

    // Encontra ciclo através de busca em largura
    vector<unsigned int> visitado;
    vector< unsigned int > fila;
    fila.push_back(vlVert1);                    // Insere primeiro vértice na fila

    unsigned int vertFila;
    unsigned int vertAdj;
    bool sair = false;
    while (fila.size() > 0 && sair == false) {
        vertFila = fila.at(0);    // Processa 1° da fila

        vector<unsigned int> adj;
        ind.getPtsAdjacentes(vertFila, adj);   // Obtem pontos adjacentes

        // Remove da lista de adjacentes se já foi visitado
        unsigned int iAdj = 0;
        while (iAdj < adj.size()) {
            auto iVis = find(visitado.begin(), visitado.end(), adj.at(iAdj));
            if (iVis != visitado.end()) {               // Se encontrou
                adj.erase(adj.begin() + iAdj);          // Remove vértice da lista de adjacencia
            } else {
                iAdj++;
            }
        }
        // Insere adjacentes na fila e detecta ciclo
        unsigned int tamAdj = adj.size();
        unsigned int i = 0;
        while (i < tamAdj && sair == false) {
            vertAdj = adj.at(i);
            auto iFila = find(fila.begin(), fila.end(), vertAdj);
            if (iFila != fila.end()) {               // Se encontrou adjacente na fila, existe um ciclo
                sair = true;
            } else {
                fila.push_back(adj.at(i));
                i++;
            }
        }

        visitado.push_back(vertFila);
        fila.erase(fila.begin());
    }

    ind.setGene(vertFila, vertAdj, false);        // Desconecta vértices que geram ciclo

    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutConectaHeuristico(Individuo &ind1) {
    // Escolhe dois vértices aleatoreamente (v1 e v2) e os conecta
    // Escolhe v1 ou v2 aleatoreamente para iniciar uma busca
    // Efetua uma busca em largura afim de encontrar um vértice gerador de ciclo
    // Remove o vértice gerador de ciclos
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    // Escolhe 5 vértice aleatoreamente e escolhe o que possui menor distância ao primeiro
    vector< unsigned int > fora;
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        fora.push_back(i);
    }
    unsigned int qtdPontos = 10;
    vector< unsigned int> dentro;
    for (unsigned int i = 0; i < qtdPontos; i++) {
        unsigned int rndVert = rand() % fora.size();
        dentro.push_back(fora.at(rndVert));
        fora.erase(fora.begin() + rndVert);
    }
    unsigned int iMelhor = 0;
    unsigned int jMelhor = 0;
    double menorDist = ind.getDistancia(dentro.at(0), dentro.at(1));
    for (unsigned int i = 0; i < (qtdPontos - 1); i++) {
        for (unsigned int j = i + 1; j < qtdPontos; j++) {
            if (ind.getGene(dentro.at(i), dentro.at(j)) == false) {
                double distancia = ind.getDistancia(dentro.at(i), dentro.at(j));
                if (distancia < menorDist) {
                    iMelhor = i;
                    jMelhor = j;
                    menorDist = distancia;
                }
            }
        }
    }

    ind.setGene(dentro.at(iMelhor), dentro.at(jMelhor), true);        // Conecta dois vértices

    // Encontra ciclo através de busca em largura
    vector<unsigned int> visitado;
    vector< unsigned int > fila;
    fila.push_back(dentro.at(iMelhor));                    // Insere primeiro vértice na fila

    unsigned int vertFila;
    unsigned int vertAdj;
    bool sair = false;
    while (fila.size() > 0 && sair == false) {
        vertFila = fila.at(0);    // Processa 1° da fila

        vector<unsigned int> adj;
        ind.getPtsAdjacentes(vertFila, adj);   // Obtem pontos adjacentes

        // Remove da lista de adjacentes se já foi visitado
        unsigned int iAdj = 0;
        while (iAdj < adj.size()) {
            auto iVis = find(visitado.begin(), visitado.end(), adj.at(iAdj));
            if (iVis != visitado.end()) {               // Se encontrou
                adj.erase(adj.begin() + iAdj);          // Remove vértice da lista de adjacencia
            } else {
                iAdj++;
            }
        }
        // Insere adjacentes na fila e detecta ciclo
        unsigned int tamAdj = adj.size();
        unsigned int i = 0;
        while (i < tamAdj && sair == false) {
            vertAdj = adj.at(i);
            auto iFila = find(fila.begin(), fila.end(), vertAdj);
            if (iFila != fila.end()) {               // Se encontrou adjacente na fila, existe um ciclo
                sair = true;
            } else {
                fila.push_back(adj.at(i));
                i++;
            }
        }

        visitado.push_back(vertFila);
        fila.erase(fila.begin());
    }

    ind.setGene(vertFila, vertAdj, false);        // Desconecta vértices que geram ciclo

    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutConectaAdjAleatorio(Individuo &ind1) {
    // Escolhe um vértice v1, escolhe um de seus adjacentes diretos, denominado v2
    // Desconecta v1 de v2, e reconecta v1 a um ponto adjacente a v2
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    unsigned int v1, v2;
    unsigned int qtdEfetuar = 1;//(qtdPtFixo * 10) / 100;
    unsigned int efetuado = 0;              // Se efetuou a mutação sob dois vértices
    while (efetuado < qtdEfetuar) {
        v1 = rand() % qtdPtFixo;            // Escolhe um item aleatório (v1)
        vector< unsigned int > adj;
        ind.getPtsAdjacentes(v1, adj);

        unsigned int rndAdj = rand() % adj.size();
        v2 = adj.at(rndAdj);                // Escolhe um adjacente de v1, denominado (v2)
        adj.clear();
        ind.getPtsAdjacentes(v2, adj);      // Obtem pontos adjacnetes a v2
        unsigned int tam =  adj.size();

        // Remove v1 da lista de adjacencia de v2
        unsigned int i = 0;
        while (i < tam) {
            if (adj.at(i) == v1) {
                adj.erase(adj.begin() + i);
                i = tam;
            }
            i++;
        }

        if (adj.size() > 0) {                       // Se v2 possui adjacencias
            ind.setGene(v1, v2, false);             // Desconecta v1 de v2
            rndAdj = rand() % adj.size();
            ind.setGene(v1, adj.at(rndAdj), true);  // Reconecta v1 a um vértice adjacente a v2
            efetuado++;
        }
    }
    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutConectaAdjHeuristico(Individuo &ind1) {
    // Escolhe um vértice v1, escolhe um de seus adjacentes diretos, denominado v2
    // Desconecta v1 de v2, e reconecta v1 ao ponto adjacente a v2 mais próximo de v1
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    unsigned int v1, v2;
    unsigned int qtdEfetuar = 1;//(qtdPtFixo * 10) / 100;
    unsigned int efetuado = 0;              // Se efetuou a mutação sob dois vértices
    while (efetuado < qtdEfetuar) {
        v1 = rand() % qtdPtFixo;            // Escolhe um item aleatório (v1)
        vector< unsigned int > adj;
        ind.getPtsAdjacentes(v1, adj);

        unsigned int rndAdj = rand() % adj.size();
        v2 = adj.at(rndAdj);                // Escolhe um adjacente de v1, denominado (v2)
        adj.clear();
        ind.getPtsAdjacentes(v2, adj);      // Obtem pontos adjacnetes a v2
        unsigned int tam =  adj.size();

        // Remove v1 da lista de adjacencia de v2
        unsigned int i = 0;
        while (i < tam) {
            if (adj.at(i) == v1) {
                adj.erase(adj.begin() + i);
                i = tam;
            }
            i++;
        }

        if (adj.size() > 0) {                       // Se v2 possui adjacencias
            // Encontra adjacente mais próximo
            unsigned int iMelhor = 0;
            double menorDist = ind.getDistancia(v1, adj.at(iMelhor));
            for (unsigned int iAdj = 1; iAdj < adj.size(); iAdj++) {
                double distancia = ind.getDistancia(v1, adj.at(iAdj));
                if (distancia < menorDist) {
                    iMelhor = iAdj;
                    menorDist = distancia;
                }
            }

            ind.setGene(v1, v2, false);                 // Desconecta v1 de v2
            ind.setGene(v1, adj.at(iMelhor), true);     // Reconecta v1 ao vértice adjacente a v2 mais próximo de v1
            efetuado++;
        }
    }
    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutConectaAdj2H(Individuo &ind1) {
    // Escolhe um vértice v1, escolhe um de seus adjacentes diretos, denominado v2
    // se v1 e v2 possuirem adjacentes, desconecta v1 de v2
    // Conecta algum adjacente de v1 à algum adjacente de v2
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    unsigned int v1, v2;
    unsigned int qtdEfetuar = 1;//(qtdPtFixo * 10) / 100;
    unsigned int efetuado = 0;              // Se efetuou a mutação sob dois vértices
    while (efetuado < qtdEfetuar) {
        vector< unsigned int > adjV1, adjV2;
        v1 = rand() % qtdPtFixo;            // Escolhe um item aleatório (v1)
        ind.getPtsAdjacentes(v1, adjV1);
        unsigned int rndAdj = rand() % adjV1.size();
        v2 = adjV1.at(rndAdj);                // Escolhe um adjacente de v1, denominado (v2)
        adjV1.erase(adjV1.begin() + rndAdj);
        if (adjV1.size() > 0) {
            ind.getPtsAdjacentes(v2, adjV2);
            for (unsigned int i = 0; i < adjV2.size(); i++) {
                if (adjV2.at(i) == v1) {
                    adjV2.erase(adjV2.begin() + i);
                    break;
                }
            }
            if (adjV2.size() > 0) {
                ind.setGene(v1, v2, false);

                unsigned int v1 = adjV1.at(0);
                unsigned int v2 = adjV2.at(0);
                double menorDist = ind.getDistancia(v1, v2);
                for (unsigned int i = 0; i < adjV1.size(); i++) {
                    for (unsigned int j = 0; j < adjV2.size(); j++) {
                        double distancia = ind.getDistancia(adjV1.at(i), adjV2.at(j));
                        if (distancia < menorDist) {
                            v1 = adjV1.at(i);
                            v2 = adjV2.at(j);
                            menorDist = distancia;
                        }
                    }
                }

                ind.setGene(v1, v2, true);
                efetuado++;
            }
        }
        adjV1.clear();
        adjV2.clear();
    }
    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutConectaAdjHeuristicoPlus(Individuo &ind1) {
    // Escolhe um vértice v1, escolhe um de seus adjacentes diretos, denominado v2
    // Desconecta v1 de v2, e reconecta v1 ao ponto adjacente a v2 mais próximo de v1
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    unsigned int qtdEfetuar = 1;//(qtdPtFixo * 10) / 100;
    unsigned int efetuado = 0;                  // Se efetuou a mutação sob dois vértices
    while (efetuado < qtdEfetuar) {
        unsigned int v1 = rand() % qtdPtFixo;   // Escolhe um item aleatório (v1)
        vector< unsigned int > adjV1;           // Adjacentes a V1
        ind.getPtsAdjacentes(v1, adjV1);

        double menorDist = 9999999999.9;
        unsigned int vlV2, vlV3;                // Menor Distância v1-v3

        unsigned int tam = adjV1.size();
        for (unsigned int i = 0; i < tam; i++) {
            unsigned int v2 = adjV1.at(i);
            vector< unsigned int > adjV2;           // Adjacentes a v2
            ind.getPtsAdjacentes(v2, adjV2);
            unsigned int tam2 = adjV2.size();
            for (unsigned int j = 0; j < tam2; j++) {
                unsigned int v3 = adjV2.at(j);
                if (v3 != v1) {
                    double dist = ind.getDistancia(v1, v3);
                    if (dist < menorDist) {
                        menorDist = dist;
                        vlV2 = v2;
                        vlV3 = v3;
                    }
                }
            }
        }

        ind.setGene(v1, vlV2, false);       // Desconecta v1 de v2
        ind.setGene(v1, vlV3, true);        // Reconecta v1 ao vértice adjacente a v2[] mais próximo de v1
        efetuado++;
    }
    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutGrau1Aleatorio(Individuo &ind1) {
    // Encontra um vértice com grau um, o desconecta e o liga em outro vértice
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    // Encontra o priméiro vértice de grau um
    unsigned int item1 = 0;
    vector< unsigned int > adj;
    ind.getPtsAdjacentes(item1, adj);
    while(adj.size() != 1) {
        item1++;
        adj.clear();
        ind.getPtsAdjacentes(item1, adj);
    }

    // Encontra um nó diferente do escolhido e do seu adjacente
    unsigned int item2 = rand() % qtdPtFixo;
    while ((item2 == item1) || (item2 == adj.at(0))) {
        item2 = rand() % qtdPtFixo;
    }

    // Desconecta item1 de seu adjacente e conecta a item2
    ind.setGene(item1, adj.at(0), false);
    ind.setGene(item1, item2, true);

    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

Individuo GA::setMutGrau1Heuristico(Individuo &ind1) {
    // Encontra um vértice com grau um, o desconecta e o liga em outro vértice
    Individuo ind = ind1;
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    vector<unsigned int> ponto;
    for(unsigned int i = 0; i < qtdPtFixo; i++) {
        ponto.push_back(i);
    }
    random_shuffle(ponto.begin(), ponto.end());

    // Encontra um vértice de grau um e seu adjacente
    vector< unsigned int > adj;
    unsigned int v1, v2;                                // Ponto e seu adjacente
    for(unsigned int i = 0; i < qtdPtFixo; i++) {
        unsigned int vlPt = ponto.at(i);
        adj.clear();
        ind.getPtsAdjacentes(vlPt, adj);
        if (adj.size() == 1) {
            v1 = vlPt;
            v2 = adj.at(0);
            break;
        }
    }
    ind.setGene(v1, v2, false);                         // Desconecta v1 de v2

    unsigned int vertMenor;                             // Vértice com menor distância à V1
    double menorDist = 9999999999.9;
    for (unsigned int i = 0; i < qtdPtFixo; i++) {
        if (i != v1 && i != v2) {                       // Não pegar distancia de v1 com v1 e v1 com v2
            double dist = ind.getDistancia(v1, i);
            if (dist < menorDist) {
                vertMenor = i;
                menorDist = dist;
            }
        }
    }
    ind.setGene(v1, vertMenor, true);                   // Conecta ao mais próximo

    /*Individuo indSMT = ind;
	this->criarArvoreSteiner(indSMT);
	ind.setFitness(indSMT.getFitness());*/
    return ind;
}

unsigned int GA::addPontoSteiner(Individuo &ind, unsigned int v1, unsigned int v2, unsigned int v3) {		// Private
	// Insere um ponto Steiner no ponto de Torricelli do triangulo formado por 3 vértices conectados
    // Triângulo é formado por: v1 conectado a v2 e a v3
    // Retorna índice do vértice inserido

    double steinerX, steinerY;       // Posição dos pontos Steiner
    double x1 = ind.getVertice(v1).getX(); double y1 = ind.getVertice(v1).getY();
    double x2 = ind.getVertice(v2).getX(); double y2 = ind.getVertice(v2).getY();
    double x3 = ind.getVertice(v3).getX(); double y3 = ind.getVertice(v3).getY();

    // Cria ponto Steiner
    Aux::getPtTorricelli(x1, y1, x2, y2, x3, y3, steinerX, steinerY);
    Vertice pontoSteiner(steinerX, steinerY);
    ind.addPontoSteiner(pontoSteiner);
    unsigned int ultimoPt = ind.getQtdPtTotal() - 1;			// Indice do ponto Steiner inserido

    // Retira a arestas que liga (v1 a v2) e (v1 a v3), e os liga ao ponto steiner
    ind.setGene(v1, v2, false);
    ind.setGene(v1, v3, false);
    ind.setGene(v1, ultimoPt, true);
    ind.setGene(v2, ultimoPt, true);
    ind.setGene(v3, ultimoPt, true);

    return ultimoPt;    // Retorna índice
}

void GA::remPontoSteiner(Individuo &ind, unsigned int s1, unsigned int v1, unsigned int v2, unsigned int v3) {		// Private
	// Remove arestas que ligam ponto Steiner e liga v1-v2, v1-v3
	// Remove ponto Steiner
    ind.setGene(s1, v1, false);
    ind.setGene(s1, v2, false);
    ind.setGene(s1, v3, false);
    ind.setGene(v1, v2, true);
    ind.setGene(v1, v3, true);
    ind.remPontoSteiner(s1);
}

void GA::criarArvoreSteiner(Individuo &ind, double prec) {
    unsigned int qtdPtFixo = ind.getQtdPtFixo();

    // Insere a quantidade máxima de vértices Steiner criando uma "Árvore de Steiner cheia"
    vector<unsigned int> adjacente;
	for (unsigned int i = 0; i < qtdPtFixo; i++) {
		adjacente.clear();
        ind.getPtsAdjacentes(i, adjacente);
        unsigned int tamAdj = adjacente.size();

        while (tamAdj > 1) {        // Se possuir grau > 1
            // Se possuir grau 2
            unsigned int iVert = 0;
            unsigned int jVert = 1;
            if (tamAdj > 2) {   // Se o grau for maior que 2
                // Busca pelo conjunto de vértices adjacentes com menor ângulo
                double menorAngulo = 6.28319;                // 360° em radianos
                for (unsigned int iAdj = 0; iAdj < tamAdj - 1; iAdj++) {
                    for (unsigned int jAdj = iAdj + 1; jAdj < tamAdj; jAdj++) {
                        double angulo = ind.getAngulo(i, adjacente[iAdj], adjacente[jAdj]);
                        if (angulo < menorAngulo) {
                            iVert = iAdj;
                            jVert = jAdj;
                            menorAngulo = angulo;
                        }
                    }
                }
            }
            // Adiciona ponto Steiner
            unsigned int ultimoPt = this->addPontoSteiner(ind, i, adjacente[iVert], adjacente[jVert]);
            adjacente.erase(adjacente.begin() + iVert); jVert--;
            adjacente.erase(adjacente.begin() + jVert);
            adjacente.push_back(ultimoPt);
            tamAdj--;
        }
	}
    // Reposiciona pontos, remove pontos desnecessários e calcula fitness
    this->reposicionaPontosSmith(ind, prec);              // Reposiciona pontos Steiner iterativamente
    //this->removePontosSobrepostos(ind);         // Remove pontos Steiner que estão sobre um ponto fixo
    //this->reposicionaPontos(ind);

    //ind.calcularFitness();
}

void GA::reposicionaPontosSmith(Individuo &ind, double prec) {
    unsigned int qtdPtFixo = ind.getQtdPtFixo();            // Indice inicial dos pontos Steiner
    unsigned int qtdPtSteiner = ind.getQtdPtSteiner();      // Quantidade de pontos Steiner

    // Cria lista de adjacência e distância dos pontos Steiner
    vector< vector<unsigned int> > lstAdj;                                  // Lista de Adjacência
    vector< vector< double > > lstDist(qtdPtSteiner, vector<double>(3));    // Lista de Distâncias

    unsigned int indicePt;
    vector<unsigned int> adjacente;
    for (unsigned int i = 0; i < qtdPtSteiner; i++) {
        indicePt = qtdPtFixo + i;
        adjacente.clear();
        ind.getPtsAdjacentes(indicePt, adjacente);
        lstAdj.push_back(adjacente);
    }

    double q = this->length(ind, lstAdj, lstDist);
    double r = this->error(ind, lstAdj, lstDist);
    do {
        this->optimize(ind, lstAdj, lstDist, prec * (r / qtdPtFixo));
        q = this->length(ind, lstAdj, lstDist);
        r = this->error(ind, lstAdj, lstDist);
    } while ( r > (q * prec));                          // Usar 0.01 para performance e 0.00001 para precisão

    ind.setFitness(q);
}

void GA::optimize(Individuo &ind, vector< vector<unsigned int> > &lstAdj, vector< vector< double > > &lstDist, double tol) {
    unsigned int qtdPtFixo = ind.getQtdPtFixo();            // Indice inicial dos pontos Steiner
    unsigned int qtdPtSteiner = ind.getQtdPtSteiner();      // Quantidade de pontos Steiner

    // 1°: Computa B array, C array, e valences. Configura o leafQ.
    double B[qtdPtSteiner][3];                      // Adjacentes
    double C[qtdPtSteiner][2];                      // X e Y
    unsigned int val[qtdPtSteiner], leafQ[qtdPtSteiner], lqp;
	unsigned int eqnstack[qtdPtSteiner], eqp;
	lqp = eqp = 0;

    for (unsigned int i = 0; i < qtdPtSteiner; i++) {
        double q[3];                                // Pontos Adjacentes
		q[0] = 1.0 / (lstDist[i][0] + tol);
		q[1] = 1.0 / (lstDist[i][1] + tol);
		q[2] = 1.0 / (lstDist[i][2] + tol);
		double soma = q[0] + q[1] + q[2];
		q[0] /= soma;
		q[1] /= soma;
		q[2] /= soma;

		val[i] = 0;
		B[i][0] = B[i][1] = B[i][2] = 0.0;          // Pontos Adjacentes
		C[i][0] = C[i][1] = 0.0;                    // X e Y

		for (unsigned int j = 0; j < 3; j++) {      // Adjacentes
            unsigned int adj = lstAdj[i][j];
            if (adj >= qtdPtFixo) { 	            // Se adj for um ponto Steiner
                val[i]++;
                B[i][j] = q[j];
            } else {                                // Se for um ponto fixo
                Vertice &ptAdj = ind.getVertice(adj);
                C[i][0] += ptAdj.getX() * q[j];
                C[i][1] += ptAdj.getY() * q[j];
            }
		}

		if (val[i] <= 1) {                          // Se for adjacente a dois ou mais Steiner
			leafQ[lqp] = i;                         // Insere folha em leafQ
			lqp++;                                  // Incrementa contador de folhas
		}
    }
    // Configurar equações para resolvê-las.
    // 2°: eliminar folhas
    while (lqp > 1) {
		lqp--;
		unsigned int i = leafQ[lqp];                // Indice do vértice para listas
		val[i]--;
		unsigned int i2 = i + qtdPtFixo;            // Indice do ponto Steiner

		// Elimina folha i
		eqnstack[eqp] = i;                          // Insere i na pilha
		eqp++;

		unsigned int j;
		for (j = 0; j < 3; j++) {
            if (B[i][j] != 0.0 && lstAdj[i][j] >= qtdPtFixo) break;              // Adjacente é j
		}
        if (j == 3) {
            for (j = 0; j < 3; j++) {
                if (lstAdj[i][j] >= qtdPtFixo) break;             // Adjacente é j
            }
        }

		double q0 = B[i][j];
		unsigned int j2 = lstAdj[i][j] - qtdPtFixo;               // Adjacente é j

		val[j2]--;
		if (val[j2] == 1) {
			leafQ[lqp] = j2;
			lqp++;
		}

		// Nova folha?
		unsigned int m;
		for (m = 0; m < 3; m++) {
            if (lstAdj[j2][m] == i2) break;
		}

		double q1 = B[j2][m];
		B[j2][m] = 0.0;
		double t = 1.0 - (q1 * q0);
		t = 1.0 / t;
		for (m = 0; m < 3; m++) {
            B[j2][m] *= t;
		}
		for (m = 0; m < 2; m++) {
			C[j2][m] += q1 * C[i][m];
			C[j2][m] *= t;
		}
	}

    // 3°: Resolve 1-vertex tree
	unsigned int i = leafQ[0];
	unsigned int i2 = i + qtdPtFixo;
    ind.getVertice(i2).setX(C[i][0]);
    ind.getVertice(i2).setY(C[i][1]);

    // 4°: Resolve novamente
	while (eqp > 0) {
		eqp--;
		unsigned int i = eqnstack[eqp];
		unsigned int i2 = i + qtdPtFixo;
		unsigned int j;
		for (j = 0; j < 3; j++) {
            if (B[i][j] != 0.0 && lstAdj[i][j] >= qtdPtFixo) break; // Adjacente é j
		}
		if (j == 3) {
            for (j = 0; j < 3; j++) {
                if (lstAdj[i][j] >= qtdPtFixo) break;               // Adjacente é j
            }
        }
		double q0 = B[i][j];
		j = lstAdj[i][j];                           // Adjacente é j
        Vertice &vertJ = ind.getVertice(j);
        double x = C[i][0] + q0 * vertJ.getX();
        double y = C[i][1] + q0 * vertJ.getY();
        ind.getVertice(i2).setX(x);
        ind.getVertice(i2).setY(y);
	}
}

double GA::error(Individuo &ind, vector< vector<unsigned int> > &lstAdj, vector< vector< double > > &lstDist) {
    unsigned int qtdPtFixo = ind.getQtdPtFixo();
    unsigned int qtdPtSteiner = ind.getQtdPtSteiner();

    double efig = 0.0;                                  // Erro
    double d12, d01, d02, r, s, t;
    unsigned int indicePtSt;
    for (unsigned int i = 0; i < qtdPtSteiner; i++) {
        indicePtSt = qtdPtFixo + i;                     // Indice do ponto Steiner
        Vertice &ptSt = ind.getVertice(indicePtSt);
        Vertice &adj0 = ind.getVertice(lstAdj[i][0]);
        Vertice &adj1 = ind.getVertice(lstAdj[i][1]);
        Vertice &adj2 = ind.getVertice(lstAdj[i][2]);

        d12 = d01 = d02 = 0.0;
        for (unsigned int eixo = 0; eixo < 2; eixo++) {    // X e Y
            t = ptSt.getPos(eixo);
            r = adj0.getPos(eixo) - t;
            s = adj1.getPos(eixo) - t;
            t = adj2.getPos(eixo) - t;
            d12 += s * t;
            d01 += r * s;
            d02 += r * t;
        }
        // Somente angulos < 120 causam erro
		t = d12 + d12 + (lstDist[i][1] * lstDist[i][2]);
		if (t > 0.0) efig += t;
		t = d01 + d01 + (lstDist[i][0] * lstDist[i][1]);
		if (t > 0.0) efig += t;
		t = d02 + d02 + (lstDist[i][0] * lstDist[i][2]);
		if (t > 0.0) efig += t;
    }
    efig = sqrt(efig);
    return (efig);
}

double GA::length(Individuo &ind, vector< vector<unsigned int> > &lstAdj, vector< vector< double > > &lstDist) {
    unsigned int qtdPtFixo = ind.getQtdPtFixo();
    unsigned int qtdPtSteiner = ind.getQtdPtSteiner();

    double distTot = 0.0;                                           // Distância total
    unsigned int indicePtSt, indicePtAdj;
    for (unsigned int i = 0; i < qtdPtSteiner; i++) {
        indicePtSt = qtdPtFixo + i;                                 // indice do Ponto Steiner
        for (unsigned int j = 0; j < 3; j++) {
            indicePtAdj = lstAdj[i][j];                             // Adjacente ao ponto Steiner

            if (indicePtAdj < indicePtSt) {
                double dist = ind.getDistancia(indicePtSt, indicePtAdj);
                distTot += dist;
                lstDist[i][j] = dist;                               // Insere dist em lista de distância

                if (indicePtAdj >= qtdPtFixo) {                     // Se adj for um ponto Steiner
                    indicePtAdj -= qtdPtFixo;                       // Indice no vetor de adjacencia e distância
                    for (unsigned int k = 0; k < 3; k++) {          // Busca ponto Steiner em adj
                        if (lstAdj[indicePtAdj][k] == indicePtSt) {
                            lstDist[indicePtAdj][k] = dist;         // Insere dist em lista de distância
                            break;
                        }
                    }
                }
            }
        }
    }
    return distTot;
}

void GA::reposicionaPontos(Individuo &ind) {
    // Reposiciona todos os pontos Steiner 1 vez
    unsigned int inicio = ind.getQtdPtFixo();               // Indice inicial dos Pontos Steiner
    unsigned int qtdPtSteiner = ind.getQtdPtSteiner();      // Quantidade de pontos Steiner

    // Cria lista de adjacências
    unsigned int indicePt;
    vector< vector<unsigned int> > lstAdj;                  // Lista de Adjacência
    for (unsigned int i = 0; i < qtdPtSteiner; i++) {
        vector<unsigned int> adjacente;
        indicePt = inicio + i;
        ind.getPtsAdjacentes(indicePt, adjacente);
        lstAdj.push_back(adjacente);
    }
    double steinerX, steinerY, x1, y1, x2, y2, x3, y3;       // Posição dos pontos Steiner

    // Reposiciona todos os pontos e cria lista com pontos Steiner que possuem adjacencia com outro ponto Steiner
    vector <unsigned int> pontosSt;
    for (unsigned int i = 0; i < qtdPtSteiner; i++) {
        x1 = ind.getVertice(lstAdj[i][0]).getX();   y1 = ind.getVertice(lstAdj[i][0]).getY();
        x2 = ind.getVertice(lstAdj[i][1]).getX();   y2 = ind.getVertice(lstAdj[i][1]).getY();
        x3 = ind.getVertice(lstAdj[i][2]).getX();   y3 = ind.getVertice(lstAdj[i][2]).getY();
        // Recalcula
        Aux::getPtTorricelli(x1, y1, x2, y2, x3, y3, steinerX, steinerY);
        indicePt = inicio + i;
        ind.getVertice(indicePt).setX(steinerX);
        ind.getVertice(indicePt).setY(steinerY);

        // Se possuir ponto Steiner adjacente, entra na lista para reposicionar iterativamente
        if (lstAdj[i][0] >= inicio || lstAdj[i][1] >= inicio || lstAdj[i][2] >= inicio) {
            pontosSt.push_back(i);      // Lista com pontos Steiner que possuem adjacencia a outro ponto Steiner
        }
	}

	// Reposiciona somente os pontos que são adjacentes a outro ponto Steiner
	unsigned int tam = pontosSt.size();
	for (unsigned int rep = 0; rep < 11; rep++) {
        for (unsigned int i = 0; i < tam; i++) {    // Percorre o vetor de pontos Steiner
            unsigned int s1 = pontosSt.at(i);
            x1 = ind.getVertice(lstAdj[s1][0]).getX();   y1 = ind.getVertice(lstAdj[s1][0]).getY();
            x2 = ind.getVertice(lstAdj[s1][1]).getX();   y2 = ind.getVertice(lstAdj[s1][1]).getY();
            x3 = ind.getVertice(lstAdj[s1][2]).getX();   y3 = ind.getVertice(lstAdj[s1][2]).getY();
            // Recalcula
            Aux::getPtTorricelli(x1, y1, x2, y2, x3, y3, steinerX, steinerY);
            indicePt = inicio + s1;
            ind.getVertice(indicePt).setX(steinerX);
            ind.getVertice(indicePt).setY(steinerY);
        }
    }
}

void GA::removePontosSobrepostos(Individuo &ind) {
    unsigned int qtdPtFixo = ind.getQtdPtFixo();
    // Remove os pontos Steiner que estão encima de um ponto fixo com grau menor que três
    unsigned int i = qtdPtFixo;             // Indice do primeiro ponto Steiner
    unsigned int j = ind.getQtdPtTotal();
    vector<unsigned int> adjacente;
    //double epsilon = 0.00001;
    while (i < j) {
        adjacente.clear();
        ind.getPtsAdjacentes(i, adjacente);
        // Descobre adjacente mais próximo ao Steiner
        double dist[3];
        for (unsigned int k = 0; k < 3; k++) {
            dist[k] = ind.getDistancia(i, adjacente.at(k));
        }
        int imenor = -1;
        double menorDist = 99999999999999;
        for (unsigned int k = 0; k < 3; k++) {
            if (dist[k] < menorDist && adjacente.at(k) < qtdPtFixo) {
                imenor = k;
                menorDist = dist[k];
            }
        }

        if (menorDist <= 0.00000000001 && imenor >= 0) {
            unsigned int v0, v1, v2;
            if (imenor == 0) {
                v0 = adjacente.at(0); v1 = adjacente.at(1), v2 = adjacente.at(2);
            } else if (imenor == 1) {
                v0 = adjacente.at(1); v1 = adjacente.at(0), v2 = adjacente.at(2);
            } if (imenor == 2) {
                v0 = adjacente.at(2); v1 = adjacente.at(0), v2 = adjacente.at(1);
            }
            this->remPontoSteiner(ind, i, v0, v1, v2);
            j--;
        } else {
            i++;
        }

        /*double sx = ind.getVertice(i).getX();              double sy = ind.getVertice(i).getY();
        double x1 = ind.getVertice(adjacente[0]).getX();   double y1 = ind.getVertice(adjacente[0]).getY();
        double x2 = ind.getVertice(adjacente[1]).getX();   double y2 = ind.getVertice(adjacente[1]).getY();
        double x3 = ind.getVertice(adjacente[2]).getX();   double y3 = ind.getVertice(adjacente[2]).getY();

        if ((fabs(sx - x1) < epsilon && fabs(sy - y1) < epsilon) && (adjacente[0] < qtdPtFixo)) {                     // Se o ponto estiver encima de um ponto fixo
            this->remPontoSteiner(ind, i, adjacente[0], adjacente[1], adjacente[2]);
            j--;
        } else if ((fabs(sx - x2) < epsilon && fabs(sy - y2) < epsilon) && (adjacente[1] < qtdPtFixo)) {
            this->remPontoSteiner(ind, i, adjacente[1], adjacente[0], adjacente[2]);
            j--;
        } else if ((fabs(sx - x3) < epsilon && fabs(sy - y3) < epsilon) && (adjacente[2] < qtdPtFixo)) {
            this->remPontoSteiner(ind, i, adjacente[2], adjacente[0], adjacente[1]);
            j--;
        } else {
            i++;
        }*/
    }
}

string GA::getLog() {
    return this->log;
}
