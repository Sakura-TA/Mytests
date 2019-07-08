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

#define DEFAULT_PORT 8000
#define MAXLINE 4096
int socket_fd, connect_fd;
char buff[4096];
int n;
FILE *outfile;
void sendstr(string s)
{
	if(send(connect_fd, (char *)s.data(),s.length(),0) == -1) perror("send error");
}

void recvstr()
{
	n=recv(connect_fd, buff, MAXLINE, 0);
	buff[n]= '\0';
}

int main(int argc, char** argv)
{
	struct sockaddr_in	servaddr;
	if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		cout<<"create socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
		exit(0);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(DEFAULT_PORT);

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
		if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
		{
			cout<<"accept socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
			continue;
		}
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
			if(type=='f') fprintf(outfile,"%s\n",buff);
			recvstr();
		}
		if(!fork())
		{
			sendstr("Fully received\n");
			if(type=='f') fclose(outfile);
			close(connect_fd);
		//	exit(0);
		}
		close(connect_fd);
	}
	close(socket_fd);
}
