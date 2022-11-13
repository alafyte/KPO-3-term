#pragma once
#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "Parm.h"

namespace Out
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const OUT INITOUT = { L"", NULL };
	OUT getout(wchar_t outfile[]);
	void WriteLine(OUT out, const char* c, ...);
	void WriteLine(OUT out, const wchar_t* c, ...);
	void WriteIn(OUT out, In::IN in);
	void WriteError(OUT out, Error::ERROR error);
	void Close(OUT out);
}
