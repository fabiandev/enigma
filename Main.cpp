#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "Input.h"
#include "Enigma.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	Input input;
	int numRotors = input.numRotors();
	Enigma *e = new Enigma(numRotors);
	for (int i = 1; i <= numRotors; i++) {
		RotorType type = input.addRotor(i);
		e->addRotor(type);
	}

	char *dKey;
	dKey = input.getChars(numRotors, "Set the daily key. Length: ");
	e->setDailyKey(dKey);
	
	char *mKey;
	mKey = input.getChars(numRotors, "Set the message key. Length: ");
	e->setMessageKey(mKey);
	
	std::string en = e->encrypt("HALLO");
	std::cout << en << std::endl;
	std::string de = e->decrypt(en);
	std::cout << de;

	char quit;
	cout << endl << "[q] Quit" << endl;
	do {
		quit = getchar();
	} while (quit != 'q');

	delete dKey; dKey = NULL;
	delete mKey; mKey = NULL;
	delete e; e = NULL;

	return 0;
}

