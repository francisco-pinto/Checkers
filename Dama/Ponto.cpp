#include "pch.h"
#include "Ponto.h"


Ponto::Ponto()
{
	x = 0;
	y = 0;
}

Ponto::Ponto(int _x, int _y)
{
	x = _x;
	y = _y;
}

Ponto::~Ponto()
{
}

void Ponto::AskPosition()
{
	char YPos = ' ';

	gotoxy(95, 41);
	cout << "Coordenadas: ";
	cout << "x: "; cin >> XPos;
	gotoxy(95, 42);
	cout << "y: "; cin >> YPos;

	if (XPos > 90) {
		XPos -= 32;
	}

	switch (YPos) {
	case '1':
		y = 1;
		break;
	case '2':
		y = 2;
		break;
	case '3':
		y = 3;
		break;
	case '4':
		y = 4;
		break;
	case '5':
		y = 5;
		break;
	case '6':
		y = 6;
		break;
	case '7':
		y = 7;
		break;
	case '8':
		y = 8;
		break;

	default:
		y = 0;
		break;
	}

	x = int(XPos - 64);
}

bool Ponto::operator ==(Ponto P) {
	if (P.getX() == x && P.getY() == y) {
		return true;
	}
	else {
		return false;
	}
}

bool Ponto::operator!=(Ponto P)
{
	if (P.getX() == x && P.getY() == y) {
		return false;
	}
	else {
		return true;
	}
}

void Ponto::gotoxy(int PosX, int PosY)
{
	COORD c = { PosX,PosY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
