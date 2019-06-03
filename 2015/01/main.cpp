#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int FindFinalFloor(const string& map, int startingFloor = 0);
int FindFirstBasementPosition(const string& map, int startingFloor = 0);
int GetNextFloor(int currentFloor, char nextDirection);

int main(int argc, char** argv)
{
	string line;

	ifstream file("input01.txt");
	if (file.is_open())
	{
		getline(file, line);
		file.close();
	}

	cout << "Ended on floor " << FindFinalFloor(line) << "." << endl;

	int pos = FindFirstBasementPosition(line);
	if (pos >= 0)
		cout << "First went into the basement at position " << pos << "." << endl;
	else
		cout << "Never went into the basement." << endl;
}

int FindFinalFloor(const string& map, int startingFloor)
{
	int floor = startingFloor;
	for (size_t i = 0; i < map.length(); ++i)
	{
		floor = GetNextFloor(floor, map[i]);
	}

	return floor;
}

int FindFirstBasementPosition(const string& map, int startingFloor)
{
	int floor = startingFloor;
	int position = 0;
	while (floor >= 0 && position < map.length())
	{
		floor = GetNextFloor(floor, map[position++]);
	}

	if (floor < 0)
		return position;
	
	return -1;
}

int GetNextFloor(int currentFloor, char nextDirection)
{
	switch (nextDirection)
	{
	case '(':
		return currentFloor + 1;
		break;
	case ')':
		return currentFloor - 1;
		break;
	}

	return currentFloor;
}