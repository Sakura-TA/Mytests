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



#define MAXLINE 4096



string defaultpath="//root//test//";

int sockfd,rec_len;

char sendline[4096],recvline[4096],buf[4096];

void sendstr()

{

	if( send(sockfd, sendline, strlen(sendline), 0) < 0)

	{

		cout<<"send msg error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;

		exit(0);

	}

}



void recvstr()

{

	if((rec_len = recv(sockfd, buf, MAXLINE,0)) == -1)

	{

		perror("recv error");

		exit(1);

	}

	buf[rec_len] = '\0';

	cout<<"Received: "<<buf<<endl;

}



void sendEOF()

{

	sendline[0]='E',sendline[1]='O',sendline[2]='F',sendline[3]='\0';

	sendstr();

}



void sendtype(char type)

{

	sendline[0]=type,sendline[1]='\0';

	sendstr();

}

int main(int argc, char** argv)

{

	int n;

	FILE *pFile;

	struct sockaddr_in	servaddr;

	string path,filename;

	char type=argv[2][0];

	if(argc < 3 || argc ==4 || (argc== 3 && type != 'm') || argc== 5 && type !='f')

	{

		cout<<"usage: ./msc <ipaddress> <type> [fileaddr] [outputaddr]"<<endl;

		cout<<"type: m send a message. f send a file."<<endl;

		cout<<type;

		exit(0);

	}



	if(type=='f')

	{

		path=argv[3];

		int index=0,i=0;

		while(i<path.length())

		{

			if(path[i]=='/'||path[i]=='\\') index=i;

			i++;

		}

		filename=path.substr(index);

		pFile = fopen((char *)path.data(),"r");

		if (pFile == NULL)

		{

			cout<<"Error opening file"<<endl;

			exit(0);

		}

	}



	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)

	{

		cout<<"create socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;

		exit(0);

	}



	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;

	servaddr.sin_port = htons(8000);

	if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <=0)

	{

		cout<<"inet_pton error for "<<argv[1]<<endl;

		exit(0);

	}



	if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)

	{

		cout<<"connect error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;

		exit(0);

	}

	sendtype(type);

	if(type=='m')

	{

		cout<<"send msg to server: "<<endl;

		fgets(sendline, 4096, stdin);

		sendstr();

		recvstr();

		sendEOF();

	}

	else

	{

		if(argv[4][0]=='0') strcpy(sendline,(char *)(defaultpath+filename).data());

		else strcpy(sendline,argv[4]);

		cout<<"filename: "<<filename<<endl;

		sendstr();

		cout<<"Trying to send file: "<<filename<<endl;

		while( fgets( sendline, 4096, pFile) != NULL )

		{

			cout<<"sent: "<<sendline<<endl;

			sendstr();

			recvstr();

		}

		sendEOF();

		recvstr();

		fclose(pFile);

	}		

	close(sockfd);

	exit(0);

}

