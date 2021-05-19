#include "pch.h"
#include "Bot.h"


Bot::Bot()
{
	index = 0;
	indexF = 0;
}

Bot::~Bot()
{
}

Ponto Bot::EscolhePecaAleatoria(Tabuleiro Tab) {

	int numPeca = 0;
	
	VerificaPossiveisJogadas(Tab);
	/*Ciclo garante que não
	passamos nenhuma posição 
	inválida*/
	do {
		srand(time(NULL));
		numPeca = rand() % index;
		PontoInicial = PIDisponiveis[numPeca];
		PontoFinal = PFDisponiveis[numPeca];
	} while (PIDisponiveis[numPeca].getX() == 0 && PFDisponiveis[numPeca].getX() == 0);
			
	return PontoInicial;
}

void Bot::JogaCimaDireita(int i, Tabuleiro Tab) {
	
	if (getSentido() == 'c') {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() + 1, getPeca(i).getY() - 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
						
			PFDisponiveis[index].setPonto(getPeca(i).getX() + 1, getPeca(i).getY() - 1);
			index++;
		}
	}
	else if (getPeca(i).getDama()) {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() + 1, getPeca(i).getY() - 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
					
			PFDisponiveis[index].setPonto(getPeca(i).getX() + 1, getPeca(i).getY() - 1);
			index++;
		}
	}
}

void Bot::JogaCimaEsquerda(int i, Tabuleiro Tab) {
	
	if (getSentido() == 'c') {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() - 1, getPeca(i).getY() - 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
			
			PFDisponiveis[index].setPonto(getPeca(i).getX() - 1, getPeca(i).getY() - 1);
			index++;
		}
	}
	else if (getPeca(i).getDama()) {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() - 1, getPeca(i).getY() - 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
			
			PFDisponiveis[index].setPonto(getPeca(i).getX() - 1, getPeca(i).getY() - 1);
			index++;
		}
	}
}

void Bot::JogaBaixoDireita(int i, Tabuleiro Tab) {
	
	if (getSentido() == 'b') {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() + 1, getPeca(i).getY() + 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
			
			PFDisponiveis[index].setPonto(getPeca(i).getX() + 1, getPeca(i).getY() + 1);
			index++;
		}
	}
	else if (getPeca(i).getDama()) {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() + 1, getPeca(i).getY() + 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
			
			PFDisponiveis[index].setPonto(getPeca(i).getX() + 1, getPeca(i).getY() + 1);
			index++;
		}
	}
}

void Bot::JogaBaixoEsquerda(int i, Tabuleiro Tab) {
	
	if (getSentido() == 'b') {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() - 1, getPeca(i).getY() + 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
			
			PFDisponiveis[index].setPonto(getPeca(i).getX() - 1, getPeca(i).getY() - 1);
			index++;
		}
	}
	else if (getPeca(i).getDama()) {
		if (Tab.getValue(getPeca(i).getX(), getPeca(i).getY()) == getForma() && Tab.getValue(getPeca(i).getX() - 1, getPeca(i).getY() + 1) == ' ') {
			PIDisponiveis[index] = getPeca(i).getPonto();
		
			PFDisponiveis[index].setPonto(getPeca(i).getX() - 1, getPeca(i).getY() + 1);
			index++;
		}
	}
}

void Bot::VerificaPossiveisJogadas(Tabuleiro Tab)
{
	for (int i = 0; i < 12; i++) {
		JogaCimaEsquerda(i, Tab);
		JogaCimaDireita(i, Tab);
		JogaBaixoEsquerda(i, Tab);
		JogaBaixoDireita(i, Tab);
	}
}

void Bot::LimparPossibilidades() {

	for (int i = 0; i < 12; i++) {
		PIDisponiveis[i].setPonto(0, 0);
		PFDisponiveis[i].setPonto(0, 0);
	}
	
	

	index = 0;

}

Ponto Bot::AskPosicao(int InicioFim, Tabuleiro Tab)
{
	/*Se 1 - Joga Posição inicial
		 2 - Joga Posição final
		 3 - Joga Dupla comer*/

	Sleep(1500);

	if (InicioFim == 1) {
		if (getPosInicialObrigatoria1().getX() != 0) {
			return getPosInicialObrigatoria1();
		}
		
		return EscolhePecaAleatoria(Tab);
	}
	else if (InicioFim == 2) {
		if (getPosFinalObrigatoria1().getX() != 0) {
			LimparPossibilidades();
			return getPosFinalObrigatoria1();
		}
		else {
			//Limpa o vetor que contem as possibilidades
			LimparPossibilidades();
			return PontoFinal;
		}
	}
	else {
		if (getPosFinalObrigatoria1().getX() != 0) {
			return getPosFinalObrigatoria1();
		}
	}
}

