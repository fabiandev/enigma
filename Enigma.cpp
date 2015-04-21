#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "Enigma.h"
#include "Seeds.h"
#include "Rotor.h"
#include "Reflector.h"

int count = 0;

Enigma::Enigma(int num_rotors) {
	 m_numRotors = num_rotors;
	 m_rotors = new Rotor*[num_rotors];
	 m_reflector = new Reflector(ReflectorSeed);
}

Enigma::~Enigma() {
	for (int i = 0; i < m_numRotors; i++) {
		delete m_rotors[i];
		m_rotors[i] = NULL;
	}

	delete[] m_rotors;
	m_rotors = NULL;

	delete m_reflector;
	m_reflector = NULL;
}

void Enigma::addRotor(RotorType type) {
	if (count < m_numRotors) {
		Rotor *rotor = new Rotor(type);
		m_rotors[count] = rotor;
		count++;
	}
}

void Enigma::changeRotor(Rotor &rotor, int posIdx) {
	m_rotors[posIdx] = &rotor;
}

void Enigma::setDailyKey(char key[]) {
	m_dailyKey = key;
	applyDailyKey();
}

void Enigma::setMessageKey(char key[]) {
	m_msgKey = key;
}

void Enigma::reset() {
	for (int i = 0; i < m_numRotors; i++) {
		m_rotors[i]->setOffset(0);
	}
}

int mod(int a, int b) {
	return (a%b + b) % b;
}

int Enigma::getPosition(int offset, int idx, bool reverse) {
	return reverse ? mod((idx - offset), 26) : mod((idx + offset), 26);
}

void Enigma::spin(int rotor) {
	int offset = m_rotors[rotor]->getOffset();

	if (offset < 25) {
		m_rotors[rotor]->setOffset(offset + 1);
	} else if (offset == 25) {
		m_rotors[rotor]->setOffset(0);

		if (rotor + 1 < m_numRotors) {
			spin(rotor + 1);
		}
	}
}

std::string Enigma::crypt(const std::string & msg) {
	std::string encrypted = "";
	int next;

	for (int i = 0; i < (int)msg.size(); i++) {

		spin(0);

		next = toInt((char)msg[i]);

		// go through rotors
		for (int j = 0; j < m_numRotors; j++) {
			next = m_rotors[j]->getCode(getPosition(m_rotors[j]->getOffset(), next));
		}

		// go through reflector
		next = m_reflector->getCode(next);

		// go back
		for (int j = m_numRotors - 1; j > -1; j--) {
			next = getPosition(m_rotors[j]->getOffset(), m_rotors[j]->getIndex(next), true);
		}

		// final letter
		encrypted += toChar(next);
	}

	return encrypted;
}

std::string Enigma::encrypt(const std::string & msg) {
	std::string key = "";
	std::string cryptKey;
	for (int i = 0; i < m_numRotors; i++) {
		key += m_msgKey[i];
	}
	cryptKey = crypt(key);
	applyMsgKey();

	return cryptKey + crypt(msg);
}

std::string Enigma::decrypt(const std::string & msg) {
	applyDailyKey();
	std::string key = "";
	std::string plainMsg = "";
	std::string plainKey;

	for (int i = 0; i < (int)msg.size(); i++) {
		if (i < m_numRotors) {
			key += msg[i];
		} else {
			plainMsg += msg[i];
		}
	}

	plainKey = crypt(key);

	for (int i = 0; i < m_numRotors; i++) {
		m_msgKey[i] = (char)plainKey[i];
	}

	applyMsgKey();

	return crypt(plainMsg);
}

void Enigma::applyMsgKey() {
	for (int i = 0; i < m_numRotors; i++) {
		m_rotors[i]->setOffset(toInt(m_msgKey[i]));
	}
}

void Enigma::applyDailyKey() {
	for (int i = 0; i < m_numRotors; i++) {
		m_rotors[i]->setOffset(toInt(m_dailyKey[i]));
	}
}

int Enigma::toInt(char c) {
	return ((int)c) - 65; // returns 0 for A, 1 for B,..
}

char Enigma::toChar(int i) {
	return (char)(i + 65); // returns A for 0, B for 2,..
}