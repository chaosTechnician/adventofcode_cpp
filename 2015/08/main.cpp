#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::ifstream file("input08.txt");
	std::string line;
	
	size_t totalCharactersInCode = 0;
	size_t totalCharacters = 0;
	size_t totalEncodedCharacters = 0;

	while (getline(file, line))
	{
		totalCharactersInCode += line.length();

		// Because we start with two double quotes, ignore first and last characters
		totalEncodedCharacters += 6; // To encode the double quotes and keep it in quotes
		for (size_t i = 1; i < line.length() - 1; ++i)
		{
			if (line[i] != '\\')
			{
				++totalCharacters;
				++totalEncodedCharacters;
			}
			else if (line[i + 1] == '\\' || line[i + 1] == '"')
			{
				++totalCharacters;
				++i;
				totalEncodedCharacters += 4;
			}
			else if (line[i + 1] == 'x')
			{
				++totalCharacters;
				i += 3;
				totalEncodedCharacters += 5;
			}
		}
	}

	size_t difference = totalCharactersInCode - totalCharacters;
	size_t encodedDifference = totalEncodedCharacters - totalCharactersInCode;
	std::cout << difference << std::endl;
	std::cout << encodedDifference << std::endl;
}
