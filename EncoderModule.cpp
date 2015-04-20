#include "stdafx.h"
#include <iostream>
#include "Seeds.h"
#include "EncoderModule.h"
#include <vector>

EncoderModule::~EncoderModule() {}

EncoderModule::EncoderModule(int seed) {
	this->seed = seed;
}

void EncoderModule::print() const {
	for (int i = 0; i < NUM_LETTERS; i++) {
		std::cout << "[" << i << "]" << " " << m_configuration[i] << ", ";
	}
	std::cout << std::endl;
}

int EncoderModule::getCode(int idx) const {
	return m_configuration[idx];
}

int EncoderModule::getIndex(int element) const {
	for (int i = 0; i < NUM_LETTERS; i++) {
		if (m_configuration[i] == element) {
			return i;
		}
	}
	return false;
}