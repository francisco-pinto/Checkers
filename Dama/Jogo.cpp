#include "pch.h"
#include "Jogo.h"
#include <time.h>

Jogo::Jogo()
{
	aJogar = 0;
}

Jogo::~Jogo()
{
}

void Jogo::EscolhePosInicial(bool obrigaComer, Ponto &Inicial, Ponto *InicialObrigatorio) {
	do {
		Informacoes(obrigaComer);
		Inicial = J[aJogar]->AskPosicao(1, Tab);
	} while (RestricoesIniciais(Inicial, InicialObrigatorio, obrigaComer));
}

void Jogo::EscolhePosFinal(bool obrigaComer, Ponto &Final, Ponto &Inicial, Ponto *FinalObrigatorio) {
	do {
		Informacoes(obrigaComer);
		Final = J[aJogar]->AskPosicao(2, Tab);
	} while (RestricoesFinais(Inicial, Final, FinalObrigatorio, obrigaComer));
}

void Jogo::ComerNovamente(bool obrigaComer, Ponto &Final, Ponto &Inicial, Ponto *FinalObrigatorio) {
	
	//Chamar a função Escolhe Pos Inicial
	bool PodeComerDuas = false;

	if (obrigaComer) {
		do {
			PodeComerDuas = ComeDuas(Final, FinalObrigatorio);

			if (PodeComerDuas) {
				//Alterar Posição
				gotoxy(95, 0);
				cout << "Come novamente";
				Inicial = Final;

				EscolhePosFinal(obrigaComer, Final, Inicial, FinalObrigatorio);

				Atualiza(Inicial, Final, FinalObrigatorio, obrigaComer);
			}
		} while (ComeDuas(Final, FinalObrigatorio));
	}
}

void Jogo::Movimento(int aJogar) {
	
	Ponto Inicial, InicialObrigatorio[4];
	Ponto Final, FinalObrigatorio[4];
	Ponto Comida;
	bool obrigaComer = ObrigatorioComer(InicialObrigatorio, FinalObrigatorio, Comida);

	EscolhePosInicial(obrigaComer, Inicial, InicialObrigatorio);
			
	EscolhePosFinal(obrigaComer, Final, Inicial, FinalObrigatorio);

	Atualiza(Inicial, Final, FinalObrigatorio, obrigaComer);

	ComerNovamente(obrigaComer, Final, Inicial, FinalObrigatorio);
}

bool Jogo::ComeDuas(Ponto Final, Ponto *FinalObrigatorio) {
	
	/*Peça que se encontra 
	no fim do tabuleiro não tem 
	opção de voltar a comer*/
	if (J[aJogar]->getSentido() == 'c' && !J[aJogar]->checkIfPecaDama(Final)) {
		if (Final.getY() == 2) {
			return false;
		}
	}
	else if (Final.getY() == 7 && !J[aJogar]->checkIfPecaDama(Final)) {
		return false;
	}


	if (J[aJogar]->ComeDuas(Tab, Final)) {
		if (J[aJogar]->checkIfPecaDama(Final)) {
			FinalObrigatorio[0] = J[aJogar]->getPosFinalObrigatoriaDama1();
			return true;
		}
		
		FinalObrigatorio[0] = J[aJogar]->getPosFinalObrigatoria1();
		return true;
	}
	
	return false;
}

bool Jogo::ObrigatorioComer(Ponto *InicialObrigatorio, Ponto *FinalObrigatorio, Ponto &Comida) {
	
	bool obrigatorio = false;

	if (J[aJogar]->Obrigatorio(Tab)) {
		InicialObrigatorio[0] = J[aJogar]->getPosInicialObrigatoria1();
		FinalObrigatorio[0] = J[aJogar]->getPosFinalObrigatoria1();

		InicialObrigatorio[1] = J[aJogar]->getPosInicialObrigatoria2();
		FinalObrigatorio[1] = J[aJogar]->getPosFinalObrigatoria2();
		obrigatorio = true;
	}
	else if (J[aJogar]->ObrigatorioDama(Tab)) {
		InicialObrigatorio[0] = J[aJogar]->getPosInicialObrigatoriaDama1();
		FinalObrigatorio[0] = J[aJogar]->getPosFinalObrigatoriaDama1();

		InicialObrigatorio[1] = J[aJogar]->getPosInicialObrigatoriaDama2();
		FinalObrigatorio[1] = J[aJogar]->getPosFinalObrigatoriaDama2();
		obrigatorio = true;
	}

	if (obrigatorio) {
		return true;
	}

	return false;	
}

bool Jogo::MoveCimaEsquerda(Ponto Inicial, Ponto Final) {
	if ((Final.getX() < Inicial.getX()) && (Final.getY() < Inicial.getY())) {
		return true;
	}

	return false;
}

bool Jogo::MoveCimaDireita(Ponto Inicial, Ponto Final) {
	if ((Final.getX() > Inicial.getX()) && (Final.getY() < Inicial.getY())) {
		return true;
	}

	return false;
}

bool Jogo::MoveBaixoEsquerda(Ponto Inicial, Ponto Final) {
	if ((Final.getX() < Inicial.getX()) && (Final.getY() > Inicial.getY())) {
		return true;
	}

	return false;
}

bool Jogo::MoveBaixoDireita(Ponto Inicial, Ponto Final) {
	if ((Final.getX() > Inicial.getX()) && (Final.getY() > Inicial.getY())) {
		return true;
	}

	return false;
}

bool Jogo::MovimentoDiagonal(Ponto Inicial, Ponto Final) {

	if (MoveCimaEsquerda(Inicial, Final)) {
		for (int i = Final.getX(), j = Final.getY(); i < Inicial.getX(), j < Inicial.getY(); i++, j++) {
			if ((J[aJogar]->getPosFinalObrigatoriaDama1() != Ponto(0, 0))) {
				return true;
			}
			else if ((J[aJogar]->getPosFinalObrigatoriaDama1().getX() == 0) && Tab.getValue(i, j) != ' ') {
				return false;
			}
		}
	}
	else if (MoveCimaDireita(Inicial, Final)) {
		for (int i = Inicial.getX(), j = Final.getY(); i < Final.getX(), j < Inicial.getY(); i++, j++) {
			if ((J[aJogar]->getPosFinalObrigatoriaDama1() != Ponto(0, 0))) {
				return true;
			}
			else if ((J[aJogar]->getPosFinalObrigatoriaDama1().getX() == 0) && Tab.getValue(i, j) != ' ') {
				return false;
			}
		}
	}
	else if (MoveBaixoEsquerda(Inicial, Final)) {
		for (int i = Final.getX(), j = Inicial.getY(); i < Inicial.getX(), j < Final.getY(); i++, j++) {
			if ((J[aJogar]->getPosFinalObrigatoriaDama1() != Ponto(0, 0))) {
				return true;
			}
			else if ((J[aJogar]->getPosFinalObrigatoriaDama1().getX() == 0) && Tab.getValue(i, j) != ' ') {
				return false;
			}
		}
	}
	else {
		for (int i = Inicial.getX(), j = Inicial.getY(); i < Final.getX(), j < Final.getY(); i++, j++) {
			if ((J[aJogar]->getPosFinalObrigatoriaDama1() != Ponto(0, 0))) {
				return true;
			}
			else if ((J[aJogar]->getPosFinalObrigatoriaDama1().getX() == 0) && Tab.getValue(i, j) != ' ') {
				return false;
			}
		}
	}

	return true;
}

bool Jogo::MovimentoImpossivel(Ponto Inicial, Ponto Final, bool obrigaComer) {
	

	/*Impede dama de andar em alguma posição,
	que não seja na sua diagonal*/
	if (J[aJogar]->checkIfPecaDama(Inicial)) {
		if (MovimentoDiagonal(Inicial, Final)) {
			return false;
		}
		else {
			/*Apaga as coordenadas quando erra
			e coloca o ecrã limpo novamente*/
			return ReiniciaTabuleiro();
		}
	}

	if (obrigaComer) {
		if (abs(Inicial.getX() - Final.getX()) >= 3 || abs(Inicial.getY() - Final.getY()) >= 3) {
			return ReiniciaTabuleiro();
		}
	}
	else {

		if (abs(Inicial.getX() - Final.getX()) >= 2 || abs(Inicial.getY() - Final.getY()) >= 2) {
			return ReiniciaTabuleiro();
		}
	}
	
	return false;
}

bool Jogo::sentidoErrado(Ponto Inicial, Ponto Final) {

	/*Se for dama, não tem sentido correto*/
	if (J[aJogar]->checkIfPecaDama(Inicial)) {
		return false;
	}

	if (J[aJogar]->getSentido() == 'b') {
			
		if (Final.getY() <= Inicial.getY()) {
			/*Apaga as coordenadas quando erra
			e coloca o ecrã limpo novamente*/
			return ReiniciaTabuleiro();
		}
	}
	else {
		if (Final.getY() >= Inicial.getY()) {
			return ReiniciaTabuleiro();
		}
	}

	return false;

}

bool Jogo::PosicaoFinalErrada(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool obrigaComer) {

	if (J[aJogar]->checkIfPecaDama(Inicial)) {
		return PosicaoFinalDamaErrada(Inicial, Final, FinalObrigatorio, obrigaComer);
	}
	
	if (Tab.getValue(Final) != ' ' || Inicial.getX() == Final.getX() || Inicial.getY() == Final.getY()) {
		/*Apaga as coordenadas quando erra
		e coloca o ecrã limpo novamente*/
		system("cls");
		Tab.Show();
		return true;
	}
	else if (FinalObrigatorio[0].getX() == 0 && FinalObrigatorio[0].getY() == 0) {
		return false;
	}
	else if (obrigaComer && (Final != FinalObrigatorio[0] && Final != FinalObrigatorio[1] && Final != FinalObrigatorio[2] && Final != FinalObrigatorio[3])) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[0] && FinalObrigatorio[1].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[1] && FinalObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[2] && FinalObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[3] && FinalObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();
	}

	return false;
}

bool Jogo::RestricoesIniciais(Ponto Inicial, Ponto *InicialObrigatorio, bool obrigaComer)
{
	if(PosicaoInicialErrada(Inicial, InicialObrigatorio, obrigaComer)) {
		return true;
	}
	return false;
}

bool Jogo::PosicaoFinalDamaErrada(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool obrigaComer) {

	if (Tab.getValue(Final) != ' ' || Inicial.getX() == Final.getX() || Inicial.getY() == Final.getY()) {
		return ReiniciaTabuleiro();
	}else if (obrigaComer && (Final != FinalObrigatorio[0] && Final != FinalObrigatorio[1] && Final != FinalObrigatorio[2] && Final != FinalObrigatorio[3])) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[0] && FinalObrigatorio[1].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[1] && FinalObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[2] && FinalObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	else if (obrigaComer && (Final != FinalObrigatorio[3] && FinalObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();
	}
	
	return false;
}

bool Jogo::RestricoesFinais(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool obrigaComer)
{
	if (PosicaoFinalErrada(Inicial, Final, FinalObrigatorio, obrigaComer) || sentidoErrado(Inicial, Final) || MovimentoImpossivel(Inicial, Final, obrigaComer)) {
		return true;
	}

	return false;
}

bool Jogo::PosicaoInicialErrada(Ponto Inicial, Ponto *InicialObrigatorio, bool obrigaComer) {
	
	if (Tab.getValue(Inicial) != J[aJogar]->getForma() && Tab.getValue(Inicial) != J[aJogar]->getFormaDama()) {
		/*Apaga as coordenadas quando erra
		e coloca o ecrã limpo novamente*/
		return ReiniciaTabuleiro();

	}
	else if (obrigaComer && (Inicial != InicialObrigatorio[0] && Inicial != InicialObrigatorio[1] && Inicial != InicialObrigatorio[2] && Inicial != InicialObrigatorio[3] && InicialObrigatorio[0].getX() != 0)) {
		return ReiniciaTabuleiro();

	}else if (obrigaComer && (Inicial != InicialObrigatorio[0] && InicialObrigatorio[1].getX() == 0)) {
		return ReiniciaTabuleiro();

	}else if (obrigaComer && (Inicial != InicialObrigatorio[1] && InicialObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();

	}
	else if (obrigaComer && (Inicial != InicialObrigatorio[2] && InicialObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();

	}
	else if (obrigaComer && (Inicial != InicialObrigatorio[3] && InicialObrigatorio[0].getX() == 0)) {
		return ReiniciaTabuleiro();

	}

	return false;
}

bool Jogo::ReiniciaTabuleiro() {
	system("cls");
	Tab.Show();
	return true;
}

void Jogo::Jogadas() {
	
	aJogar = EscolhePrimeiroAJogar();

	while (!Vencedor()) {
		Movimento(aJogar);
		aJogar = TrocaJogador();
	}
}

void Jogo::End() {
	system("cls");
	
	//Colocar nomes
	if (J[0]->getNumPecasComidas() == 12) {
		gotoxy(12, 24);
		cout << "Parabens ao Jogador 1";
	}
	else {
		gotoxy(12, 24);
		cout << "Parabens ao Jogador 2";
	}

	Sleep(5000);
}

bool Jogo::Vencedor() {
	
	if (J[0]->getNumPecasComidas() == 12 || J[1]->getNumPecasComidas() == 12) {
		return true;
	}

	return false;
}

void Jogo::Atualiza(Ponto Inicial, Ponto Final, Ponto *FinalObrigatorio, bool obrigaComer) {
	
	int DamaNova;

	//Retira Peças Comidas
	if (obrigaComer) {
		if (Final == FinalObrigatorio[0]) {
			if (J[aJogar]->checkIfPecaDama(Inicial)) {
				Tab.RetiraComida(J[aJogar]->getPosComidaDama1());
			}
			else {
				Tab.RetiraComida(J[aJogar]->getPosComida1());
			}
		}
		else {
			if (J[aJogar]->checkIfPecaDama(Inicial)) {
				Tab.RetiraComida(J[aJogar]->getPosComidaDama2());
			}
			else {
				Tab.RetiraComida(J[aJogar]->getPosComida2());
			}
		}
		
		J[aJogar]->EliminaPeca();
	}


	//Altera Posições normalmente
	if (J[aJogar]->checkIfPecaDama(Inicial)) {
		Tab.AlteraPosicoes(Inicial, Final, J[aJogar]->getFormaDama());
	}
	else {
		Tab.AlteraPosicoes(Inicial, Final, J[aJogar]->getForma());
	}


	//Altera posição das peças
	J[aJogar]->AlteraPosicoes(Inicial, Final);
	

	//Verifica se existe alguma dama
	DamaNova = J[aJogar]->checkDama();
	if (DamaNova != -1) {
		//Troca a sua forma para Dama
		Tab.setValue(J[aJogar]->getPosPeca(DamaNova), J[aJogar]->getFormaDama());
	}

	J[aJogar]->ReiniciaPosicoesObrigatorias();

	system("cls");
	Tab.Show();
}

void Jogo::gotoxy(int PosX, int PosY)
{
	COORD c = { PosX,PosY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Jogo::DesenhaQuadradoIdentificador() {
	

	//Quadrado 1
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 246);

	for (int j = 0; j < 4 + 2; j++) {
		for (int i = 0; i < 2; i++) {
			gotoxy(95 + j, 7 + i);
			cout << char(219);
		}
	}


	//Quadrado 2
	SetConsoleTextAttribute(hConsole, 244);


	for (int j = 0; j < 4 + 2; j++) {
		for (int i = 0; i < 2; i++) {
			gotoxy(130 + j, 7 + i);
			cout << char(219);
		}
	}

	SetConsoleTextAttribute(hConsole, 15);
	
}

void Jogo::Informacoes(bool ObrigaComer) {
	
	DesenhaQuadradoIdentificador();

	if (J[aJogar]->getCorPeca() == "Amarelas") {

		gotoxy(95, 10);
		cout << "E a vez do " << J[aJogar]->getNome();
	}
	else {

		gotoxy(130, 10);
		cout << "E a vez do " << J[aJogar]->getNome();
	}

	if (ObrigaComer) {
		gotoxy(95, 12);
		cout << "Obrigatorio Comer";
	}
}

int Jogo::TrocaJogador() {
	if (aJogar == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

void Jogo::InicializaJogadores(int escolha) {

	srand(time(NULL));
	int valor = rand() % 40 + 1;
	char forma1, forma2;

	if (valor % 2 == 0) {
		forma1 = 'o';
		forma2 = 'x';
	}
	else {
		forma1 = 'x';
		forma2 = 'o';
	}

	J[0] = (Jogador *) new Jogador;
	J[0]->setForma(forma1);
	J[0]->setFormaDama();
	J[0]->setFormaInimiga();
	J[0]->setBot(false);

	//Escolha entre bot e jogador
	if (escolha == 1) {
		J[1] = (Jogador*) new Jogador;	
		J[1]->setForma(forma2);
		J[1]->setFormaDama();
		J[1]->setFormaInimiga();
		J[1]->setBot(false);


		for (int i = 0; i < 2; i++) {
			J[i]->Inicializar(i + 1, Tab);
		}
	}
	else {
		J[1] = (Bot*) new Bot;
		J[1]->setForma(forma2);
		J[1]->setFormaDama();
		J[1]->setFormaInimiga();
		J[1]->setBot(true);

		for (int i = 0; i < 2; i++) {
			J[i]->Inicializar(i + 1, Tab);
		}
	}	

	DadosJogador();
}

void Jogo::DadosJogador() {

	string nome;

	for (int i = 0; i < 2; i++) {
		if (!J[i]->getBot()) {
			cout << "Insira o nome do jogador " << i + 1 << ": ";
			getline(cin, nome);
			J[i]->setNome(nome);
		}
	}

	system("cls");
}

int Jogo::Opcao() {
	
	char escolha = ' ';

	cout << "Deseja jogar contra:\n1.Jogador\n2.Bot\n";

	do {
		escolha = _getch();
	} while (escolha != '1' && escolha != '2');

	system("cls");

	return int(escolha - 48);
}

void Jogo::Start()
{
	int escolha = Opcao();
	InicializaJogadores(escolha);
	Tab.Show();
	Jogadas();
}

int Jogo::EscolhePrimeiroAJogar()
{
	if (J[0]->getForma() == 'o') {
		return 0;
	}
	else {
		return 1;
	}
}
