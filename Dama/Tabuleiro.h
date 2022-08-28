#pragma once
#include "Peca.h"

class Tabuleiro
{
private:
	int x = 8, y = 4;
	char Tab[8][8];
	char auxDesign[8][8];
public:
	Tabuleiro();
	~Tabuleiro();

	void Show();
	void RetiraComida(Ponto Comida);
	void AlteraPosicoes(Ponto Inicial, Ponto Final, char value);
	void ValorInicial(Ponto P, char value);
	
	void setValue(Ponto P, char value){ Tab[(P.getX() - 1)][(P.getY() - 1)] = value; }
	char getValue(Ponto P) { return Tab[(P.getX() - 1)][(P.getY() - 1)]; }
	char getValue(int _x, int _y) { return Tab[_x - 1][_y - 1]; }

private:
	void geraMargem();
	void ColunaMargem(int PosX, int PosY);
	void LinhaMargem(int PosX, int PosY);
	void geraTabuleiro();
	void Quadrado(int x, int y, int altura, int largura);
	void geraPeca(int color, int PosX, int PosY);
	void gotoxy(int PosX, int PosY);
	void showPecas();
	void DesenhaPeca(int PosX, int PosY, int xi, int yi);
	void FormaPeca(int altura, int largura, int PosX, int PosY);
	void geraPecaDama(int color, int PosX, int PosY);
};

