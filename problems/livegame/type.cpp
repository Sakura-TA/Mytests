#include <iostream>
#include <vector>
using namespace std;

class type
{
	char expr;
	int ticksPerMove;
	int sleepChance;
	vector<char> canWalkOn;
public:
	type(char e,int t,int s)
	{
		expr=e,ticksPerMove=t,sleepChance=s;
	}
	void addWalkable(char t)
	{
		canWalkOn.push_back(t);
	}
}
