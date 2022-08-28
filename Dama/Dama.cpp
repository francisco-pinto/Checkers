#include "pch.h"
#include <iostream>
#include <conio.h>
#include "Jogo.h"
#include <fstream>

using namespace std;

void menu();

void gotoxy(int PosX, int PosY)
{
	COORD c = { PosX,PosY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void scrollbar(bool show) {
	
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, show);
}

void Instrucoes() {
	
	ifstream ifile;
	string instru;
	
	ifile.open("Instrucoes.txt");

	scrollbar(true);

	if (!ifile) {
		cout << "Erro na abertura das isntrucoes";
		Sleep(1500);
		menu();
	}
	while (ifile.peek() != EOF) {
		getline(ifile, instru);
		cout << instru;
		cout << "\n";
	}

	//Eliminate Scroll Bar
	system("pause");
	scrollbar(false);
	menu();
}

void menu() {
	 
	Jogo Jogo;
	char opcao = ' ';
	system("cls");
	
	cout << "\n _____   _                  _					";
	cout << "\n/ ____|	| |                | |				";
	cout << "\n| |     | |__    ___   ___ | | __ ___  _ __  ___";
	cout << "\n| |     | '_ \\  / _ \\ / __|| |/ // _ \\| '__|/ __|";
	cout << "\n| |____ | | | ||  __/| (__ |   <|  __/|  |  \\__ \\";
	cout << "\n\\_____| |_| |_| \\___| \\___||_|\\_\\___| | _|  |___/";
		
	do {
		gotoxy(68, 18);
		cout << "Menu";

		gotoxy(73, 20);
		cout << "a. Jogar";

		gotoxy(73, 23);
		cout << "b. Instrucoes";

		gotoxy(73, 26);
		cout << "c. Sair";

		gotoxy(0, 0);
		opcao = _getch();

		if (opcao < 97) {
			opcao = opcao + 32;
		}

	} while (opcao != 'a' && opcao != 'b' && opcao != 'c');
	
	
	switch (opcao) {
		case 'a':
			system("cls");
			Jogo.Start();
			Jogo.End();
			break;
		case 'b':
			system("cls");
			Instrucoes();
			break;
		case 'c':
			exit(0);
			break;
	}

	system("cls");
}

void DisplaySettings() {

	//Fullscreen
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL); //FullScreen
	/*Foi impedido de ser seleciondado na janela,
	no modo edição*/

	//Eliminate Scroll Bar
	scrollbar(false);

	//Esconde o cursor do display (underscore branco)
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
	DisplaySettings();

	menu();
	system("pause");
}
