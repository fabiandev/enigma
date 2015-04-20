#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "Input.h"
#include "Seeds.h"

char* Input::getChars(int num, std::string msg) {
	char *chars = new char[num];
	bool success;
	do {
		std::cout << msg << num << std::endl;
		success = readChars(chars, num);
	} while (!success);
	
	return chars;
}

int Input::numRotors() {
	int numbers[1];
	bool success;
	do {
		std::cout << "How many rotors should be added to Enigma? (max. 10)?" << std::endl;
		success = readNumbers(numbers, 1, 1, 10);
	} while (!success);
	
	return numbers[0];
}

RotorType Input::addRotor(int pos) {
	int numbers[1];
	bool success;
	do {
		std::cout << "Which rotor type do you want to choose for position " << pos << "?" << std::endl;
		std::cout << "[1] ROTOR_TYPE_I\n[2] ROTOR_TYPE_II\n[3] ROTOR_TYPE_III\n[4] ROTOR_TYPE_IV\n[5] ROTOR_TYPE_V" << std::endl;
		success = readNumbers(numbers, 1, 1, 5);
	} while (!success);

	switch (numbers[0]) {
	case 1:
		return ROTOR_TYPE_I;
		break;
	case 2:
		return ROTOR_TYPE_II;
		break;
	case 3:
		return ROTOR_TYPE_III;
		break;
	case 4:
		return ROTOR_TYPE_IV;
		break;
	case 5:
		return ROTOR_TYPE_V;
		break;
	default:
		return ROTOR_TYPE_I;
		break;
	}
}

bool Input::readNumbers(int numbers[], int numNumbers, int min, int max) {
	std::string input;
	std::stringstream inputStream;
	int numInputs = 0;
	bool error = false;

	std::getline(std::cin, input);
	inputStream.str(input);

	for (int i = 0; i < numNumbers; ++i) {
		inputStream >> numbers[i];
		if (numbers[i] < min || numbers[i] > max) {
			error = true; break;
		}
		numInputs++;
	}

	if (numInputs != numNumbers) {
		error = true;
	}

	if (!error) {
		return true;
	}

	inputStream.clear();
	std::cout << "\nError: Invalid input!\n";

	return false;
}

bool Input::readChars(char chars[], int numChars) {
	std::string input;
	std::stringstream inputStream;
	int numInputs = 0;
	bool error = false;

	std::getline(std::cin, input);
	inputStream.str(input);

	for (int i = 0; i < numChars; ++i) {
		inputStream >> chars[i];
		if (chars[i] < 'A' || chars[i] > 'Z') {
			error = true; break;
		}
		numInputs++;
	}

	if (numInputs != numChars) {
		error = true;
	}

	if (!error) {
		return true;
	}

	inputStream.clear();
	std::cout << "\nError: Invalid input!\n";

	return false;
}

bool Input::readString(std::string str) {
	std::getline(std::cin, str);
	return true;
}