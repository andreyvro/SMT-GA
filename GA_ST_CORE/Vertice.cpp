#include "Vertice.h"

Vertice::Vertice(double x, double y) {
	this->x = x;
	this->y = y;
}

void Vertice::setX(double x) {
	this->x = x;
}

void Vertice::setY(double y) {
	this->y = y;
}

const double Vertice::getX() {
	return this->x;
}

const double Vertice::getY() {
	return this->y;
}

const double Vertice::getPos(unsigned int indice) {
    if (indice == 0) {
        return this->x;
    } else {
        return this->y;
    }
}
