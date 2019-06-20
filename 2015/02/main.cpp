#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

inline int Min(int a, int b) { return (a <= b) ? a : b; }
int GetWrappingArea(int l, int w, int h);
int GetRibbonLength(int l, int w, int h);

int main(int argc, char** argv)
{
	int paperArea = 0;
	int ribbonLength = 0;
	string line;

	ifstream file("input02.txt");
	while (getline(file, line))
	{
		int l, w, h;
		if (sscanf(line.c_str(), "%ix%ix%i", &l, &w, &h))
		{
			paperArea += GetWrappingArea(l, w, h);
			ribbonLength += GetRibbonLength(l, w, h);
		}
	}
	file.close();

	cout << "Gifts require " << paperArea << " square feet of paper and " << ribbonLength << " feet of ribbon." << endl;
	return 0;
}

int GetWrappingArea(int l, int w, int h)
{
	int side1Area = l * w;
	int side2Area = w * h;
	int side3Area = l * h;
	int slackArea = Min(Min(side1Area, side2Area), side3Area);

	return 2 * side1Area + 2 * side2Area + 2 * side3Area + slackArea;
}

int GetRibbonLength(int l, int w, int h)
{
	int side1Perimeter = 2 * l + 2 * w;
	int side2Perimeter = 2 * w + 2 * h;
	int side3Perimeter = 2 * l + 2 * h;
	int shortestPerimeter = Min(Min(side1Perimeter, side2Perimeter), side3Perimeter);
	int volume = l * w * h;

	return shortestPerimeter + volume;
}
