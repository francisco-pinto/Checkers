#include "pch.h"
#include "Utilizadores.h"

Utilizadores::Utilizadores()
{
	numPecasComida = 0;
	
	if (bot) {
		nome = "Bot";
	}
}

void Utilizadores::setFormaInimiga()
{
	if (forma == 'x') {
		formaInimiga = 'o';
		formaInimigaDama = 'O';
	}
	else {
		formaInimiga = 'x';
		formaInimigaDama = 'X';
	}

}

void Utilizadores::setFormaDama()
{
	if (forma == 'x') {
		formaDama = 'X';
	}
	else {
		formaDama = 'O';
	}
}

void Utilizadores::Inicializar(int num, Tabuleiro &Tab)
{
	setNumero(num);
	PreenchePeca();
	PecaPosition();
	PosicaoTabuleiro(Tab);
	setCorPeca();
}

void Utilizadores::PecaPosition()
{
	int x = 1, y = 1;
	int j = 0, i = 0, k = 0;

	//Atribuir valores iniciais aos Pontos

	if (numJogador == 1) {
		sentido = 'b';
		do {
			P[i].setCoordenadas(2 * k + x, y);

			if (i == 3) {
				x = 2;
				y = 2;
				k = 0;
			}
			else if (i == 7) {
				x = 1;
				y = 3;
				k = 0;
			}
			else {
				k++;
			}

			i++;
		} while (i < 12);
	}
	else {
		sentido = 'c';
		i = 0;
		x = 2, y = 8;

		do {
			P[i].setCoordenadas(2 * k + x, y);

			if (i == 3) {
				x = 1;
				y = 7;
				k = 0;
			}
			else if (i == 7) {
				x = 2;
				y = 6;
				k = 0;
			}
			else {
				k++;
			}

			i++;
		} while (i < 12);
	}
}

void Utilizadores::PreenchePeca()
{
	if (forma == 'x') {
		//Forma das Peças 
		for (int i = 0; i < 12; i++) {
			P[i].setForma('x');
		}
	}
	else {
		//Forma das Peças 
		for (int i = 0; i < 12; i++) {
			P[i].setForma('o');
		}
	}
}

void Utilizadores::PosicaoTabuleiro(Tabuleiro &Tab)
{
	for (int i = 0; i < 12; i++) {
		Tab.ValorInicial(P[i].getPonto(), P[i].getForma());
	}
}

void Utilizadores::ReiniciaPosicoesObrigatorias()
{	
	for (int i = 0; i < 2; i++) {
		PosPecaComida[i].setPonto(0, 0);
		PosIObriga[i].setPonto(0, 0);
		PosFObriga[i].setPonto(0, 0);

		PosPecaComidaDama[i].setPonto(0, 0);
		PosIObrigaDama[i].setPonto(0, 0);
		PosFObrigaDama[i].setPonto(0, 0);
	}
}

bool Utilizadores::Obrigatorio(Tabuleiro Tab) {

	bool comeu = false;

	if (sentido == 'c') {
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (Tab.getValue(i, j) == getForma() && (Tab.getValue(i + 1, j - 1) == formaInimiga || Tab.getValue(i + 1, j - 1) == formaInimigaDama) && Tab.getValue(i + 2, j - 2) == ' ' && (i != 0 && j != 0)) {

					//Opção de comer uma peça ou outra
					if (comeu) {
						PosIObriga[1].setPonto(i, j);
						PosFObriga[1].setPonto(i + 2, j - 2);
						PosPecaComida[1].setPonto(i + 1, j - 1);
					}
					else {
						PosIObriga[0].setPonto(i, j);
						PosFObriga[0].setPonto(i + 2, j - 2);
						PosPecaComida[0].setPonto(i + 1, j - 1);
					}

					comeu = true;
				}
				else if (Tab.getValue(i, j) == getForma() && (Tab.getValue(i - 1, j - 1) == formaInimiga || Tab.getValue(i - 1, j - 1) == formaInimigaDama) && Tab.getValue(i - 2, j - 2) == ' ' && (i != 0 && j != 0)) {

					if (comeu)
					{
						PosIObriga[1].setPonto(i, j);
						PosFObriga[1].setPonto(i - 2, j - 2);
						PosPecaComida[1].setPonto(i - 1, j - 1);
					}
					else {
						PosIObriga[0].setPonto(i, j);
						PosFObriga[0].setPonto(i - 2, j - 2);
						PosPecaComida[0].setPonto(i - 1, j - 1);
					}

					comeu = true;
				}
			}
		}
	}
	else {
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (Tab.getValue(i, j) == getForma() && (Tab.getValue(i + 1, j + 1) == formaInimiga || Tab.getValue(i + 1, j + 1) == formaInimigaDama) && Tab.getValue(i + 2, j + 2) == ' ' && (i != 0 && j != 0)) {

					if (comeu) {
						PosIObriga[1].setPonto(i, j);
						PosFObriga[1].setPonto(i + 2, j + 2);
						PosPecaComida[1].setPonto(i + 1, j + 1);
					}
					else {
						PosIObriga[0].setPonto(i, j);
						PosFObriga[0].setPonto(i + 2, j + 2);
						PosPecaComida[0].setPonto(i + 1, j + 1);
					}

					comeu = true;
				}
				else if (Tab.getValue(i, j) == getForma() && (Tab.getValue(i - 1, j + 1) == formaInimiga || Tab.getValue(i - 1, j + 1) == formaInimigaDama) && Tab.getValue(i - 2, j + 2) == ' ' && (i != 0 && j != 0)) {

					if (comeu) {
						PosIObriga[1].setPonto(i, j);
						PosFObriga[1].setPonto(i - 2, j + 2);
						PosPecaComida[1].setPonto(i - 1, j + 1);
					}
					else {
						PosIObriga[0].setPonto(i, j);
						PosFObriga[0].setPonto(i - 2, j + 2);
						PosPecaComida[0].setPonto(i - 1, j + 1);
					}

					comeu = true;
				}
			}
		}
	}

	//Erro de peça comer para fora matriz
	if (comeu && (((PosFObriga[0].getX() != 0 && PosFObriga[0].getY() == 0) || (PosFObriga[0].getX() == 0 && PosFObriga[0].getY() != 0)) || ((PosFObriga[1].getX() != 0 && PosFObriga[1].getY() == 0) || (PosFObriga[1].getX() == 0 && PosFObriga[1].getY() != 0)) || (PosFObriga[0].getX() != 0 && PosFObriga[0].getY() == 9) || (PosFObriga[0].getX() != 0 && PosFObriga[0].getY() == 9))) {
		return false;
	}
	else if (comeu) {
		return true;
	}

	return false;
}

bool Utilizadores::checkIfPecaDama(Ponto Ponto)
{
	for (int i = 0; i < 12; i++) {
		if (P[i].getPonto() == Ponto) {
			if (P[i].getDama()) {
				return true;
			}
		}
	}

	return false;
}

bool Utilizadores::ObrigatorioDama(Tabuleiro Tab)
{
	bool comeu[3] = { false, false, false };

	for (int i = 0; i < 12; i++) {
		if (P[i].getDama()) {
			ComeCimaDireita(Tab, comeu, i);
			ComeCimaEsquerda(Tab, comeu, i);
			ComeBaixoDireita(Tab, comeu, i);
			ComeBaixoEsquerda(Tab, comeu, i);
		}
	}

	//Erro de peça comer para fora matriz
	if ((comeu[0] || comeu[1] || comeu[2])  && (((PosFObrigaDama[0].getX() != 0 && PosFObrigaDama[0].getY() == 0) || (PosFObrigaDama[0].getX() == 0 && PosFObrigaDama[0].getY() != 0)) || ((PosFObrigaDama[1].getX() != 0 && PosFObrigaDama[1].getY() == 0) || (PosFObrigaDama[1].getX() == 0 && PosFObrigaDama[1].getY() != 0)) || (PosFObrigaDama[0].getX() != 0 && PosFObrigaDama[0].getY() == 9) || (PosFObrigaDama[0].getX() != 0 && PosFObrigaDama[0].getY() == 9))) {
		return false;
	}
	else if ((comeu[0] || comeu[1] || comeu[2])) {
		return true;
	}

	return false;
}

void Utilizadores::setCorPeca()
{
	if (forma == 'o') {
		corPeca = "Amarelas";
	}
	else {
		corPeca = "Vermelhas";
	}
}

bool Utilizadores::ComeCimaDireita(Tabuleiro Tab, bool *comeu, int numPeca) {

	if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && (Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == formaInimiga || Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() - 1);

			comeu[1] = true;
		}
		else if(comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObriga[2].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() - 1);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObriga[3].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() - 1);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObriga[0].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() - 1);

			comeu[0] = true;
		}


		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == ' ' && (Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == formaInimiga || Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() - 3) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);

			comeu[1] = true;
		}
		else if(comeu[1]){
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() - 2);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == ' ' && (Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() - 3) == formaInimiga || (Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() - 3) == formaInimigaDama)) && Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() - 4) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
		
			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
			
			comeu[2] = true;
		
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
		
			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() - 3);
		
			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == ' ' && (Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() - 4) == formaInimiga || Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() - 4) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() - 5) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() - 4);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == ' ' && Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() - 4) == ' ' && (Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() - 5) == formaInimiga || Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() - 5) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 6, P[numPeca].getY() - 6) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() - 5);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() - 2) == ' ' && Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() - 3) == ' ' && Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() - 4) == ' ' && Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() - 5) == ' ' && (Tab.getValue(P[numPeca].getX() + 6, P[numPeca].getY() - 6) == formaInimiga || Tab.getValue(P[numPeca].getX() + 6, P[numPeca].getY() - 6) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 7, P[numPeca].getY() - 7) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() - 6);

			comeu[0] = true;
		}

		return true;
	}

	return false;
}

bool Utilizadores::ComeCimaEsquerda(Tabuleiro Tab, bool *comeu, int numPeca) {

	if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && (Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == formaInimiga || Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == ' ') {

		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() - 1);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() - 1);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() - 1);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() - 1);

			comeu[0] = true;
		}
		
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == ' ' && (Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == formaInimiga || Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() - 3) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() - 2);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == ' ' && (Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() - 3) == formaInimiga || Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() - 3) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() - 4) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() - 3);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == ' ' &&  Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() - 3) == ' ' && (Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() - 4) == formaInimiga || Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() - 4) == formaInimiga) && Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() - 5) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() - 4);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == ' ' &&  Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() - 3) == ' ' && Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() - 4) == ' ' && (Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() - 5) == formaInimiga || Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() - 5) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 6, P[numPeca].getY() - 6) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);
			
			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() - 5);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() - 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() - 2) == ' ' && Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() - 3) == formaInimiga && Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() - 4) == ' ' && Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() - 5) == ' ' && (Tab.getValue(P[numPeca].getX() - 6, P[numPeca].getY() - 6) == formaInimiga || Tab.getValue(P[numPeca].getX() - 6, P[numPeca].getY() - 6) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 7, P[numPeca].getY() - 7) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);

			comeu[2] = true;
		}
		else if (comeu[3]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() - 7);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() - 6);

			comeu[0] = true;
		}
		return true;
	}

	return false;

}

bool Utilizadores::ComeBaixoDireita(Tabuleiro Tab, bool *comeu, int numPeca) {

	if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && (Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == formaInimiga || Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == ' ') {

		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() + 1);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() + 1);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() + 1);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 1, P[numPeca].getY() + 1);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == ' ' && (Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == formaInimiga || Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() + 3) == ' ') {

		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 2, P[numPeca].getY() + 2);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == ' ' && (Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() + 3) == formaInimiga || Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() + 3) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() + 4) == ' ') {

		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 3, P[numPeca].getY() + 3);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == ' '  && Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() + 3) == ' ' && (Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() + 4) == formaInimiga || Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() + 4) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() + 5) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);
			
			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 4, P[numPeca].getY() + 4);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == ' '  && Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() + 3) == ' ' && Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() + 4) == ' ' && (Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() + 5) == formaInimiga || Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() + 5) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 6, P[numPeca].getY() + 6) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 5, P[numPeca].getY() + 5);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() + 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() + 2, P[numPeca].getY() + 2) == ' ' && Tab.getValue(P[numPeca].getX() + 3, P[numPeca].getY() + 3) == ' ' && Tab.getValue(P[numPeca].getX() + 4, P[numPeca].getY() + 4) == ' ' && Tab.getValue(P[numPeca].getX() + 5, P[numPeca].getY() + 5) == ' ' && (Tab.getValue(P[numPeca].getX() + 6, P[numPeca].getY() + 6) == formaInimiga || Tab.getValue(P[numPeca].getX() + 6, P[numPeca].getY() + 6) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() + 7, P[numPeca].getY() + 7) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() + 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() + 6, P[numPeca].getY() + 6);

			comeu[0] = true;
		}
		return true;
	}

	return false;

}

bool Utilizadores::ComeBaixoEsquerda(Tabuleiro Tab, bool *comeu, int numPeca) {

	if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && (Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == formaInimiga || Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() + 1);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() + 1);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() + 1);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 1, P[numPeca].getY() + 1);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == ' ' && (Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == formaInimiga || Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() + 3) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 2, P[numPeca].getY() + 2);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == ' ' && (Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() + 3) == formaInimiga || Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() + 3) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() + 4) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 3, P[numPeca].getY() + 3);

			comeu[0] = true;
		}

		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == ' ' && Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() + 3) == ' ' && (Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() + 4) == formaInimiga || Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() + 4) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() + 5) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 4, P[numPeca].getY() + 4);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == ' ' && Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() + 3) == ' ' && Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() + 4) == ' ' && (Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() + 5) == formaInimiga || Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() + 5) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 6, P[numPeca].getY() + 6) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 5, P[numPeca].getY() + 5);

			comeu[0] = true;
		}
		return true;
	}
	else if (Tab.getValue(P[numPeca].getX(), P[numPeca].getY()) == getFormaDama() && Tab.getValue(P[numPeca].getX() - 1, P[numPeca].getY() + 1) == ' ' && Tab.getValue(P[numPeca].getX() - 2, P[numPeca].getY() + 2) == ' ' && Tab.getValue(P[numPeca].getX() - 3, P[numPeca].getY() + 3) == ' ' && Tab.getValue(P[numPeca].getX() - 4, P[numPeca].getY() + 4) == ' ' && Tab.getValue(P[numPeca].getX() - 5, P[numPeca].getY() + 5) == ' ' && (Tab.getValue(P[numPeca].getX() - 6, P[numPeca].getY() + 6) == formaInimiga || Tab.getValue(P[numPeca].getX() - 6, P[numPeca].getY() + 6) == formaInimigaDama) && Tab.getValue(P[numPeca].getX() - 7, P[numPeca].getY() + 7) == ' ') {
		//Opção de comer uma peça ou outra
		if (comeu[0]) {
			PosIObrigaDama[1].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[1].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[1].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);

			comeu[1] = true;
		}
		else if (comeu[1]) {
			PosIObrigaDama[2].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[2].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[2].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);

			comeu[2] = true;
		}
		else if (comeu[2]) {
			PosIObrigaDama[3].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[3].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[3].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);

			comeu[3] = true;
		}
		else {
			PosIObrigaDama[0].setPonto(P[numPeca].getX(), P[numPeca].getY());
			PosFObrigaDama[0].setPonto(P[numPeca].getX() - 7, P[numPeca].getY() + 7);
			PosPecaComidaDama[0].setPonto(P[numPeca].getX() - 6, P[numPeca].getY() + 6);

			comeu[0] = true;
		}
		return true;
	}

	return false;
}

void Utilizadores::EliminaPeca()
{
	//Elimina dados da Peça
	for (int i = 0; i < 8; i++) {
		if (P[i].getPonto() == PosPecaComida[0] || P[i].getPonto() == PosPecaComida[1]) {
			P[i].setForma(' ');
			P[i].setCoordenadas(0, 0);
			numPecasComida++;
			return;
		}
	}
}

void Utilizadores::AlteraPosicoes(Ponto Inicial, Ponto Final)
{
	for (int i = 0; i < 12; i++) {
		if (P[i].getPonto() == Inicial) {
			P[i].setPonto(Final);
		}
	}
}

int Utilizadores::checkDama()
{
	if (sentido == 'c') {
		for (int i = 0; i < 12; i++) {
			if (P[i].getY() == 1) {
				P[i].setDama(true);
				P[i].setForma(getForma() - 32);
				return i;
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			if (P[i].getY() == 8) {
				P[i].setDama(true);
				P[i].setForma(getForma() - 32);
				return i;
			}
		}
	}

	return -1;
}

bool Utilizadores::ComeDuas(Tabuleiro Tab, Ponto Pos) {

	if (checkIfPecaDama(Pos)) {
		return ComeDuasDama(Tab, Pos);
	}

	if (sentido == 'c') {
		if (Tab.getValue(Pos.getX(), Pos.getY()) == getForma() && Tab.getValue(Pos.getX() + 1, Pos.getY() - 1) == formaInimiga && Tab.getValue(Pos.getX() + 2, Pos.getY() - 2) == ' ') {
			PosFObriga[0].setPonto(Pos.getX() + 2, Pos.getY() - 2);
			PosFObriga[1].setPonto(0, 0);
			PosPecaComida[0].setPonto(Pos.getX() + 1, Pos.getY() - 1);
			PosPecaComida[1].setPonto(0, 0);
			return true;
		}
		else if (Tab.getValue(Pos.getX(), Pos.getY()) == getForma() && Tab.getValue(Pos.getX() - 1, Pos.getY() - 1) == formaInimiga && Tab.getValue(Pos.getX() - 2, Pos.getY() - 2) == ' ') {
			PosFObriga[0].setPonto(Pos.getX() - 2, Pos.getY() - 2);
			PosFObriga[1].setPonto(0, 0);
			PosPecaComida[0].setPonto(Pos.getX() - 1, Pos.getY() - 1);
			PosPecaComida[1].setPonto(0, 0);
			return true;
		}
	}
	else {
		if (Tab.getValue(Pos.getX(), Pos.getY()) == getForma() && Tab.getValue(Pos.getX() + 1, Pos.getY() + 1) == formaInimiga && Tab.getValue(Pos.getX() + 2, Pos.getY() + 2) == ' ') {
			PosFObriga[0].setPonto(Pos.getX() + 2, Pos.getY() + 2);
			PosFObriga[1].setPonto(0, 0);
			PosPecaComida[0].setPonto(Pos.getX() + 1, Pos.getY() + 1);
			PosPecaComida[1].setPonto(0, 0);
			return true;
		}
		else if (Tab.getValue(Pos.getX(), Pos.getY()) == getForma() && Tab.getValue(Pos.getX() - 1, Pos.getY() + 1) == formaInimiga && Tab.getValue(Pos.getX() - 2, Pos.getY() + 2) == ' ') {
			PosFObriga[0].setPonto(Pos.getX() - 2, Pos.getY() + 2);
			PosFObriga[1].setPonto(0, 0);
			PosPecaComida[0].setPonto(Pos.getX() - 1, Pos.getY() + 1);
			PosPecaComida[1].setPonto(0, 0);
			return true;
		}
	}

	return false;
}

bool Utilizadores::ComeDuasDama(Tabuleiro Tab, Ponto Pos) {

	bool comeu[3] = { false, false, false };
	int i = 0;

	//Check Posição Peça
	i = checkDamaPos(Pos);

	ComeCimaDireita(Tab, comeu, i);
	ComeCimaEsquerda(Tab, comeu, i);
	ComeBaixoDireita(Tab, comeu, i);
	ComeBaixoEsquerda(Tab, comeu, i);

	//Erro de peça comer para fora matriz
	if ((comeu[0] || comeu[1] || comeu[2]) && (((PosFObrigaDama[0].getX() != 0 && PosFObrigaDama[0].getY() == 0) || (PosFObrigaDama[0].getX() == 0 && PosFObrigaDama[0].getY() != 0)) || ((PosFObrigaDama[1].getX() != 0 && PosFObrigaDama[1].getY() == 0) || (PosFObrigaDama[1].getX() == 0 && PosFObrigaDama[1].getY() != 0)) || (PosFObrigaDama[0].getX() != 0 && PosFObrigaDama[0].getY() == 9) || (PosFObrigaDama[0].getX() != 0 && PosFObrigaDama[0].getY() == 9))) {
		return false;
	}
	else if ((comeu[0] || comeu[1] || comeu[2])) {
		return true;
	}

	return false;
}

int Utilizadores::checkDamaPos(Ponto Pos) {
	for (int i = 0; i < 12; i++) {
		if (P[i].getPonto() == Pos) {
			if (P[i].getDama()) {
				return i;
			}
		}
	}

	return -1;
}

Utilizadores::~Utilizadores()
{
}
