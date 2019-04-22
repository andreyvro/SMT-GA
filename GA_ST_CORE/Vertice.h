#ifndef VERTICE_H
#define VERTICE_H

using namespace std;

class Vertice {
	private:
		double x;				// Posição X
		double y;				// Posição Y
	public:
		Vertice(double x, double y);
		void setX(double x);
		void setY(double y);
		const double getX();
		const double getY();
		const double getPos(unsigned int indice);
};

#endif // VERTICE_H
