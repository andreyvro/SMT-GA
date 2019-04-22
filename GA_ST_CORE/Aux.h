#ifndef AUX_H
#define AUX_H

#include <cmath>
#include <iostream>
#include <fstream>
#include "Vertice.h"

using namespace std;

class Aux {
    private:
        Aux();
    public:
        static double doubleRand();
        static void setTitulo();
        static void setModoUso();
        static void setArqSaida(string arquivo, string texto);

        static const double ang120;                              // Valor de 120º em radianos
        // Retorna distância euclidiana entre dois pontos
        static double getDistancia(const double &x1, const double &y1, const double &x2, const double &y2);
        // Retorna ângulo que se forma no primeiro vértice informado nos parâmetros
        static double getAngulo(const double &x1, const double &y1,
                               const double &x2, const double &y2,
                               const double &x3, const double &y3);
        // Retorna ponto de Torricelli
        static void getPtTorricelli(const double &x1, const double &y1,
                                    const double &x2, const double &y2,
                                    const double &x3, const double &y3,
                                    double &retX, double &retY);
        static int orientacao(const double &x1, const double &y1,
                              const double &x2, const double &y2,
                              const double &x3, const double &y3);
        static void criarTrianguloEquilatero(const double &x1, const double &y1,
                                             const double &x2, const double &y2,
                                             double &x3, double &y3);
        static void pontoDeInterseccao(const double &x1, const double &y1, const double &x2, const double &y2,
                                       const double &x3, const double &y3, const double &x4, const double &y4,
                                       double &ix, double &iy);
};

#endif // AUX_H
