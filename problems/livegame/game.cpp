#include "gamemap.cpp"
#include <iostream>
#include <cstdlib>
using namespace std;

gameMap *map;



void init()
{
	srand(time(0));
	map=new gameMap(50,200,rand(),10);
}

int main()
{
	init();
	while(1)
	{
		map->printMap();
	}	
}
