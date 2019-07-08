#include <iostream>
#include <vector>

using namespace std;

class commandsGroup
{
	string commandsName[100];
	void (*commandsAddr[100])();
	int top;
public:
	commandsGroup()
	{
		top=0;
	}
	void (*search(string s))()
	{
		for(int i=0;i<top;i++)
		{
			if(commandsName[i]==s) return commandsAddr[i];
		}
		cout<<"Command not found"<<endl;
		return commandsAddr[0];
	}
	void insert(string cmdName,void (*cmdAddr)())
	{
		commandsName[top]=cmdName;
		commandsAddr[top]=cmdAddr;
		top++;
		cout<<"read:"<<cmdName<<endl;
	}
};

void help()
{
	cout<<"This is ur help"<<endl;
}



void exit()
{
	exit(0);
}
commandsGroup cmdGroup;
void init()
{
//	for(void (*i)() =help;i!=init;i+=sizeof(i)) cout<<sizeof(i);       //failed
	cmdGroup.insert("help",help);
	cmdGroup.insert("exit",exit);

}

int main()
{
	init();
	string command;
	while(1)
	{
	//	cout<<command<<endl;
		cout<<"\033[33mbconsole$:\033[37m";
		cin>>command;
		(*cmdGroup.search(command))();		
	}
	cout<<endl;
}
