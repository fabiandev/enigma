#ifndef ENIGMA_H
#define ENIGMA_H
#include "Seeds.h"
#include "Rotor.h"
#include "Reflector.h"

class Enigma {
public:
	Enigma(int numRotors);
	~Enigma();
	void addRotor(RotorType type);
	void changeRotor(Rotor & rotor, int posIdx);
	void setDailyKey(char key[]);
	void setMessageKey(char key[]);
	void reset();
	std::string encrypt(const std::string & msg);
	std::string decrypt(const std::string & msg);
	void applyMsgKey();
	int toInt(char c);
	char toChar(int i);
private:
	std::string crypt(const std::string & msg);
	int getPosition(int offset, int idx, bool reverse = false);
	void spin(int rotor);
	void applyDailyKey();
	int m_numRotors;
	Rotor **m_rotors;
	Reflector *m_reflector;
	char *m_msgKey;
	char *m_dailyKey;
};

#endif;