#include <iostream>
#include <unistd.h>

using namespace std;



int main(int argv,char **args)
{
	string cmd="";
	if(argv==3)
	{
		cmd=args[1],cmd+=" > ",cmd+=args[2];
		system((char *)cmd.data(
}
