#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;
//---------------------------------------------Const---------------------------------------------------------
#define MAXLINE 4096
//-----------------------------------------Const Variable----------------------------------------------------
string linuxdefaultpath="//root//test//";
string windefaultpath="D:\\test\\";
string defaultRecv="Received";
//--------------------------------------------Variable-------------------------------------------------------
int sockfd,rec_len,n;
char sendline[4096],recvline[4096],buf[4096];
struct sockaddr_in	servaddr;

//----------------------------------------------Info---------------------------------------------------------
void printUsage()
{
	cout<<"usage: ./msc <ipaddress> <type>"<<endl;
	cout<<"type:"<<endl;
	cout<<"a : customized send massage,end with \"EOF\""<<endl;
	cout<<"c : shell mode of type-a,end with \"EOF\""<<endl;
	cout<<"m [msg] : send a massage."<<endl;
	cout<<"f [inpath] [outpath] :send a file."<<endl;
}
//--------------------------------------------Realize--------------------------------------------------------
void startSocket(char *ip)
{
	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout<<"create socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	if( inet_pton(AF_INET, ip, &servaddr.sin_addr) <=0)
	{
		cout<<"inet_pton error for "<<ip<<endl;
		exit(0);
	}

	if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		cout<<"connect error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}

}
void insertStr(string s){strcpy(sendline,(char *)s.data());}
void sendStr()
{
	if( send(sockfd, sendline, strlen(sendline), 0) < 0)
	{
		cout<<"send msg error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}
}

void recvStr()
{
	if((rec_len = recv(sockfd, buf, MAXLINE,0)) == -1)
	{
		perror("recv error");
		exit(1);
	}
	buf[rec_len] = '\0';
	cout<<"Received: "<<buf<<endl;
}
bool checkRecv(string chk){return !strcmp((char *)chk.data(),buf);}

void sendReq(string req,string chk)
{
	insertStr(req);
	sendStr();
	recvStr();
	cout<<"sent :"<<req<<endl;
	if(!checkRecv(chk))
	{
		cout<<"Receiving msg Error: expecting \""<<chk<<"\", received \""<<buf<<"\""<<endl;
		exit(0);
	}
}
void recvReq(string chk)
{
	recvStr();
	insertStr(chk);
	sendStr();
}
void sendEOF()
{
	sendline[0]='E',sendline[1]='O',sendline[2]='F',sendline[3]='\0';
	sendStr();
	recvStr();
}
bool checkEOF(char * chk){cout<<strcmp(chk,"EOF");return !strcmp(chk,"EOF");}
//---------------------------------------------Mode---------------------------------------------------------------
void anyLineMode()
{
	string tp;
	cout<<"send msg to server: "<<endl;
	while(1)
	{
		fgets(sendline, 4096, stdin);
		sendStr();
		recvStr();
		tp=sendline;
		if(tp=="EOF") break;
	}
}
void commandMode()
{
	cout<<"input commands here: "<<endl;
	while(1)
	{
		fgets(sendline,4096,stdin);
		if(checkEOF(sendline))
		{
			sendEOF();
			break;
		}
		sendReq(sendline,defaultRecv);
		insertStr(defaultRecv);
		sendStr();
		while(!checkEOF(buf))
		{
			recvReq(defaultRecv);
		//	cout<<buf<<endl;
		}
		recvStr();
		if(!checkRecv(defaultRecv))
		{
			cout<<"Receiving msg Error: expecting \""<<defaultRecv<<"\", received \""<<buf<<"\""<<endl;
			exit(0);
		}
	}
}
void messageMode(string msg)
{
	sendReq(msg,defaultRecv);
}
void uploadMode(string path,string dir)
{
	FILE *sendFile;
	string fileName;
	int index=0;

	int i;
	while(i<path.length())
	{
		if(path[i]=='/'||path[i]=='\\') index=i;
		i++;
	}
	fileName=path.substr(index);
	sendFile = fopen((char *)path.data(),"r");
	if (sendFile == NULL)
	{
		cout<<"Error opening file"<<endl;
		exit(0);
	}


	if(dir=="l") dir=linuxdefaultpath+fileName;
	else if(dir=="w") dir=windefaultpath+fileName;
	sendReq(dir,defaultRecv);
	cout<<"Trying to send file: "<<fileName<<endl;
	while( fgets( sendline, 4096, sendFile) != NULL )
	{
		cout<<"sent: "<<sendline<<endl;
		sendStr();
		recvStr();
		if(!checkRecv(buf))
		{
			cout<<"Receiving msg Error: expecting \""<<defaultRecv<<"\", received \""<<buf<<"\""<<endl;
			exit(0);
		}
	}
	sendEOF();
	fclose(sendFile);
}
//---------------------------------------------Main----------------------------------------------------------------
int main(int argc, char** argv)
{
	string type=argv[2];
	if(argc < 3 ||(argc == 3 && type[0]!= 'c' && type[0]!='a')|| (argc== 4 && type[0]!= 'm') || (argc== 5 && type[0]!='u'))
	{
		printUsage();
		cout<<type;
		exit(0);
	}
	cout<<type[0]<<endl;
	startSocket(argv[1]);
	sendReq(type,defaultRecv);
	switch(type[0])
	{
		case 'a':anyLineMode();break;
		case 'c':commandMode();break;
		case 'm':messageMode(argv[3]);break;
		case 'u':uploadMode(argv[3],argv[4]);break;
	}
	close(sockfd);
	exit(0);
}
