#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>
#include<string.h>
#include<arpa/inet.h>
#include<strings.h>
#include<fstream>
using namespace std;
#define e -1
#define m 5
#define b 1024

char az[28][28];
char prev[28][28];
int req=0;
ofstream l_file;
int t=0;
void req_store(char r[b], string zo)
{
	req++;
	       if(req == 1)
          		l_file.open("sow.txt"); 
		else
			l_file.open("sow.txt", ios::app);       
        
	l_file<<"Client Request : "<<r<<"\n"<<zo.c_str()<<"\n\n";
   	
	l_file.close();
}

int Check_first(char a[28][28], int c, int bi)
{
 
    for(int i=1;i<27;i++)
	{
		if(a[c][i]=='+')
		{

			if(i==bi)
			{
				t=1;
				return t;
			}
			else
				Check_first(a, i, bi);
		}
	}
return t;
}

main(int argc, char** argv)
{
	struct sockaddr_in server;
	struct sockaddr_in client;	
	int sock,newp;
	int l=0,hu,j,g,opt,nope,k=1,z,up,fo=9090,ko,lo,bo,xo,co,mo,d=0,c=0,ff,ff1,i,p=0,q,sizz,re,fr,sec,res1,res2,ri;
	int sl=sizeof(struct sockaddr_in);
	char data[b];
	string dat,qw,sw,so,sop;	
	int bu[20];
	string wer="";

	while ((opt= getopt(argc,argv, "hp:l:"))!=-1)
	{

		switch (opt) 
		{
			case 'h':
				cout<<"−h: Print a usage summary with all options and exit.\n\n";
				cout<<"-p port-number : Listen on the given port. If not provided, dec_server will listen on port 9090.\n\n";
				cout<<"−l file: Log all requests and responses to the given file. If not, print all to stdout\n";
				break;
			case 'p':
				if(optarg==NULL)
					cout<<"No spec, default value 9090 is set\n";
				else
					fo=atoi(optarg);
				break;
			case 'l':
				hu=1;
				break;
		}
	} 	


	for(i=1;i<27;i++)
		for(j=1;j<27;j++)
			az[i][j]='.';

	az[0][0]='x';

	for(i=1;i<27;i++)
		az[i][0]=char(i+64);

	for(j=1;j<27;j++)
		az[0][j]=char(j+64);

		
	if((sock=socket(AF_INET, SOCK_STREAM, 0))==e)
	{
		perror("socket:");
		exit(-1);
	}
	
	memset(&server, 0, sizeof(server)); 
	server.sin_family=AF_INET;
	server.sin_port=htons(fo);
	server.sin_addr.s_addr=INADDR_ANY;
	
	if((bind(sock, (struct sockaddr*) &server, sizeof(server)))==e)
	{
		perror("connect:");
		exit(-1);
	}


	if((listen(sock, m))==e)
	{
		perror("listen:");
		exit(-1);
	}
	
	memset(&client, 0, sizeof(client)); 
	socklen_t len = sizeof(client);

	while(1)
	{
	
		if((newp=accept(sock, (struct sockaddr *)&client, &len))==-1)
		{
			perror("accept:");
			exit(-1);
		}
		else
		{
			l=recv(newp, data, b-1, 0);
			data[l]='\0';
			printf("Data received is %s\n", data);

				
			dat="";
			k=1;
			z=strlen(data);
			bu[0]=0;

				for(i=0;i<z;i++)
					if(data[i]==';')
					{
						bu[k]=i+2;
						k++;
					}
			k=k-1;
			bu[k]=z;

			string s[k];

				for(i=0;i<k;i++)
				{
					for(j=bu[i];j<bu[i+1];j++)
						s[i]+=data[j];
				}
			q=k;

			cout<<"Commands are as follows:\n";
		
				for(i=0;i<k;i++) 
				{
					cout<<i+1<<"."<<s[i];
					cout<<"\n";
				}
			j=0;
			sop="";

				while(j<q)
				{
					if(s[j].find("insert")==0)
					{
						ko=1;
						for(i=0;i<27;i++)
						{									
							for(int q=0;q<27;q++)
								prev[i][q]=az[i][q];
				
						}

 						so=s[j];
						for(i=7;i<s[j].size();i++)
						{
							if(so[i]!='-'&&so[i]!=' '&&so[i]!='>'&&so[i]!=';')
							{
								sop+=so[i];
							}
						}

					}
					j++;
					cout<<"\n";
				}

				for(int yu=0;yu<sop.size();yu+=2)
				{
					for(i=1;i<27;i++)
						if(az[i][0]==sop[yu])
						{
							co=i;
							break;
						}

					for(j=1;j<27;j++)
						if(az[0][j]==sop[yu+1])
						{
							mo=j;
							break;
						}

					nope=0;
					
					if(az[co][mo]=='.')
					{
						ff=Check_first(az,co,mo);
						t=0;
						if(ff==0)
						{
							ff1=Check_first(az,mo,co);
							t=0;
							if(ff1==0)
								az[co][mo]='+';
							else
								nope=1;
						}
						else
								ri=1;
					}

				}

				if(nope==1)
				{
					xo=1;
					cout<<"\nInsert not successful\n";
	
					for(i=0;i<27;i++)
					{									
						for(j=0;j<27;j++)
							az[i][j]=prev[i][j];
					
					}
				}
				cout<<"\nMatrix After Insertion:\n";
		
				for(i=0;i<27;i++)
				{									
					for(j=0;j<27;j++)
						cout<<az[i][j]<<" ";
						cout<<"\n";	
				}

				j=0;
				sw="";

				while(j<q)
				{
					if(s[j].find("query")==0)
					{	
						lo=1;
						qw=s[j];
							
						cout<<"Query asked: "<<s[j]<<"\n";
							
						for(int r=6;r<s[j].size();r++)
						{
							if(qw[r]!=' '&&qw[r]!=';')
							{
								sw+=qw[r];
							}
						}
					}
					j++;
				}

				for(int yu=0;yu<sw.size();yu+=2)
				{
					for(i=1;i<27;i++)
						if(az[i][0]==sw[yu])
						{
							co=i;
							break;
						}
	
					for(j=1;j<27;j++)
						if(az[0][j]==sw[yu+1])
						{
							mo=j;
							break;
						}

					fr=0,sec=0;

					for(i=1;i<27;i++)
					{
						if(fr==0&&az[co][i]=='+'||az[i][co]=='+')
							fr=1;
						if(sec==0&&az[mo][i]=='+'||az[i][mo]=='+')
							sec=1;
					}
					
					wer="";		
	
					if(fr==1&&sec==1)
					{
						res1=Check_first(az,co,mo);
						string v1,v2;		

						if(res1==1)
						{
							cout<<"Event "<<az[co][0]<<" Happened Before Event "<<az[0][mo]<<"\n";
							v1=az[co][0];
							v2=az[0][mo];
							wer+="Event "+v1+" Happened Before Event "+v2+"\n";
						}
						t=0;
		
						res2=Check_first(az,mo,co);

						if(res2==1)
						{
							cout<<"Event "<<az[0][mo]<<" Happened Before Event "<<az[co][0]<<"\n";
							v1=az[0][mo];
							v2=az[co][0];				
							wer+="Event "+v1+" Happened Before Event "+v2+"\n";
						}
						t=0;
				
						if(res1==0&&res2==0)
						{
							v1=az[co][0];
							v2=az[0][mo];
							wer+="The Queried Events "+v1+" and "+v2+" are concurrent\n";
							cout<<"The Queried Events "<<az[co][0]<<" and "<<az[0][mo]<<" are concurrent\n";
						}	
					}

					if(fr==0&&sec==0)
					{
						cout<<"The Queried Event was not found\n";
						wer+="The Queried Event was not found\n";
					}
					else if(sec==0)
					{
						cout<<"The Queried Event was not found\n";
						wer+="The Queried Event was not found\n";
					}

					else if(fr==0)
					{
						cout<<"The Queried Event was not found\n";
						wer+="The Queried Event was not found\n";
					}


				}				

				j=0;
				while(j<q)
				{		
					if(s[j].find("reset")==0)
					{
						bo=1;
						az[0][0]='x';
						for(i=1;i<27;i++)
							for(re=1;re<27;re++)
								az[i][re]='.';

						for(i=1;i<27;i++)
							az[i][0]=char(i+64);

						for(re=1;re<27;re++)
							az[0][re]=char(re+64);

						for(i=1;i<27;i++)
						{
							for(re=1;re<27;re++)
								cout<<az[i][re]<<" ";
								cout<<"\n";
						}
					}
					j++;
				}
			
				if(ko==1)
				{
					dat+="\nResponse from server: Insert Done\n";
					ko=0;
				}
				if(ri==1)
				{
					dat="";
					dat+="\nResponse from server: This is done\n";
					ri=0;
				}

				if(xo==1)
				{
					up=1;
					dat="";
					dat+="\nResponse from server: Insert not Successful\n";
					xo=0;
				}
				if(lo==1)
				{
					if(up==1)
					dat="";
					dat+="\nResponse from server: Query Done\n";
					dat+=wer;					
					lo=0;
				}
				if(bo==1)
				{
					if(up==1)
					dat="";
					dat+="\nResponse from server: Reset Done\n";
					bo=0;
				}
				
				if(hu==1)
					req_store(data, dat);
			
			sizz=dat.length();
		
		sendto(newp, dat.c_str(), sizz, 0, 0, 0);
			
	
		}// end else

	
	}//end while

close(newp);
close(sock);

} 	
	
