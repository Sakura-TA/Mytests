#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argv,char **args)
{
	string cmd="";
	if(argv==2)
	{
		cmd="cat ",cmd+=args[1];
		system("clear");
		while(true)
		{	
			system((char *)cmd.data());
			usleep(100000);
		}
	}
}
