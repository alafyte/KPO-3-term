#pragma once
#include "stdafx.h"

class Serealizer
{
private:

	std::ofstream file;
	unsigned char longMarker = 0x01;
	unsigned char byteMarker = 0x02;
	unsigned char stringMarker = 0x03;
	unsigned char longLength = sizeof(long);
	unsigned char byteLength = sizeof(unsigned char);
	unsigned char stringLength;
	long Long;
	unsigned char byte;
	char str[150];

public:

	Serealizer(long Long, unsigned char byte, char* str)
	{
		this->Long = Long;
		this->byte = byte;
		strcpy_s(this->str, str);
		this->stringLength = strlen(str) + 1;
	}

	void SerealizeData();

};

