#include "stdafx.h"
#include "FST.h"

int _tmain(int argc, TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	char str1[] = "abbf";
	char str2[] = "abcdbf";
	char str3[] = "abbbcebbf";
	char str4[] = "abcecebbbbf";
	char str5[] = "abbcdcdbbbf";
	char str6[] = "abbbbcdcdcdcdbbbbbbf";
	char str7[] = "abcebf";
	char str8[] = "abcdcf";
	char str9[] = "abcddbf";

	char* chains[] = { str1, str2, str3, str4, str5, str6, str7, str8, str9 };

	for (int i = 0; i < sizeof(chains) / sizeof(char*); i++)
	{
		FST::FST fst(chains[i], 6,
			FST::NODE(1, FST::RELATION('a', 1)),
			FST::NODE(3, FST::RELATION('b', 1), FST::RELATION('b', 4), FST::RELATION('c', 2)),
			FST::NODE(2, FST::RELATION('d', 3), FST::RELATION('e', 3)),
			FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('c', 2)),
			FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('f', 5)),
			FST::NODE()
		);

		if (FST::execute(fst))
			std::cout << "Цепочка " << fst.string << " распознана" << std::endl;
		else std::cout << "Цепочка " << fst.string << " не распознана" << std::endl;
	};
	//Пример из условия лабораторной работы
	/*char str1[] = "aaabbbaba";
	char str2[] = "aaabbbabba";*/
	//FST::FST fst1(str1, 4, FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
	//	FST::NODE(1, FST::RELATION('b', 2)), 
	//	FST::NODE(1, FST::RELATION('a', 3)),
	//	FST::NODE()
	//	);

	//if (FST::execute(fst1)) // выполнить разбор
	//	std::cout << "Цепочка " << fst1.string << " распознана" << std::endl;
	//else std::cout << "Цепочка " << fst1.string << " не распознана" << std::endl;

	//FST::FST fst2(
	//	str2,
	//	4,
	//	FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),
	//	FST::NODE(1, FST::RELATION('b', 2)),
	//	FST::NODE(1, FST::RELATION('a', 3)),
	//	FST::NODE()
	//	);

	//if (FST::execute(fst2)) // выолнить разбор
	//	std::cout << "Цепочка " << fst2.string << " распознана"<< std::endl;
	//else std::cout << "Цепочка " << fst2.string << " не распознана"<< std::endl;

	system("pause");
	return 0;
}
