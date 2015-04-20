#ifndef ROTOR_H
#define ROTOR_H
#include "EncoderModule.h"

class Rotor : public EncoderModule
{
public:
	Rotor(int seed);
	virtual void init();
	void setOffset(int offset);
	int getOffset();
protected:
	int offset; // current rotor position
};

#endif;