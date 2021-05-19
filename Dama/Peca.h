#pragma once
#include "Ponto.h"
#include "Peca.h"
#include <iostream>

using namespace std;

class Peca
{
private:
	Ponto P;
	char forma;
	char formaDama;
	bool Dama; 
public:
	Peca();
	~Peca();
	
	void setPonto(Ponto _P) { P = _P; }
	void setCoordenadas(int x, int y) { P.setX(x); P.setY(y); }
	void setDama(bool value) { Dama = value; }
	void setForma(char value) { forma = value; }
	char getForma() { return forma; }
	char getFormaDama();
	bool getDama() { return Dama; }


	Ponto getPonto() { return P; }
	int getX() { return P.getX(); }
	int getY() { return P.getY(); }

};

