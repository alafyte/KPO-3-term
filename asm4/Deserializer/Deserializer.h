#pragma once
#include "stdafx.h"

class Deserializer
{
protected:
	std::ifstream file;
	std::ofstream fileAsm;
	unsigned char longMarker = 0x01;
	unsigned char byteMarker = 0x02;
	unsigned char stringMarker = 0x03;

	long Long;
	unsigned char byte;
	char str[150];

public:
	
	Deserializer() 
	{ 
		this->Long = NULL;
		this->byte = NULL;
	}

	void DeserializeData();
	void ConvertToAssembler();
};
