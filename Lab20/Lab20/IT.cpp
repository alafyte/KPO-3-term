#include "stdafx.h"


namespace IT
{
	IdTable::IdTable()
	{
		this->noname_lexema_count = 0;
		this->maxsize = TI_MAXSIZE;
		this->size = 0;
		this->table = new Entry[TI_MAXSIZE];
	}
	Entry::Entry()
	{
		this->parrent_function[0] = '\0';
		this->id[0] = '\0';
		this->firstApi = 0;
		this->iddatatype = IT::IDDATATYPE::DEF;
		this->idtype = IT::IDTYPE::D;
		this->parmQuantity = 0;
		
	}

	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, int it)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		this->value.vint = it;
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr.str,255, ch);
		this->value.vstr.len = strlen(ch);
	}
	Entry::Entry(const char* parrent_function, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int first, const char* ch)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->firstApi = first;
		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
		strcpy_s(this->value.vstr.str, 255, ch);
		this->value.vstr.len = strlen(ch);
	}
	Entry::Entry(char* parrent_function, char* id, IDDATATYPE iddatatype, IDTYPE idtype)
	{
		int i = 0;
		if (parrent_function)
			for (i = 0; parrent_function[i] != '\0'; i++)
				this->parrent_function[i] = parrent_function[i];
		this->parrent_function[i] = '\0';
		i = 0;
		if (id)
			for (i = 0; id[i] != '\0'; i++)
				this->id[i] = id[i];

		this->id[i] = '\0';
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		this->parmQuantity = 0;
	}

	IdTable Create(int size)
	{
		IdTable id_table;
		id_table.size = size;
		id_table.maxsize = TI_MAXSIZE;
		id_table.table = new Entry[TI_MAXSIZE];
		return id_table;
	}
	void IdTable::Add(Entry entry)
	{
		if (strlen(entry.id) > ID_MAXSIZE && entry.idtype != IDTYPE::F)
			throw ERROR_THROW(121);

		if (this->size < this->maxsize)
		{
			if (entry.idtype != IDTYPE::F)
				entry.id[5] = '\0';
			this->table[this->size] = entry;

			switch (entry.iddatatype)
			{
			case IDDATATYPE::INT:
			{
				this->table[this->size].value.vint = TI_INT_DEFAULT;
			}
			case IDDATATYPE::STR:
			{
				this->table[this->size].value.vstr.str[0] = TI_STR_DEFAULT;
				this->table[this->size].value.vstr.len = 0;
			}
			}
			this->size++;
		}
		else
			throw ERROR_THROW(122);

	}
	Entry IdTable::GetEntry(int n)
	{
		if (n < this->size && n >= 0)
			return this->table[n];
	}
	int IdTable::IsId(const char id[ID_MAXSIZE])
	{
		for (int iter = 0; iter < this->size; iter++)
		{
			if (strcmp(this->table[iter].id, id) == 0)
				return iter;
		}
		return TI_NULLIDX;
	}
	int IdTable::IsId(const char id[ID_MAXSIZE], const char parrent_function[ID_MAXSIZE + 5])
	{
		for (int i = 0; i < this->size; i++)
		{
			if ((strcmp(this->table[i].id, id) == 0) &&
				(strcmp(this->table[i].parrent_function, parrent_function) == 0))
				return i;
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable.table = nullptr;
	}

	char* IdTable::GetLexemaName()
	{
		char buffer[5];
		_itoa_s(this->noname_lexema_count, buffer, 10);
		strcat_s(buffer,5,"_l");
		this->noname_lexema_count++;
		return buffer;
	}

	void IdTable::PrintIdTable(const wchar_t* in)
	{
		std::ofstream* idStream = new std::ofstream;
		idStream->open(in);

		if (idStream->is_open())
		{
			bool flagForFirst = false;

#pragma region Literals

			* (idStream) << "##########################################################################################################################" << endl;
			*(idStream) << "------------------ Литералы ------------------" << std::endl;
			
			*(idStream) << std::setw(15) << "Идентификатор:" << std::setw(17) << "Тип данных:"<< std::setw(15) << "Значение:" << std::setw(27) << "Длина строки:" << std::setw(20) << "Первое вхождение:" << std::endl;
			

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::L)
				{
					std::cout.width(25);
					switch (this->table[i].iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table[i].id << "\t\t\t" << "INT " << "\t\t" << this->table[i].value.vint << "\t\t\t" << "-\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table[i].id << "\t\t\t" << "STR " << "\t    " << this->table[i].value.vstr.str << std::setw(30 - strlen(this->table[i].value.vstr.str)) << (int)this->table[i].value.vstr.len << "\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					}
				}
			}

			


#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Functions

			flagForFirst = false;

			*(idStream) << "##########################################################################################################################" << endl;
			*(idStream) << "------------------ Функции ------------------" << std::endl;
			
			*(idStream) << std::setw(15) << "Идентификатор:" << std::setw(26) << "Тип данных возврата:" << std::setw(36) << "Количество переданных параметров:" << std::setw(22) << "Первое вхождение:" << std::endl;
			

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::F)
				{

					switch (this->table[i].iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table[i].id << std::setw(28 - strlen(this->table[i].id)) << "INT " << "\t\t\t\t" << this->table[i].parmQuantity << "\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table[i].id << std::setw(28 - strlen(this->table[i].id)) << "STR " << "\t\t\t\t" << this->table[i].parmQuantity << "\t\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					}

				}


			}

			

#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "##########################################################################################################################" << endl;
			*(idStream) << "------------------ Переменные ------------------" << std::endl;
			*(idStream) << std::setw(25) << "Имя родительского блока:" << std::setw(20) << "Идентификатор:" << std::setw(16) << "Тип данных:" << std::setw(24) << "Тип идентификатора:" << std::setw(21) << "Первое вхождение:" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::V)
				{


					switch (this->table[i].iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << std::setw(15) << "V" << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << std::setw(15) << "V" << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

				if (this->table[i].idtype == IT::IDTYPE::P)
				{

					switch (this->table[i].iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "INT " << std::setw(15) << "P" << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table[i].parrent_function << std::setw(35 - strlen(this->table[i].parrent_function)) << this->table[i].id << std::setw(20) << "STR " << std::setw(15) << "P" << "\t\t\t" << this->table[i].firstApi << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}


			}


#pragma endregion
			* (idStream) << "\n\n\n";

		}
		else
			throw ERROR_THROW(125);
		idStream->close();
		delete idStream;
	}
}