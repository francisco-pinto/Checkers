#include "pch.h"
#include "Jogador.h"

using namespace std;

Jogador::Jogador()
{
	
}

Jogador::~Jogador()
{
}

void Jogador::gotoxy(int PosX, int PosY)
{
	COORD c = { PosX,PosY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Ponto Jogador::AskPosicao(int InicioFim, Tabuleiro Tab)
{
	gotoxy(95, 40);

	if (InicioFim == 1) {
		cout << "Escolha a peca inicial";
	}
	else {
		cout << "Escolha a posicao final da peca";
	}
	
	Pos.AskPosition();
	return Pos; 
}
