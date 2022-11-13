#include "stdafx.h"
#include "In.h"
#include "Error.h"

#define STRING_END_ZERO '\0'
using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in;
		in.size = 0;
		in.lines = 1;
		in.ignor = 0;
		char* line = new char[IN_MAX_LEN_TEXT];;
		int cols = 0;

		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream fin(infile);
		if (fin.fail()) 
			throw ERROR_THROW(110);

		while (in.size < IN_MAX_LEN_TEXT)
		{
			char k;
			fin.get(k);
			unsigned char uc = k;

			if (fin.eof())
			{
				text[in.size] = STRING_END_ZERO;
				break;
			}
			if (in.code[uc] == in.T || in.code[uc] == in.D || in.code[uc] == in.O)
			{
				text[in.size] = uc;
				in.size++;
				cols++;
			}
			else if (in.code[uc] == in.I)
			{
				in.ignor++;
			}
			else if (in.code[uc] == in.F)
			{
				throw ERROR_THROW_IN(111, in.lines, cols);
			}
			else
			{
				text[in.size] = in.code[uc];
				in.size++;
				cols++;
			}
			if (uc == IN_CODE_ENDL)
			{
				in.lines++;
				cols = 0;
			}
		}
		in.text = text;
		return in;
	}
}