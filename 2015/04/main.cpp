#include <iostream>
#include <string>
#include "md5.h"

int main(int argc, char* argv)
{
	const char* secretKey = "bgvyzdsv";
	const size_t valueSize = 50;
	size_t number = 0;
	bool foundIt = false;
	char value[valueSize + 1];

	do
	{
		sprintf_s(value, valueSize, "%s%zi", secretKey, number);
		std::string hash = md5(std::string(value));
		foundIt = true;
		for (int i = 0; i < 5 && foundIt; ++i)
		{
			foundIt = (hash[i] == '0');
		}

		if (!foundIt)
		{
			++number;
		}
	} while (!foundIt);

	std::cout << "Number = " << number;

	return 0;
}
