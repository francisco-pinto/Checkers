#pragma once
#include "Jogador.h"
#include "Bot.h"
#include "Tabuleiro.h"
#include "Peca.h"
#include "Utilizadores.h"
#include <conio.h>

class Jogo
{
private:
	Utilizadores *J[2];
	Tabuleiro Tab;
	int aJogar;

public:
	Jogo();
	~Jogo();

	void Movimento(int aJogar);
	void Jogadas();
	void End();
	void Start();

private:
	void InicializaJogadores(int escolha);
	void DadosJogador();
	void EscolhePosInicial(bool obrigaComer, Ponto &Inicial, Ponto * InicialObrigatorio);
	void EscolhePosFinal(bool obrigaComer, Ponto &Final, Ponto &Inicial, Ponto * FinalObrigatorio);
	void ComerNovamente(bool obrigaComer, Ponto &Final, Ponto &Inicial, Ponto * FinalObrigatorio);
	int Opcao();
	void Informacoes(bool ObrigaComer);

	int EscolhePrimeiroAJogar();
	int TrocaJogador();

	bool ComeDuas(Ponto Final, Ponto *FinalObrigatorio);
	bool ObrigatorioComer(Ponto *InicialObrigatorio, Ponto *FinalObrigatorio, Ponto &Comida);
	bool MoveCimaEsquerda(Ponto Inicial, Ponto Final);
	bool MoveCimaDireita(Ponto Inicial, Ponto Final);
	bool MoveBaixoEsquerda(Ponto Inicial, Ponto Final);
	bool MoveBaixoDireita(Ponto Inicial, Ponto Final);
	bool MovimentoDiagonal(Ponto Inicial, Ponto Final);
	bool sentidoErrado(Ponto Inicial, Ponto Final);
	bool MovimentoImpossivel(Ponto Inicial, Ponto Final, bool obrigaComer);

	bool PosicaoInicialErrada(Ponto P, Ponto *Obrigatoria, bool obrigaComer);
	bool ReiniciaTabuleiro();
	bool PosicaoFinalErrada(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool obrigaComer);
	bool RestricoesIniciais(Ponto Inicial, Ponto *InicialObrigatorio, bool obrigaComer);
	bool PosicaoFinalDamaErrada(Ponto Inicial, Ponto Final, Ponto * FinalObrigatorio, bool obrigaComer);
	bool RestricoesFinais(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool obrigaComer);
	
	void Atualiza(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool ObrigaComer);
	bool Vencedor();
	void gotoxy(int PosX, int PosY);
	void DesenhaQuadradoIdentificador();
};

