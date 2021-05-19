#include "pch.h"
#include "Peca.h"


Peca::Peca()
{
	Dama = false;
}


Peca::~Peca()
{
}

char Peca::getFormaDama()
{
	if (forma == 'x') {
		formaDama = 'X';
	}
	else {
		formaDama = 'O';
	}

	return formaDama;
}
