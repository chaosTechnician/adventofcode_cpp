#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;

typedef map<pair<int, int>, int> COORDMAP;

pair<int, int> Move(const pair<int, int> location, char direction);
void Deliver(const pair<int, int> location, COORDMAP* deliveries);


int main(int argc, char** argv)
{
	string line;

	ifstream file("input03.txt");
	if (file.is_open())
	{
		getline(file, line);
		file.close();
	}

	COORDMAP deliveries;
	pair<int, int> location(0, 0);

	Deliver(location, &deliveries);
	for (size_t i = 0; i < line.length(); ++i)
	{
		location = Move(location, line[i]);
		Deliver(location, &deliveries);
	}
	
	cout << deliveries.size() << " houses received presents." << endl;

	cout << "A wild Robo-Santa appeared!" << endl;

	COORDMAP newDeliveries;
	pair<int, int> santaLocation(0, 0);
	pair<int, int> roboSantaLocation(0, 0);

	Deliver(santaLocation, &newDeliveries);
	Deliver(roboSantaLocation, &newDeliveries);
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (i % 2 == 0)
		{
			santaLocation = Move(santaLocation, line[i]);
			Deliver(santaLocation, &newDeliveries);
		}
		else
		{
			roboSantaLocation = Move(roboSantaLocation, line[i]);
			Deliver(roboSantaLocation, &newDeliveries);
		}
	}

	cout << newDeliveries.size() << " houses received presents." << endl;

	return 0;
}

pair<int, int> Move(const pair<int, int> location, char direction)
{
	pair<int, int> newLocation = location;
	switch (direction)
	{
	case '^':
		++newLocation.second;
		break;
	case 'v':
		--newLocation.second;
		break;
	case '>':
		++newLocation.first;
		break;
	case '<':
		--newLocation.first;
		break;
	}

	return newLocation;
}

void Deliver(const pair<int, int> location, COORDMAP* deliveries)
{
	COORDMAP::iterator i = deliveries->find(location);
	if (i != deliveries->end())
	{
		++(deliveries->at(location));
	}
	else
	{
		deliveries->emplace(location, 1);
	}

	//return deliveries->at(location);
}
