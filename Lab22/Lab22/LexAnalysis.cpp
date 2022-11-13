#include "stdafx.h"

namespace LA
{
	void FindLex(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		char* temp = new char[token_size] {};
		int str_number = 1;
		int str_position = 1;
		In::IN in;

		for (int i = 0, j = 0; i < source.size; i++)
		{
			if (in.code[(source.text[i])] != in.D && in.code[(source.text[i])] != in.O && (source.text[i]) != '|')
			{
				temp[j++] = source.text[i];
				str_position++;
				continue;
			}
			else
			{
				if (j != 0)
				{
					i--;
					temp[j] = '\0';
					if (Analyse(temp, str_number, lexTable, idTable))
					{
						temp[0] = '\0'; j = 0;
						continue;
					}
					else
						throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);
				}
				else
				{
					if (source.text[i] == '\'')
					{
						temp[j++] = source.text[i++];

						for (int c = 0; source.text[i] != '\''; c++)
						{
							if (c <= TI_STR_MAXSIZE)
							{
								temp[j++] = source.text[i++];
							}
							else
								throw ERROR_THROW_IN(127, str_number, str_position - strlen(temp) + 1);
						}

						if (source.text[i] == '\'')
						{
							temp[j] = source.text[i];
							if (Analyse(temp, str_number, lexTable, idTable))
							{
								temp[0] = '\0'; j = 0;
								continue;
							}
							else
								throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);
						}
						else
							throw ERROR_THROW_IN(124, str_number, str_position - strlen(temp) + 1);
					}

					if (source.text[i] != '|')
					{
						if (source.text[i] == ' ' || source.text[i] == '\t')
						{
							str_position++;
							continue;
						}

						temp[0] = source.text[i];
						temp[1] = '\0';
						if (Analyse(temp, str_number, lexTable, idTable))
							str_position++;
						else
							throw ERROR_THROW_IN(123, str_number, str_position - strlen(temp) + 1);

						temp[0] = '/0'; j = 0;
					}
				}
			}
			if (source.text[i] == '|')
			{
				str_number++;
				str_position = 0;
			}
		}
		delete[] temp;
	}

	bool Analyse(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		static TypeOfVar flag_type_variable;

		switch (token[0])
		{
		case LEX_COMMA:
		{
			Add(lexTable, { LEX_COMMA ,str_number, LT_TI_NULLXDX });
			return true;
		}

		case LEX_LEFTBRACE:
		{
			Add(lexTable, { LEX_LEFTBRACE,str_number,LT_TI_NULLXDX });
			return true;
		}

		case LEX_RIGHTBRACE:
		{
			Add(lexTable, { LEX_RIGHTBRACE,str_number,LT_TI_NULLXDX });
			return true;
		}

		case LEX_LEFTHESIS:
		{
			Add(lexTable, { LEX_LEFTHESIS,str_number,LT_TI_NULLXDX });
			return true;
		}

		case LEX_RIGHTHESIS:
		{
			Add(lexTable, { LEX_RIGHTHESIS,str_number,LT_TI_NULLXDX });
			return true;
		}

		case LEX_SEMICOLON:
		{
			Add(lexTable, { LEX_SEMICOLON,str_number,LT_TI_NULLXDX });
			return true;
		}

		case '+':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D, lexTable.size,'+' });
			Add(lexTable, { LEX_PLUS,str_number,idTable.size - 1 });
			return true;
		}

		case '-':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '-' });
			Add(lexTable, { LEX_MINUS, str_number, idTable.size - 1 });
			return true;
		}

		case '*':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '*' });
			Add(lexTable, { LEX_STAR, str_number, idTable.size - 1 });
			return true;
		}

		case '/':
		{
			idTable.Add({ "\0", "\0", IT::IDDATATYPE::DEF, IT::IDTYPE::D,lexTable.size, '/' });
			Add(lexTable, { LEX_DIRSLASH, str_number, idTable.size - 1 });
			return true;
		}

		case LEX_EQUAL_SIGN:
		{
			Add(lexTable, { LEX_EQUAL_SIGN, str_number, LT_TI_NULLXDX });
			return true;
		}

		case 'f':
		{
			FST::FST* function = new FST::FST(FUNCTION(token));
			if (FST::execute(*function))
			{
				Add(lexTable, { LEX_FUNCTION, str_number, LT_TI_NULLXDX });

				delete function;
				function = NULL;
				return true;
			}
			else
			{
				delete function;
				function = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 'i':
		{
			FST::FST* integer = new FST::FST(INTEGER(token));
			if (FST::execute(*integer))
			{
				Add(lexTable, { LEX_INTEGER, str_number, LT_TI_NULLXDX });

				delete integer;
				integer = NULL;
				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::INT;
				return true;
			}
			else
			{
				delete integer;
				integer = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 's':
		{
			FST::FST* string = new FST::FST(STRING(token));
			if (FST::execute(*string))
			{
				Add(lexTable, { LEX_STRING, str_number, LT_TI_NULLXDX });

				delete string;
				string = NULL;
				flag_type_variable.LT_posititon = lexTable.size - 1;
				flag_type_variable.type = TypeOfVar::STR;
				return true;
			}
			else
			{
				delete string;
				string = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}

		case 'd':
		{
			FST::FST* declare = new FST::FST(DECLARE(token));
			if (FST::execute(*declare))
			{
				Add(lexTable, { LEX_DECLARE, str_number, LT_TI_NULLXDX });

				delete declare;
				declare = NULL;
				return true;
			}
			else
			{
				delete declare;
				declare = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}

		case 'r':
		{
			FST::FST* _return = new FST::FST(RETURN(token));
			if (FST::execute(*_return))
			{
				Add(lexTable, { LEX_RETURN, str_number, LT_TI_NULLXDX });

				delete _return;
				_return = NULL;
				return true;
			}
			else
			{
				delete _return;
				_return = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case 'p':
		{
			FST::FST* _print = new FST::FST(PRINT(token));
			if (FST::execute(*_print))
			{
				Add(lexTable, { LEX_PRINT, str_number, LT_TI_NULLXDX });

				delete _print;
				_print = NULL;
				return true;
			}
			else
			{
				delete _print;
				_print = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}
		case '\'':
		{
			FST::FST* string_literal = new FST::FST(STRING_LITERAL(token));
			if (FST::execute(*string_literal))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
					Add(lexTable, { LEX_LITERAL, str_number, i });
				else
				{
					idTable.Add({ "\0", (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=') ? idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id : idTable.GetLexemaName() , IT::IDDATATYPE::STR, IT::IDTYPE::L,lexTable.size });
					idTable.table[idTable.size - 1].value.vstr.len = 0;
					int i = 0, j = 0;
					for (; token[i] != '\0'; i++)
					{
						idTable.table[idTable.size - 1].value.vstr.str[j] = token[i];
						idTable.table[idTable.size - 1].value.vstr.len++;
						j++;
					}
					idTable.table[idTable.size - 1].value.vstr.str[j] = '\0';

					Add(lexTable, { LEX_LITERAL, str_number,idTable.size - 1 });
				}

				delete string_literal;
				string_literal = NULL;
				return true;
			}
		}
		default:
		{
			FST::FST* number_literal = new FST::FST(INTEGER_LITERAL(token));
			if (FST::execute(*number_literal))
			{
				int i = idTable.IsId(token);
				if (i != LT_TI_NULLXDX)
					Add(lexTable, { LEX_LITERAL, str_number, i });
				else
				{
					idTable.Add({ "\0", (idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id[0] != '\0' && lexTable.GetEntry(lexTable.size - 1).lexema == '=') ? idTable.GetEntry(lexTable.GetEntry(lexTable.size - 2).idxTI).id : idTable.GetLexemaName() , IT::IDDATATYPE::INT, IT::IDTYPE::L , lexTable.size });
					idTable.table[idTable.size - 1].value.vint = atoi(token);
					Add(lexTable, { LEX_LITERAL,str_number, idTable.size - 1 });
				}
				delete number_literal;
				number_literal = NULL;
				return true;
			}
			else
			{
				delete number_literal;
				number_literal = NULL;

				return AnalyseIdentificator(token, str_number, lexTable, idTable, flag_type_variable);
			}
		}

		}
	}

	bool AnalyseIdentificator(char* token, const int str_number, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVar& flag_type_variable)
	{
		FST::FST* id = new FST::FST(IDENTIFICATOR(token));

		if (FST::execute(*id))
		{
			bool Checked_id = false;

			//Функция
			if (strcmp(token, "main") == 0 ||
				((lexTable.GetEntry(lexTable.size - 1).lexema == LEX_FUNCTION &&
					lexTable.GetEntry(lexTable.size - 2).lexema == 't') &&
					flag_type_variable.LT_posititon == lexTable.size - 2))
			{
				if (strcmp(token, "main") == 0)
				{
					for (int iter = 0; iter < idTable.size; iter++)
					{
						if (strcmp(idTable.GetEntry(iter).id, "main") == 0)
						{
							throw ERROR_THROW_IN(129, str_number, -1);
						}
					}
				}
				if (idTable.IsId(token) == -1)
				{
					if (flag_type_variable.type == TypeOfVar::INT)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F ,lexTable.size });
					}
					if (flag_type_variable.type == TypeOfVar::STR)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::STR, IT::IDTYPE::F ,lexTable.size });
					}
					if (strcmp(token, "main") == 0)
					{
						idTable.Add({ "\0", token, IT::IDDATATYPE::INT, IT::IDTYPE::F ,lexTable.size });
					}

					flag_type_variable.LT_posititon = -1;
					flag_type_variable.type = TypeOfVar::DEF;

					Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
					Checked_id = true;
				}
				else
					throw ERROR_THROW_IN(123, str_number, -1);
			}

			//Переменная
			if (!Checked_id && (lexTable.GetEntry(lexTable.size - 1).lexema == 't' && lexTable.GetEntry(lexTable.size - 2).lexema == LEX_DECLARE && flag_type_variable.LT_posititon == lexTable.size - 1))
			{
				bool LeftBrace = false;
				for (int i = lexTable.size - 1; i >= 0; i--)
				{
					if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
						LeftBrace = true;
					if (LeftBrace &&
						lexTable.GetEntry(i).lexema == LEX_ID &&
						idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
					{
						if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
						{
							if (flag_type_variable.type == TypeOfVar::INT)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token, IT::IDDATATYPE::INT, IT::IDTYPE::V, lexTable.size });
							}
							if (flag_type_variable.type == TypeOfVar::STR)
							{
								idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id, token , IT::IDDATATYPE::STR, IT::IDTYPE::V, lexTable.size });
							}
							flag_type_variable.LT_posititon = -1;
							flag_type_variable.type = TypeOfVar::DEF;

							Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
							Checked_id = true;
							break;
						}
						else
							throw ERROR_THROW_IN(125, str_number, -1);
					}


				}
			}

			//Параметр функции
			if (!Checked_id &&
				(lexTable.GetEntry(lexTable.size - 1).lexema == 't' && flag_type_variable.LT_posititon == lexTable.size - 1))
			{
				for (int i = lexTable.size - 1; i > 0; i--)
				{
					LT::Entry entry_minus_one = lexTable.GetEntry(i - 1);
					LT::Entry entry_minus_two = lexTable.GetEntry(i - 2);
					LT::Entry entry = lexTable.GetEntry(i);
					bool type_check = (idTable.GetEntry(entry.idxTI).idtype == IT::IDTYPE::F);
					if (entry.lexema == LEX_ID && type_check)
					{
						if (entry_minus_one.lexema == LEX_FUNCTION && entry_minus_two.lexema == 't')
						{
							if (idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id) == -1)
							{
								if (flag_type_variable.type == TypeOfVar::INT)
								{
									idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,token , IT::IDDATATYPE::INT, IT::IDTYPE::P, lexTable.size });
									idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
								}
								if (flag_type_variable.type == TypeOfVar::STR)
								{
									idTable.Add({ idTable.GetEntry(lexTable.GetEntry(i).idxTI).id,token  , IT::IDDATATYPE::STR, IT::IDTYPE::P, lexTable.size });
									idTable.table[(lexTable.GetEntry(i).idxTI)].parmQuantity++;
								}
								flag_type_variable.LT_posititon = -1;
								flag_type_variable.type = TypeOfVar::DEF;

								Add(lexTable, { LEX_ID, str_number, idTable.size - 1 });
								Checked_id = true;
								break;
							}
							else
								throw ERROR_THROW_IN(125, str_number, -1);
						}
					}
				}
			}

			//Идентификаторы с учётом области видимости
			if (!Checked_id)
			{
				bool LeftBrace = false;
				for (int i = lexTable.size - 1; i >= 0; i--)
				{
					if (lexTable.GetEntry(i).lexema == LEX_LEFTBRACE)
						LeftBrace = true;
					if (LeftBrace && lexTable.GetEntry(i).lexema == LEX_ID &&
						idTable.GetEntry(lexTable.GetEntry(i).idxTI).idtype == IT::IDTYPE::F)
					{
						int temp = idTable.IsId(token, idTable.GetEntry(lexTable.GetEntry(i).idxTI).id);
						if (temp != -1)
						{
							Add(lexTable, { LEX_ID,str_number,temp });
							break;
						}
						else
						{
							temp = idTable.IsId(token);
							if (idTable.GetEntry(temp).idtype != IT::IDTYPE::F)
							{
								token[5] = '\0';
							}
							if (temp != -1 && idTable.GetEntry(temp).idtype == IT::IDTYPE::F)
							{
								Add(lexTable, { LEX_ID,str_number,temp });
								break;
							}

							else throw ERROR_THROW_IN(126, str_number, -1);
						}
					}
				}
			}

			delete id;
			id = NULL;
			return true;
		}
		else
		{
			delete id;
			id = NULL;
			return false;
		}
	}
}