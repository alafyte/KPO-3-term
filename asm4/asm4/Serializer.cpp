#include "stdafx.h"


void Serealizer::SerealizeData()
{
	file = ofstream("C:\\University\\3_cåì\\ÊÏÎ\\asm4\\asm4\\bin.bin");

	file.clear();


	file.write((char*)&longMarker, 1);
	file.write((char*)&longLength, 1);
	file.write(reinterpret_cast<char*>(&Long), longLength);

	file.write((char*)&byteMarker, 1);
	file.write((char*)&byteLength, 1);
	file.write(reinterpret_cast<char*>(&byte), byteLength);

	file.write((char*)&stringMarker, 1);
	file.write((char*)&stringLength, 1);
	file.write(str, stringLength);

	file.close();
}
