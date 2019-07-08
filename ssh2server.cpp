#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#define DEFAULT_PATH "/var/saved_ssh"
#define MAX_DATA 50
using namespace std;
int top=-1;
class server
{
public:
	int num=0;
	string addr="";
	string account="";
	string password="";
	string remarks="";
	void list()
	{
		cout<<"\033[36m["<<num<<"]"<<endl
		    <<"ip       :"<<addr<<endl
		    <<"account  :"<<account<<endl
		    <<"password :\""<<password<<'\"'<<endl
		    <<"remarks  :"<<remarks<<"\033[0m"<<endl;
	}
	void connect()
	{
		string s="";
		s=s+"sshpass -p \""+password+"\" ssh "+account+"@"+addr;
		system((char*)s.data());
	}
};
server serverinfo[MAX_DATA];
void init()
{
	ifstream fi;
	fi.open(DEFAULT_PATH,ios::in);
	while(fi>>serverinfo[++top].addr&&serverinfo[top].addr!="EOF")
	{
		serverinfo[top].num=top;
		fi>>serverinfo[top].account>>serverinfo[top].password;
		getline(fi,serverinfo[top].remarks);
		getline(fi,serverinfo[top].remarks);
	}
	top--;
}

void del()
{
	int num;
	cout<<"\033[34mSelect a server :\033[0m";
	cin>>num;
	cout<<"\033[36m-------Del info--------"<<endl;
	serverinfo[num].list();
	cout<<"Are you sure?(y/n)";
	string ack;
	cin>>ack;
	if(ack[0]=='y'||ack[0]=='Y')
	{
		cout<<"\033[32mAccepted\033[0m"<<endl;
		memcpy(&serverinfo[num],&serverinfo[num+1],sizeof(serverinfo)*(top-num));
		top--;
	}
	else cout<<"\033[31mCanceled\033[0m"<<endl;
}
void add()
{
	char ip[4];
	cout<<"\033[34m--------New Server-------\nip :\033[0m";
	cin>>serverinfo[++top].addr;
	cout<<"\033[34mLogin Account :\033[0m";
	cin>>serverinfo[top].account;
	cout<<"\033[34mPassword :\033[0m";
	cin>>serverinfo[top].password;
	cout<<"\033[34mRemarks :\033[0m";
	getchar();
	getline(cin,serverinfo[top].remarks);
	serverinfo[top].list();
	cout<<"Are you sure?(y/n)";
	string ack;
	cin>>ack;
	if(ack[0]=='y'||ack[0]=='Y') cout<<"\033[32mAccepted\033[0m"<<endl;
	else cout<<"\033[31mCanceled\033[0m"<<endl,top--;
}


void save()
{
	ofstream fi;
	fi.open(DEFAULT_PATH,ios::out);
	for(int i=0;i<=top;i++)
	{
		fi<<serverinfo[i].addr<<" "<<serverinfo[i].account<<" "<<serverinfo[i].password<<endl<<serverinfo[i].remarks<<endl;
	}
	fi<<"EOF";
}
int main(int argc,char** argv)
{
	init();
	if(argc==2&&argv[1][0]=='l')
	{
		for(int i=0;i<=top;i++)
		{
			serverinfo[i].list();
		}
	}
	else if(argc==2&&argv[1][0]>='0'&&argv[1][0]<='9')
	{
		int num=0;
		for(char *i=argv[1];*i!='\0';i++)
		{
			num*=10;
			num+=*i-'0';
		}
		if(num>top||num<0)
		{
			cout<<"No such server"<<endl;
			exit(0);
		}
		serverinfo[num].connect();
	}
	else if(argc==2&&argv[1][0]=='a') add();
	else if(argc==2&&argv[1][0]=='d') del();
	else
	{
		cout<<"Usage: ssh2server [No./a/l]"<<endl
		    <<"a: add a new server"<<endl
		    <<"d: delete selected server"<<endl
		    <<"l: list all saved server-info"<<endl;
	}
	save();
}

