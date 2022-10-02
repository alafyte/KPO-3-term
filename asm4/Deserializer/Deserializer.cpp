#include "stdafx.h"

void Deserializer::DeserializeData() 
{

	file = ifstream("C:\\University\\3_cåì\\ÊÏÎ\\asm4\\asm4\\bin.bin");
	unsigned char marker;
	unsigned char currentLength;

	while (!file.eof())
	{
		file.read(reinterpret_cast<char*>(&marker), 1);
		file.read(reinterpret_cast<char*>(&currentLength), 1);

		if (marker == 0x01)
			file.read(reinterpret_cast<char*>(&Long), currentLength);
		else if (marker == 0x02)
			file.read(reinterpret_cast<char*>(&byte), currentLength);
		else if (marker == 0x03)
			file.read(str, currentLength);
	}

	cout << Long << " " << (int)byte << " " << str << endl;

	file.close();
}

void Deserializer::ConvertToAssembler()
{
	fileAsm = ofstream("C:\\University\\3_cåì\\ÊÏÎ\\asm4\\AssemblerProgram\\test.asm");


	fileAsm.clear();

	fileAsm ASM_HEAD;

	fileAsm << "LONGF	DD " << Long << endl;
	fileAsm << "BYTEF	DB " << (int)byte << endl;
	fileAsm << "STRF	DB \"" << str << "\", 0" << endl << endl;

	fileAsm ASM_FOOTER;

	fileAsm.close();
}