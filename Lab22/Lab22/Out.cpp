#include "stdafx.h"
#include "Out.h"
#pragma warning(disable:4996)

namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		OUT out;
		out.stream = new ofstream;
		out.stream->open(outfile);
		if (out.stream->fail())
			throw ERROR_THROW(112);
		wcscpy_s(out.outfile, outfile);
		return out;
	}

	void WriteLine(OUT out, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*out.stream << ptr[i++];
		*out.stream << endl;
	}
	void WriteLine(OUT out, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*out.stream << temp;
		}
		*out.stream << endl;
	}

	void WriteIn(OUT out, In::IN in) 
	{
		*out.stream << in.text << std::endl;
	}

	void WriteError(OUT out, Error::ERROR error)
	{
		if (out.stream)
		{
			*out.stream << "--- Ошибка!!! --- " << endl;
			*out.stream << "Ошибка " << error.id << ": " << error.message << endl;
			if (error.inext.line != -1)
			{
				*out.stream << "Строка: " << error.inext.line << endl << "Столбец: " << error.inext.col << endl << endl;
			}
		}
	}
	void Close(OUT out) {
		out.stream->close();
		delete out.stream;
	}
}