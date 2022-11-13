#include "stdafx.h"
#define BEGIN_SYMBOL '|'

namespace PolishNotation
{
	bool Stack::push(LT::Entry input)
	{
		if (this->current_size < this->max_count)
		{
			lexEntry* temp = new lexEntry(input, this->head);
			this->head = temp;
			this->current_size++;
		}
		else
			return false;
	}

	bool Stack::push(PolishNotation::lexEntry input)
	{
		if (this->current_size < this->max_count)
		{
			lexEntry* temp = new lexEntry(input, this->head);
			this->head = temp;
			this->current_size++;
		}
		else
			return false;
	}

	lexEntry* Stack::pop()
	{
		if (this->current_size != 0)
		{

			lexEntry temp(*this->head);
			delete this->head;
			this->head = temp.next;
			this->current_size--;

			return &temp;
		}
		else
			return 0;
	}

	char Stack::Last_element(IT::IdTable idTable)
	{
		if (this->head->lexema == 'v')
			return idTable.table[this->head->idxTI].value.operation;
		return this->head->lexema;
	}


	bool PolishNotation(int lt_position, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		PolishNotation::Stack* literals = new PolishNotation::Stack;
		PolishNotation::Stack* operators = new PolishNotation::Stack;

		operators->push({ BEGIN_SYMBOL, -1, -1 });

		bool flag = true;
		bool is_complete = false;
		LT::Entry temp;
		In::IN in_ex;

		for (int i = lt_position; flag;)
		{
			temp = lexTable.GetEntry(i);

			if (idTable.GetEntry(temp.idxTI).idtype == IT::IDTYPE::F)
			{
				LT::Entry temp_1;
				temp_1 = lexTable.GetEntry(i);
				temp_1.lexema = '\@';
				char buffer[ID_MAXSIZE];
				int parm_quantity = 0;
				i++;
				for (; lexTable.GetEntry(i).lexema != ')'; i++)
				{

					if (in_ex.code[lexTable.GetEntry(i).lexema] != in_ex.D)
					{
						parm_quantity++;
						temp = lexTable.GetEntry(i);
						literals->push(temp);
					}
				}
				_itoa_s(parm_quantity, buffer, 10);
				literals->push(temp_1);
				literals->push({ buffer[0],temp_1.sn,temp_1.idxTI });
				i++;
				continue;
			}
			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL)
			{
				literals->push(temp);
				i++;
				continue;
			}

			switch (operators->Last_element(idTable))
			{
			case BEGIN_SYMBOL:
			{
				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				if (temp.lexema == LEX_RIGHTHESIS) { flag = false; }
				if (temp.lexema == LEX_SEMICOLON) { is_complete = true; flag = false; }
				break;
			}
			case PLUS:
			case MINUS:
			{
				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTHESIS ||
						temp.lexema == LEX_SEMICOLON)
					{
						literals->push(*operators->pop());
						break;
					}
				}

				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
			}

			case STAR:
			case DIRSLASH:
			{
				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_RIGHTHESIS ||
						temp.lexema == LEX_SEMICOLON)
					{
						literals->push(*operators->pop());
						break;
					}
				}
				if (temp.lexema == LEX_LEFTHESIS)
				{
					operators->push(temp);
					i++;
					break;
				}
			}
			case LEX_LEFTHESIS:
			{
				if (temp.lexema == LEX_SEMICOLON) flag = false;

				if (temp.idxTI != -1)
				{
					if (idTable.table[temp.idxTI].value.operation == PLUS ||
						idTable.table[temp.idxTI].value.operation == MINUS ||
						idTable.table[temp.idxTI].value.operation == STAR ||
						idTable.table[temp.idxTI].value.operation == DIRSLASH)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				else
				{
					if (temp.lexema == LEX_LEFTHESIS)
					{
						operators->push(temp);
						i++;
						break;
					}
				}
				if (temp.lexema == LEX_RIGHTHESIS)
				{
					operators->pop();
					i++;
					break;
				}
			}
			default:
				flag = false;
			}
		}

		if (is_complete)
		{
			PolishNotation::lexEntry* temp;
			int count = literals->getCount();
			LT::Entry* temp_array = new LT::Entry[count];

			for (int i = count - 1; i >= 0; i--)
			{
				temp = literals->pop();
				if (temp)
				{
					temp_array[i] = *temp;
				}
			}

			for (int i = lt_position, j = 0; lexTable.table[i].lexema != LEX_SEMICOLON; i++)
			{
				if ((i - count) < lt_position)
					lexTable.table[i] = temp_array[j++];
				else
					lexTable.table[i] = { '#', lexTable.table[i].sn, -1};
			}

			delete[] temp_array;
			delete literals;
			delete operators;
			return true;
		}
		else
		{
			delete literals;
			delete operators;
			return false;
		}
	}
}