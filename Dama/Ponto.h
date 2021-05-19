#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class Ponto
{
private:
	char XPos;
	int x;
	int y;
public:
	Ponto();
	Ponto(int _x, int _y);
	~Ponto();

	void setPonto(int _x, int _y) { x = _x; y = _y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	int getX() { return x; }
	int getY() { return y; }

	void AskPosition();
	bool operator==(Ponto P);
	bool operator!=(Ponto P);

private:
	void gotoxy(int PosX, int PosY);
};

