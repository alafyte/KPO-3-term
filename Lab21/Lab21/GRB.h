#pragma once
#include "Error.h"


typedef short GRBALPHABET;
namespace GRB
{
	struct Rule							//������� � ���������� �������
	{
		GRBALPHABET nn;							//����������� (����� ������ �������) < 0
		int iderror;							//������������� ���������������� ���������
		short size;								//���������� ������� - ������ ������ �������
		struct Chain							//�������(������ ����� �������)
		{
			short size;						//����� �������
			GRBALPHABET* nt;				//������� ���������� (>0) � �������������� (<0) 
			Chain()
			{
				this->size = 0; 				//���������� �������� � �������
				this->nt = 0;					//������� (�������� ��� ����������)
			};
			Chain(short psize, GRBALPHABET s, ...);						//���-�� �������� � �������/�������(��������� � �����������)
			char* getCChain(char* b);									//�������� ������ ������� �������
			static GRBALPHABET T(char t) { return GRBALPHABET(t); };	//��������
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };	//�� ��������
			static bool isT(GRBALPHABET s) { return s > 0; };			//��������?
			static bool isN(GRBALPHABET s) { return !isT(s); };			//�� ��������?
			static char alphabet_to_char(GRBALPHABET s)					//GRBALPHABET->char (��������� �� ��������� � ���� �������)
			{
				return isT(s) ? char(s) : char(-s);
			};
		}*chains;			//������ ������� - ������ ������ �������
		Rule()
		{
			this->nn = 0x00;
			this->size = 0;
		}
		Rule(GRBALPHABET pnn, int iderroe, short psize, Chain c, ...);
		//(����������(< 0); ������������� ���������������� ����� - �; ��� - �� ������� - ������ ������ �������; ��������� ������� - ������ ������ �������)
		char* getCRule(char* b, short nchain); //�������� ������� � ���� N->������� (��� ����������) (�����;����� �������(������ �����) � �������)
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j); //�������� ��������� �� j ���������� �������, ������� � ����� ��� -1 (������ ������ �������;������������ �������; ����� �������)
	};
	struct Greibach					//���������� �������
	{
		short size;						//���������� ������
		GRBALPHABET startN;				//��������� ������
		GRBALPHABET stbottomT;			//��� �����
		Rule* rules;					//��������� ������
		Greibach() { this->size = 0; this->startN = 0; this->stbottomT = 0; this->rules = 0; };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule);
		Rule getRule(short n);
	};
	Greibach getGreibach();
}

