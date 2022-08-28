#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "Peca.h"
#include "Utilizadores.h"
#include "Tabuleiro.h"

/*Jogador 1 - Peças acima
  Jogador 2 - Peças abaixo*/

using namespace std;

class Jogador:
	public Utilizadores
{
private:
	Ponto Pos;
	
public:
	Jogador();
	 ~Jogador();

	 Ponto AskPosicao(int InicioFim, Tabuleiro Tab);	

private:
	void gotoxy(int PosX, int PosY);
};


