#include "stdafx.h"


int main()
{
	Deserializer deserializer = Deserializer();
	deserializer.DeserializeData();
	deserializer.ConvertToAssembler();

	return 0;
}