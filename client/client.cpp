#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<strings.h>
using namespace std;
#define e -1
#define b 1024

main(int argc, char** argv)
{
	int sock;
	string ipd="127.0.0.1";
	int f=9090;
	int opt;
cout<<"Client: Enter Command\n";

	while ((opt= getopt(argc,argv, "hs:p:"))!=-1)
	{
		switch (opt) 
		{
			case 'h':
				cout<<"−h : Print a usage summary with all options and exit.\n\n";
				cout<<"-s server-host : Connect to the specified host (by hostname or by IP address). If not provided, connect to the localhost.\n\n";
				cout<<"-p port-number: Connect to the server at the given port. If not provided, connect to 9090.\n";
			break;
			case 'p':
				if(optarg==NULL)
					cout<<"No spec, default value 9090 is set\n";
				else
					f=atoi(optarg);
				break;
			case 's':
				if(optarg==NULL)
					cout<<"No Specified Info, Localhost Set";
				else
					ipd=optarg;
				break;
		}
	} 			

	while(1)
	{
	
		char inp[b];
		gets(inp);
		struct sockaddr_in remote_server;
		memset(&remote_server, 0, sizeof(remote_server));
		remote_server.sin_family=AF_INET;
		remote_server.sin_addr.s_addr=inet_addr(ipd.c_str());
		remote_server.sin_port=htons(f);		
			
		int l;
	
			
			if((sock=socket(AF_INET, SOCK_STREAM, 0))==e)
			{
				perror("socket:");
				exit(-1);
			}
	
		char t='\n';
		char * p;
		int q,le;
			
			if(connect(sock, (struct sockaddr *) &remote_server, sizeof(remote_server))==e)
			{
				perror("connect:");
				exit(-1);
			}
		le=1024;
		p=inp; 
		
			while(le>0)
			{
				q=send(sock, p, le, 0);
				p=p+q;
				le=le-q;
			}
	
		char op[b];
		strcpy(op,"\0");
		l=recvfrom(sock, op, b, 0, 0, 0);
		op[l]='\0';
		printf("%s\n", op);

	}
	
	close(sock);	

} 	
