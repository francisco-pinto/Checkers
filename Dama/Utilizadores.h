#pragma once
#include "Ponto.h"
#include "Peca.h"
#include "Tabuleiro.h"

class Utilizadores
{
private:
	int numJogador;
	string nome;
	int valor; //Valor aleatório, para atribuir peças aleatoriamente
	int numPecasComida;
	char sentido;
	char formaInimiga;
	char formaInimigaDama;
	char forma;
	char formaDama;
	string corPeca;
	bool bot;
	Peca P[12];

	Ponto PosIObriga[2];
	Ponto PosFObriga[2];
	Ponto PosPecaComida[2];

	Ponto PosIObrigaDama[4];
	Ponto PosFObrigaDama[4];
	Ponto PosPecaComidaDama[4];
public:
	 Utilizadores();
	 ~Utilizadores();

	void setNome(string _nome) { nome = _nome; }
	void setNumero(int num) { numJogador = num; }
	void setFormaInimiga();
	void setFormaDama();
	void setForma(char _forma) { forma = _forma; }
	void setBot(bool B) { bot = B; }

	string getNome() { return nome; }
	char getForma() { return forma; }
	char getFormaDama() { return formaDama; }
	char getFormaInimiga() { return formaInimiga; }
	char getSentido() { return sentido; }
	int getNumPecasComidas() { return numPecasComida; }
	void setNumPecasComidas(int num) { numPecasComida = num; }
	bool getBot() { return bot; }
	Peca getPeca(int n) { return P[n]; }

	void Inicializar(int num, Tabuleiro & Tab);
	void PecaPosition();
	void PreenchePeca();
	void PosicaoTabuleiro(Tabuleiro & Tab);

	string getCorPeca() { return corPeca; }

	Ponto getPosComida1() { return PosPecaComida[0]; }
	Ponto getPosInicialObrigatoria1() { return PosIObriga[0]; }
	Ponto getPosFinalObrigatoria1() { return PosFObriga[0]; }

	Ponto getPosComida2() { return PosPecaComida[1]; }
	Ponto getPosInicialObrigatoria2() { return PosIObriga[1]; }
	Ponto getPosFinalObrigatoria2() { return PosFObriga[1]; }

	//Posções da dama
	Ponto getPosComidaDama1() { return PosPecaComidaDama[0]; }
	Ponto getPosInicialObrigatoriaDama1() { return PosIObrigaDama[0]; }
	Ponto getPosFinalObrigatoriaDama1() { return PosFObrigaDama[0]; }

	Ponto getPosComidaDama2() { return PosPecaComidaDama[1]; }
	Ponto getPosInicialObrigatoriaDama2() { return PosIObrigaDama[1]; }
	Ponto getPosFinalObrigatoriaDama2() { return PosFObrigaDama[1]; }
	Ponto getPosPeca(int value) { return P[value].getPonto(); }
	
	Ponto getPosComidaDama3() { return PosPecaComidaDama[2]; }
	Ponto getPosInicialObrigatoriaDama3() { return PosIObrigaDama[2]; }
	Ponto getPosFinalObrigatoriaDama3() { return PosFObrigaDama[2]; }

	Ponto getPosComidaDama4() { return PosPecaComidaDama[3]; }
	Ponto getPosInicialObrigatoriaDama4() { return PosIObrigaDama[3]; }
	Ponto getPosFinalObrigatoriaDama4() { return PosFObrigaDama[3]; }

	void ReiniciaPosicoesObrigatorias();

	virtual Ponto AskPosicao(int InicioFim, Tabuleiro Tab) = 0;

	bool Obrigatorio(Tabuleiro Tab);
	bool checkIfPecaDama(Ponto Ponto);
	bool ObrigatorioDama(Tabuleiro Tab);

	void EliminaPeca();
	void AlteraPosicoes(Ponto Inicial, Ponto Final);
	int checkDama();
	bool ComeDuas(Tabuleiro Tab, Ponto Pos);
	bool ComeDuasDama(Tabuleiro Tab, Ponto Pos);
	int checkDamaPos(Ponto Pos);

private:
	void setCorPeca();

	bool ComeCimaDireita(Tabuleiro Tab, bool *comeu, int numPeca);
	bool ComeCimaEsquerda(Tabuleiro Tab, bool *comeu, int numPeca);
	bool ComeBaixoDireita(Tabuleiro Tab, bool *comeu, int numPeca);
	bool ComeBaixoEsquerda(Tabuleiro Tab, bool *comeu, int numPeca);
	
	
};

