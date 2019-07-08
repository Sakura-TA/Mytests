#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;
//--------------------------------------------Const---------------------------------------------------
#define DEFAULT_PORT 8000
#define MAXLINE 4096
//----------------------------------------Const Variable----------------------------------------------
string defaultRecv="Received";
//------------------------------------------Variable--------------------------------------------------
int socket_fd, connect_fd;
char buff[4096];
int n;
FILE *outFile;
struct sockaddr_in	servaddr;

//-------------------------------------------Realize--------------------------------------------------
void initSocket()
{
}
bool acceptConnection()
{	
	if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
	{
		cout<<"accept socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		return 1;
	}
	return 0;
}
void sendStr(string s)
{
	if(send(connect_fd, (char *)s.data(),s.length(),0) == -1) perror("send error");
}

void recvStr()
{
	n=recv(connect_fd, buff, MAXLINE, 0);
	buff[n]= '\0';
}
bool checkEOF(char *chk){return !strcmp(chk,"EOF\n");}
void recvReq(int i)
{
	recvStr();
	sendStr(defaultRecv);
	if(i) cout<<"recv: "<<buff<<endl;
}
void sendReq(string s)
{
	sendStr(s);
	recvStr();
}
void endConnectSocket()
{
	if(!fork())
	{
		sendStr("Fully received\n");
		close(connect_fd);
	//	exit(0);
	}
	close(connect_fd);
}
bool execSys(string s)
{
	s=s+" >> tmp";
	pid_t status=system((char *)s.data());
	return(status == -1||(WIFEXITED(status)&&!WEXITSTATUS(status)));
}
//--------------------------------------------Mode----------------------------------------:W--------------
void anyLineMode()
{
	while(!checkEOF(buff))
	{
		recvReq(1);
	}
}

void commandMode()
{
	FILE *sendFile;
	string command;
	char tp[4096];
	while(1)
	{
		recvReq(1);
		command=buff;
		recvStr();
		if(checkEOF((char *)command.data())) break;
		if (!execSys(command))
		{
			sendReq("Error wrong command");
			sendReq("EOF");
			sendStr(defaultRecv);
			continue;
		}
		sendFile = fopen("tmp","r");
		while( fgets( tp, 4096, sendFile) != NULL)
		{
			command=tp;
			sendReq(command);
			if(!strcmp((char *)defaultRecv.data(),buff))
			{
				cout<<"Receiving msg Error: expecting \""<<defaultRecv<<"\",received \""<<buff<<"\""<<endl;
			exit(0);
			}
		}
		sendReq("EOF");
		sendStr(defaultRecv);
		fclose(sendFile);
	}
}	
void messageMode()
{
	recvReq(1);
}
void uploadMode()
{
	recvStr();
	char path[1000];
	strcpy(path,buff);
	outFile=fopen(path,"w");
	cout<<path<<endl;
	sendStr(defaultRecv);
	buff[0]='\0';
	recvReq(1);
	while(!checkEOF(buff))
	{
		fprintf(outFile,"%s",buff);
		recvReq(1);
	}
	fclose(outFile);

}
//--------------------------------------------Main------------------------------------------------------
int main(int argc, char** argv)
{
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(DEFAULT_PORT);
	if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		cout<<"create socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}
	if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
	{
		cout<<"bind socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}
	if( listen(socket_fd, 10) == -1)
	{
		cout<<"listen socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}
	cout<<"=====waiting for client's request======"<<endl;
	while(1)
	{

		if(acceptConnection()) continue;
		recvReq(1);
		int type=buff[0];
		switch(type)
		{
			case 'a':anyLineMode();break;
			case 'c':commandMode();break;
			case 'm':messageMode();break;
			case 'u':uploadMode();break;
		}
		 endConnectSocket();
	}
	close(socket_fd);
}
