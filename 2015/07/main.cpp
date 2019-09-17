#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>

void CheckSignals(std::string filename);

int main()
{
	CheckSignals("input07.txt");
	CheckSignals("input07b.txt");
}

void CheckSignals(std::string filename)
{
	std::string line;
	std::map<std::string, unsigned __int16> wire;

	int lastWireCount = 0;
	int wireCount = 0;

	do
	{
		lastWireCount = wireCount;
		wireCount = 0;
		std::fstream file(filename);
		while (getline(file, line))
		{
			// Tokenize
			std::istringstream myStream(line);
			std::string t1, t2, t3, t4, t5;
			
			bool bad = false;
	
			myStream >> t1;
			long int li = strtol(t1.c_str(), NULL, 10);
			if (li != 0L || t1 == "0") // It's a number
			{
				myStream >> t2;
				myStream >> t3;
				if (t2 == "->")				// 1 -> a
				{
					wire[t3] = (unsigned __int16)li;
					++wireCount;
				}
				else if (t2 == "AND")		// 1 AND a -> b
				{
					myStream >> t4;
					myStream >> t5;
					if (wire.count(t3) != 0)
					{
						wire[t5] = (unsigned __int16)li & wire[t3];
						++wireCount;
					}
				}
				else if (t2 == "LSHIFT")	// 1 LSHIFT 1 -> a
				{
					myStream >> t4;
					myStream >> t5;
					long int rs = strtol(t3.c_str(), NULL, 10);
					if (rs != 0L)
					{
						wire[t5] = (unsigned __int16)li << rs;
						++wireCount;
					}
					else
						bad = true;
				}
				else if (t2 == "OR")		// 1 OR a -> b
				{
					myStream >> t4;
					myStream >> t5;
					if (wire.count(t3) != 0)
					{
						wire[t5] = (unsigned __int16)li | wire[t3];
						++wireCount;
					}
				}
				else if (t2 == "RSHIFT")	// 1 RSHIFT 1 -> a
				{
					myStream >> t4;
					myStream >> t5;
					long int rs = strtol(t3.c_str(), NULL, 10);
					if (rs != 0L)
					{
						wire[t5] = (unsigned __int16)li >> rs;
						++wireCount;
					}
					else
						bad = true;
				}
			}
			else if (t1 == "NOT")		// NOT a -> b
			{
				myStream >> t2;
				myStream >> t3;
				myStream >> t4;
				if (wire.count(t2) != 0)
				{
					wire[t4] = ~wire[t2];
					++wireCount;
				}
			}
			else
			{
				myStream >> t2;
				if (t2 == "->")					// a -> b
				{
					myStream >> t3;
					if (wire.count(t1) != 0)
					{
						wire[t3] = wire[t1];
						++wireCount;
					}
				}
				else if (t2 == "AND")			// a AND b -> c
				{
					myStream >> t3;
					myStream >> t4;
					myStream >> t5;
					if (wire.count(t1) != 0 && wire.count(t3))
					{
						wire[t5] = wire[t1] & wire[t3];
						++wireCount;
					}
				}
				else if (t2 == "LSHIFT")	// a LSHIFT 1 -> b
				{
					myStream >> t3;
					myStream >> t4;
					myStream >> t5;
					if (wire.count(t1) != 0)
					{
						long int rs = strtol(t3.c_str(), NULL, 10);
						if (rs != 0L)
						{
							wire[t5] = wire[t1] << rs;
							++wireCount;
						}
						else
							bad = true;
					}
				}
				else if (t2 == "OR")		// a OR b -> c
				{
					myStream >> t3;
					myStream >> t4;
					myStream >> t5;
					if (wire.count(t1) != 0 && wire.count(t3))
					{
						wire[t5] = wire[t1] | wire[t3];
						++wireCount;
					}
				}
				else if (t2 == "RSHIFT")	// a RSHIFT 1 -> b
				{
					myStream >> t3;
					myStream >> t4;
					myStream >> t5;
					if (wire.count(t1) != 0)
					{
						long int rs = strtol(t3.c_str(), NULL, 10);
						if (rs != 0L)
						{
							wire[t5] = wire[t1] >> rs;
							++wireCount;
						}
						else
							bad = true;
					}
				}
			}
		}
		file.close();
	} while (lastWireCount != wireCount);

	std::cout << "Value on wire a: " << wire["a"] << std::endl;
}
