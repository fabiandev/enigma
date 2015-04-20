#ifndef INPUT_H
#define INPUT_H
#include "Seeds.h"

class Input
{
public:
	int numRotors();
	RotorType addRotor(int pos);
	bool readNumbers(int numbers[], int numNumbers, int min, int max);
	bool readChars(char chars[], int numChars);
	bool readString(std::string str);
	char* getChars(int num, std::string msg);
};

#endif