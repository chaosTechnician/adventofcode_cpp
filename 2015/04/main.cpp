#include <iostream>
#include <string>
#include "md5.h"

size_t FindNumber(const char* secretKey, size_t numberOfZeroes);

int main(int argc, char* argv)
{
	const char* secretKey = "bgvyzdsv";

	std::cout << "Number for 5 zeroes: " << FindNumber(secretKey, 5) << std::endl;
	std::cout << "Number for 6 zeroes: " << FindNumber(secretKey, 6) << std::endl;

	return 0;
}

size_t FindNumber(const char* secretKey, size_t numberOfZeroes)
{
	const size_t valueSize = 50;
	size_t number = 0;
	bool foundIt = false;
	char value[valueSize + 1];

	do
	{
		sprintf_s(value, valueSize, "%s%zi", secretKey, number);
		std::string hash = md5(std::string(value));
		foundIt = true;
		for (int i = 0; i < numberOfZeroes && foundIt; ++i)
		{
			foundIt = (hash[i] == '0');
		}

		if (!foundIt)
		{
			++number;
		}
	} while (!foundIt);

	return number;
}