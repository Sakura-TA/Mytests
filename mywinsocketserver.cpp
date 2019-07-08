#include<winsock2.h>
#include<windows.h>
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#pragma comment(lib,"ws2_32.lib")
#define DEFAULTPORT 8000
#define MAXLINE 4096
using namespace std;

char buff[4096];
int n;
FILE outfile;
void sendstr(string s)
{
	send(sClient, (char *)s.data(), s.length(), 0);
}

void recvstr()
{
	n = recv(sClient, buff, 0);
	buff[n]='\0';
}

int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	SOCKET slisten = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		cout<<"socket error !"<<endl;
		return 0;
	}

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(DEFAULTPORT);
	servaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout<<"bind error !"<<endl;
	}

	if(listen(slisten, 5) == SOCKET_ERROR)
	{
		cout<<"listen error !"<<endl;
		return 0;
	}

	SOCKET sClient;
	struct sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	cout<<"======waiting for connection======"<<endl;
	while(1)
	{
		if(sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen) == INVALID_SOCKET)
		{
			cout<<"accept error !"<<endl;
			continue;
		}
		cout<<"Connection built: "<<inet_ntoa(remoteAddr.sin_addr))<<endl;
		recvstr();
		int type=buff[0];
		if(type=='f')
		{
			recvstr();
			char path[1000];
			strcpy(path,buff);
			outfile=fopen(path,"w");
			cout<<path<<endl;
		}
		recvstr();
		while(buff[0]!='E'||buff[1]!='O'||buff[2]!='F')
		{
			cout<<"recv:"<<buff<<endl;
			sendstr("Received\n");
			if(type=='f') fprintf(outfile, "%s\n",buff);
			recvstr();
		}
		sendstr("Fully received\n");
		if(type=='f') fclose(outfile);
		closesocket(sClient);
	}
	closesocket(slisten);
	WSACleanup();
	return 0;
}
