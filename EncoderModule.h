#ifndef ENCODER_MODULE_H
#define ENCODER_MODULE_H

class EncoderModule {
public:
	static const int NUM_LETTERS = 26;
	EncoderModule(int randSeed);
	virtual ~EncoderModule();
	virtual void init() = 0;
	virtual void print() const;
	virtual int getCode(int idx) const;
	virtual int getIndex(int element) const;
protected:
	int m_configuration[NUM_LETTERS];
	int seed;
};

#endif;