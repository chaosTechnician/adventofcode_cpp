#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum Action
{
	TurnOn,
	TurnOff,
	Toggle
};

const size_t FIELD_WIDTH = 1000;
const size_t FIELD_HEIGHT = 1000;

void ChangeLights(bool lights[FIELD_WIDTH][FIELD_HEIGHT], int x1, int y1, int x2, int y2, Action action);

int main(int argc, char* argv)
{
	std::string line;
	char command[10];
	bool lights[FIELD_WIDTH][FIELD_HEIGHT];
	ChangeLights(lights, 0, 0, FIELD_WIDTH - 1, FIELD_HEIGHT - 1, TurnOff);

	std::ifstream file("input06.txt");
	while (getline(file, line))
	{
		std::istringstream myStream(line);
		std::string token;
		int x1, y1, x2, y2;

		myStream >> token;
		if (token == "turn")
		{
			myStream >> token;
		}

		myStream >> x1;
		myStream.ignore(1);
		myStream >> y1;
		myStream.ignore(9); // " through ".length()
		myStream >> x2;
		myStream.ignore(1);
		myStream >> y2;

		if (token == "on")
		{
			ChangeLights(lights, x1, y1, x2, y2, TurnOn);
		}
		if (token == "off")
		{
			ChangeLights(lights, x1, y1, x2, y2, TurnOff);
		}
		if (token == "toggle")
		{
			ChangeLights(lights, x1, y1, x2, y2, Toggle);
		}
	}
	file.close();

	int lightsCount = 0;
	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		for (int y = 0; y < FIELD_HEIGHT; ++y)
		{
			if (lights[x][y])
			{
				++lightsCount;
			}
		}
	}

	std::cout << lightsCount << " lights are on." << std::endl;

	return 0;
}

void ChangeLights(bool lights[FIELD_WIDTH][FIELD_HEIGHT], int x1, int y1, int x2, int y2, Action action)
{
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			switch (action)
			{
			case TurnOn:
				lights[x][y] = true;
				break;
			case TurnOff:
				lights[x][y] = false;
				break;
			case Toggle:
				lights[x][y] = !lights[x][y];
				break;
			}
		}
	}
}