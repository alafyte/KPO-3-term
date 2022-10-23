#include "stdafx.h"
#include <fstream>
namespace LT
{
	LT::LexTable::LexTable()
	{
		this->maxsize = LT_MAXSIZE;
		this->size = 0;
		this->table = new Entry[LT_MAXSIZE];
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size < lextable.maxsize)
			lextable.table[lextable.size++] = entry;
		else
			throw ERROR_THROW(120);
	}
	Entry LexTable::GetEntry(int n)
	{
		if (n < this->maxsize && n >= 0)
			return this->table[n];
	}
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.table = nullptr;
	}
	void LexTable::PrintLexTable(const wchar_t* in)
	{

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(in);
		(*lex_stream) << "--------- Таблица лексем ---------";

		if (lex_stream->is_open())
		{
			int num_string = 0;
			for (int i = 0; i < this->size;)
			{
				if (num_string == this->table[i].sn)
					(*lex_stream) << this->table[i++].lexema;
				else
				{
					num_string++;
					if (this->table[i].sn != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << ".\t";

					if (num_string == this->table[i].sn)
						(*lex_stream) << this->table[i++].lexema;
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}
	LT::Entry::Entry()
	{
		this->lexema = '\0';
		this->sn = LT_TI_NULLXDX;
		this->idxTI = LT_TI_NULLXDX;
	}

	LT::Entry::Entry(const char lex, int str_n, int idxTI)
	{
		this->lexema = lex;
		this->sn = str_n;
		this->idxTI = idxTI;
	}
}