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

void ChangeLights(bool* lights, int x1, int y1, int x2, int y2, Action action);

void TurnOffLights(int* lights);
void ChangeLights(int* lights, int x1, int y1, int x2, int y2, Action action);

int main(int argc, char* argv)
{
	std::string line;
	bool* lights = new bool[FIELD_WIDTH * FIELD_HEIGHT];
	ChangeLights(lights, 0, 0, FIELD_WIDTH - 1, FIELD_HEIGHT - 1, TurnOff);

	int* lightsWithBrightness = new int [FIELD_WIDTH * FIELD_HEIGHT];
	TurnOffLights(lightsWithBrightness);

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
			ChangeLights(lightsWithBrightness, x1, y1, x2, y2, TurnOn);
		}
		if (token == "off")
		{
			ChangeLights(lights, x1, y1, x2, y2, TurnOff);
			ChangeLights(lightsWithBrightness, x1, y1, x2, y2, TurnOff);
		}
		if (token == "toggle")
		{
			ChangeLights(lights, x1, y1, x2, y2, Toggle);
			ChangeLights(lightsWithBrightness, x1, y1, x2, y2, Toggle);
		}
	}
	file.close();

	int lightsCount = 0;
	int totalBrightness = 0;
	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		for (int y = 0; y < FIELD_HEIGHT; ++y)
		{
			if (lights[x * FIELD_HEIGHT + y])
			{
				++lightsCount;
			}

			totalBrightness += lightsWithBrightness[x * FIELD_HEIGHT + y];
		}
	}

	std::cout << lightsCount << " lights are on with the old plan." << std::endl;
	std::cout << "The total brightness from the new directions is " << totalBrightness << "." << std::endl;

	delete [] lights;
	lights = NULL;

	delete[] lightsWithBrightness;
	lightsWithBrightness = NULL;

	return 0;
}

void ChangeLights(bool* lights, int x1, int y1, int x2, int y2, Action action)
{
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			switch (action)
			{
			case TurnOn:
				lights[x * FIELD_HEIGHT + y] = true;
				break;
			case TurnOff:
				lights[x * FIELD_HEIGHT + y] = false;
				break;
			case Toggle:
				lights[x * FIELD_HEIGHT + y] = !lights[x * FIELD_HEIGHT + y];
				break;
			}
		}
	}
}

void TurnOffLights(int* lights)
{
	for (int x = 0; x < FIELD_WIDTH; ++x)
	{
		for (int y = 0; y < FIELD_HEIGHT; ++y)
		{
			lights[x * FIELD_HEIGHT + y] = 0;
		}
	}
}

void ChangeLights(int* lights, int x1, int y1, int x2, int y2, Action action)
{
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			switch (action)
			{
			case TurnOn:
				lights[x * FIELD_HEIGHT + y] += 1;
				break;
			case TurnOff:
				if (lights[x * FIELD_HEIGHT + y] > 0)
				{
					lights[x * FIELD_HEIGHT + y] -= 1;
				}
				break;
			case Toggle:
				lights[x * FIELD_HEIGHT + y] += 2;
				break;
			}
		}
	}
}