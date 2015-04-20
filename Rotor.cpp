#include "stdafx.h"
#include <iostream>
#include "Seeds.h"
#include "EncoderModule.h"
#include "Rotor.h"
#include <vector>

Rotor::Rotor(int seed) : EncoderModule(seed) {
	init();
}

void Rotor::setOffset(int offset) {
	this->offset = offset;
}

int Rotor::getOffset() {
	return offset;
}

void Rotor::init() {
	std::vector<int> v; // holds int 0 - 25

	for (int i = 0; i < NUM_LETTERS; i++) {
		v.push_back(i);
	}

	srand(seed);

	std::vector<int> r; // random order of 0 - 25
	for (int i = 0; i < NUM_LETTERS; i++) {
		int idx = (rand() % v.size()); // random index 0 - vector v size
		r.push_back(v[idx]); // add value from vector v to random vector r
		std::vector<int>::iterator it = v.begin() + idx; // get element to delete
		v.erase(it); // delete this element from vector v
	}

	// copy into config array
	for (int i = 0; i < NUM_LETTERS; i++) {
		m_configuration[i] = r[i];
	}
}