#include <fstream>
#include <iostream>
#include <string>

bool isNice(std::string str);
bool isNiceNew(std::string str);

int main(int argc, char* argv)
{
	std::string line;
	size_t oldNiceCount = 0;
	size_t newNiceCount = 0;

	std::ifstream file("input05.txt");
	while (getline(file, line))
	{
		if (isNice(line))
		{
			++oldNiceCount;
		}

		if (isNiceNew(line))
		{
			++newNiceCount;
		}
	}
	file.close();

	std::cout << oldNiceCount << " strings are nice under the old rules." << std::endl;
	std::cout << newNiceCount << " strings are nice under the new rules." << std::endl;

	return 0;
}

bool isNice(std::string str)
{
	int vowelCount = 0;
	bool pairedLetters = false;
	bool isBad = false;

	for (size_t i = 0; i < str.length() && !isBad; ++i)
	{
		char c1 = str[i];
		if (c1 == 'a' || c1 == 'e' || c1 == 'i' || c1 == 'o' || c1 == 'u')
		{
			++vowelCount;
		}

		if (i < str.length() - 1)
		{
			char c2 = str[i + 1ul];
			if (c1 == c2)
			{
				pairedLetters = true;
			}

			if ((c1 == 'a' && c2 == 'b')
				|| (c1 == 'c' && c2 == 'd')
				|| (c1 == 'p' && c2 == 'q')
				|| (c1 == 'x' && c2 == 'y'))
			{
				isBad = true;
			}
		}
	}

	return !isBad && (vowelCount >= 3) && pairedLetters;
}

bool isNiceNew(std::string str)
{
	bool doublePair = false;
	bool repeatSkipOne = false;
	bool isNice = false;

	for (size_t i = 0; i < str.length() - 2 && !isNice; ++i)
	{
		char i0 = str[i];
		char i1 = str[i + 1ul];
		char i2 = str[i + 2ul];
		if (i0 == i2)
		{
			repeatSkipOne = true;
		}

		if (i < str.length() - 3)
		{
			for (size_t j = i + 2; j < str.length() - 1 && !doublePair; ++j)
			{
				char j0 = str[j];
				char j1 = str[j + 1ul];
				if (i0 == j0 && i1 == j1)
				{
					doublePair = true;
				}
			}
		}

		isNice = repeatSkipOne && doublePair;
	}

	return isNice;
}
