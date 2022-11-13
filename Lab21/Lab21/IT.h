#pragma once

#define ID_MAXSIZE		5					// максимальное количество символов в идентификаторе 
#define TI_MAXSIZE		4096				// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT  0x00000000			// значение по умолчанию для типа integer
#define TI_STR_DEFAULT  0x00				// значение по умолчанию для типа string
#define TI_NULLIDX		0xffffffff			// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE  255					// максимальная длина строки

#define PARM_ID L".id.txt"

namespace IT
{
	enum IDDATATYPE { DEF = 0, INT = 1, STR = 2 };				// типы данных идентификаторов: integer, string
	enum IDTYPE { D = 0, V = 1, F = 2, P = 3, L = 4 };			// типы идентификаторов: переменная, функция, параметр, литерал

	struct Entry
	{
		char parrent_function[ID_MAXSIZE + 5];
		int firstApi;
		char id[ID_MAXSIZE + 5];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union
		{
			int vint;
			char operation = '\0';
			struct
			{
				unsigned char len;
				char str[TI_STR_MAXSIZE];
			} vstr;
		} value;
		int parmQuantity;
		Entry();
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* str);
		Entry(const char* parrentFunc, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* str);
		Entry(char* parrentFunc, char* id, IDDATATYPE iddatatype, IDTYPE idtype);
	};

	struct IdTable
	{
		int noname_lexema_count;
		int maxsize;
		int size;
		Entry* table;
		Entry GetEntry(int n);
		int IsId(const char id[ID_MAXSIZE]);
		int IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5]);
		void Add(Entry entry);
		void PrintIdTable(const wchar_t* in);
		IdTable();
		char* GetLexemaName();
	};
	void Delete(IdTable& idtable);
};

