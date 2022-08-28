#include "pch.h"
#include "Tabuleiro.h"
#include "Peca.h"
#include "Ponto.h"
#include <iostream>

using namespace std;

Tabuleiro::Tabuleiro()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Tab[j][i] = ' ';
		}
	}
}

Tabuleiro::~Tabuleiro()
{
}

void Tabuleiro::FormaPeca(int altura, int largura, int PosX, int PosY) {
	
	for (int j = 0; j < largura + 2; j++) {
		for (int i = 0; i < altura; i++) {
			gotoxy(PosX + j, PosY + i);
			cout << char(219);
		}
	}


	//Muda a cor da linha para representar a dama
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);

}

void Tabuleiro::geraPecaDama(int color, int PosX, int PosY) {

	//Desenha Quadrado
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

	FormaPeca(2, 4, PosX, PosY);

	//Desenha risca que distingue dama da outra peça
	SetConsoleTextAttribute(hConsole, 16);
	for (int j = 2; j < 4; j++) {
		for (int i = 0; i < 2; i++) {
			gotoxy(PosX + j, PosY + i);
			cout << char(219);
		}
	}
	
	SetConsoleTextAttribute(hConsole, 15);
}

void Tabuleiro::geraPeca(int color, int PosX, int PosY) {

	//Desenha Quadrado
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

	FormaPeca(2, 4, PosX, PosY);

	SetConsoleTextAttribute(hConsole, 15);
}

void Tabuleiro::DesenhaPeca(int PosX, int PosY, int xi, int yi) {
	
	//Forma Normal
	if (Tab[xi][yi] == 'o') {
		geraPeca(246, PosX, PosY);
	}else if (Tab[xi][yi] == 'x') {
		geraPeca(244, PosX, PosY);
	}
			

	//Forma Dama
	if (Tab[xi][yi] == 'O') {
		geraPecaDama(246, PosX, PosY);
	}else if (Tab[xi][yi] == 'X') {
		geraPecaDama(244, PosX, PosY);
	}
}

void Tabuleiro::showPecas() {

	int PosX = 10, PosY = 5, k = 0;
	int xi = 0, yi = 0;				//Coordenadas do tabuleiro
	
	do {
		
		DesenhaPeca(PosX, PosY, xi, yi);

		xi++;
		PosX += 10;
		k++;

		if (k == 8) {
			PosY += 5;
			PosX = 10;
			
			k = 0;
			
			yi++;
			xi = 0;
		}
	
	} while (xi < 8 && yi < 8);

}

void Tabuleiro::Show()
{
	int i = 0, j = 0, k = 0;
	
	//Compor funçao showpecas

	geraTabuleiro();
	geraMargem();
	showPecas();

	//Design básico com linhas

	//Peças e interior do tabuleiro
	//for (i = 0; i < 8; i++) {
	//	for (j = 0; j < 8; j++) {
	//		cout << "| " << Tab[j][i];
	//	}
	//	cout << "|" << "\n";
	//	for (k = 0; k < 8; k++) {
	//		cout << "---";
	//	}
	//	cout << "\n";
	//}
}

void Tabuleiro::RetiraComida(Ponto Comida) {
	
	Tab[Comida.getX() - 1][Comida.getY() - 1] = ' ';
}

void Tabuleiro::AlteraPosicoes(Ponto Inicial, Ponto Final, char value) {
	Tab[Inicial.getX() - 1][Inicial.getY() - 1] = ' ';
	Tab[Final.getX() - 1][Final.getY() - 1] = value;
}

void Tabuleiro::ValorInicial(Ponto P, char value)
{
	Tab[P.getX() - 1][P.getY() - 1] = value;
}

void Tabuleiro::geraMargem() {

	int	PosX = x - 2;
	int PosY = y - 7;

	//Cores da consola. Muda para amarelo
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);

	LinhaMargem(PosX, PosY);
	ColunaMargem(PosX, PosY);

	//Cores da consola. Muda para Branco
	SetConsoleTextAttribute(hConsole, 15);

}

void Tabuleiro::ColunaMargem(int PosX, int PosY) {

	int i = 0, j = 0;
	int PosXEsquerda = PosX;
	int PosXDireita = PosX + 83;

	//Coluna Esquerda
	for (int j = 0; j < 8; j++) {
		gotoxy(PosXEsquerda - 3, (PosY + 4) + 5 * j);
		cout << j + 1;
	}

	for (i = 0; i < 44; i++) {
		gotoxy(PosXEsquerda, PosY + i);
		cout << char(219);

		gotoxy(PosXEsquerda - 1, PosY + i);
		cout << char(219);
	}

	//Coluna Direita
	for (j = 0; j < 44; j++) {
		gotoxy(PosXDireita, PosY + j);
		cout << char(219);

		gotoxy(PosXDireita + 1, PosY + j);
		cout << char(219);
	}
}

void Tabuleiro::LinhaMargem(int PosX, int PosY) {

	int i = 0, j = 0;

	int PosYCima = PosY;
	int PosYBaixo = PosY + 43;

	//Mudar cor

	//Linha cima
	for (int j = 0; j < 8; j++) {
		gotoxy(12 + 10 * j, PosYCima - 1);
		cout << char(65 + j);
	}

	for (i = 0; i < 84; i++) {
		gotoxy(PosX + i, PosYCima);
		cout << char(219);
	}

	//Linha baixo
	for (j = 0; j < 84; j++) {
		gotoxy(PosX + j, PosYBaixo);
		cout << char(219);
	}

}

void Tabuleiro::geraTabuleiro() {

	for (int linha = 0; linha < 8; linha++) {
		for (int coluna = 0; coluna < 4; coluna++) {
			if (linha % 2 == 0) {
				y = 4;
			}
			else {
				y = 9;
			}
			Quadrado(x + linha * 10, y + coluna * 10, 5, 10);
		}
	}
}

void Tabuleiro::Quadrado(int x, int y, int altura, int largura) {

	gotoxy(x, y);

	for (int j = 0; j < largura; j++) {
		for (int i = 0; i < altura; i++) {
			gotoxy(x + j, y + i);
			cout << char(219);
		}
	}
}

void Tabuleiro::gotoxy(int PosX, int PosY)
{
	COORD c = { PosX,PosY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
