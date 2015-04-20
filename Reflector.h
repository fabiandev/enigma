#ifndef REFLECTOR_H
#define REFLECTOR_H
#include "EncoderModule.h"

class Reflector : public EncoderModule
{
public:
	Reflector(int seed);
	virtual void init();
};

#endif;