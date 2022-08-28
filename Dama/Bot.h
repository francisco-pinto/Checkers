#pragma once
#include <time.h>
#include "Utilizadores.h"
#include "Peca.h"
#include "Tabuleiro.h"

class Bot :
	public Utilizadores
{
private:
	Ponto Pos;
	Ponto PontoInicial;
	Ponto PontoFinal;
	Ponto PIDisponiveis[12];
	Ponto PFDisponiveis[12];
	int index;
	int indexF;

public:
	Bot();
	~Bot();

	Ponto AskPosicao(int InicioFim, Tabuleiro Tab);

private:
	Ponto EscolhePecaAleatoria(Tabuleiro Tab);

	void JogaCimaDireita(int i, Tabuleiro Tab);
	void JogaCimaEsquerda(int i, Tabuleiro Tab);
	void JogaBaixoDireita(int i, Tabuleiro Tab);
	void JogaBaixoEsquerda(int i, Tabuleiro Tab);

	void VerificaPossiveisJogadas(Tabuleiro Tab);

	void LimparPossibilidades();

};

