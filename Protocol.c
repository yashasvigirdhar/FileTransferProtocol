/*
   Sudhanshu Shekhar and Shashank Yadav
   */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
int timeToclose;
int childPid;
int fd[2];



int toDownload(char * str)
{
	if(strlen(str)>2 && str[0]=='D' && str[1]==' ')
		return 1;

	return 0;
}

void uclient( int c1){
	int connected, bytes_recieved,addr_len;  
	char sendto_data [1024],recvfrom_data[1024];
	char regex[100];
	char fileName[100];
	struct hostent *host;
	struct sockaddr_in server_addr;  
	//host = gethostbyname("127.0.0.1");
	host= (struct hostent *) gethostbyname((char *)"127.0.0.1");
	//gives me the socket
	if ((connected = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket");
		fprintf(stderr,"fck\n");
		exit(1);
	}


	server_addr.sin_family = AF_INET;     
	server_addr.sin_port = htons(c1);   
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	//bzero(&(server_addr.sin_zero),8); 

	addr_len = sizeof(struct sockaddr);

	/*	//establishes connection bw client and server
	 */


	char *pch;
	char copy[1024];
	while(1)
	{
		gets(sendto_data); // DATA which is got in the input buffer
		//printf("wtf %s\n",sendto_data);
		
shortcut :		
		strcpy(copy,sendto_data);
		pch = strtok (copy," ");

		//=======================    	IndexGet =================================
		if(pch!=NULL)
		{
			if(strcmp(pch,"FileHash")==0)
				{
					pch = strtok (NULL, " ");
					if(pch !=NULL)
					{
						if(strcmp(pch,"Verify")==0)
						{
							pch = strtok (NULL, " ");
							if(pch!=NULL)
							{
								strcpy(sendto_data,"FV");
								strcat(sendto_data,pch);
								printf("sendto_data : %s\n",sendto_data);
								sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
								while(1)
								{
									bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
									recvfrom_data[bytes_recieved] = '\0';
									if(strcmp(recvfrom_data,"End Of File") == 0)break;
									fwrite(recvfrom_data,1,bytes_recieved,stdout);
									/*if(recvfrom_data[0]=='A' && recvfrom_data[1]=='N' && recvfrom_data[2]=='S')
									{
										printf("\nANS MD5 CAUGHT\n");
										char arr[100];
										strncpy(arr,recvfrom_data+4,strlen(recvfrom_data)-1);
						
										//file to be received here
						
										printf("\n%s\n",arr);
										fflush(stdout);
										break;
									}*/
									
								}
								printf("\nout now\n");
								continue;
							}
						
						}
						else if(strcmp(pch,"CheckAll")==0)
						{
							strcpy(sendto_data,"FC");
							sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
							while(1)
							{
								bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
								recvfrom_data[bytes_recieved] = '\0';
								if(strcmp(recvfrom_data,"End Of File") == 0)break;
									fwrite(recvfrom_data,1,bytes_recieved,stdout);
									
								/*if(recvfrom_data[0]=='A' && recvfrom_data[1]=='N' && recvfrom_data[2]=='S')
								{
									printf("\nANS MD5 checkall CAUGHT\n");
									char arr[100];
									strncpy(arr,recvfrom_data+4,strlen(recvfrom_data)-1);
							
									//file to be received here
						
									printf("\n%s\n",arr);
									fflush(stdout);
									break;
								}*/
							}
							printf("\nout now\n");
							continue;
						}
					}
					else printf("wrong usage of FileHash\n");
				}
			else if(strcmp(pch,"IndexGet")==0)	
			{
				printf ("%s\n",pch);
				pch = strtok (NULL, " ");
				if(pch!=NULL)
				{
				//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Indexget ShortList >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	Add Before Regex
					if(strcmp(pch,"ShortList")==0)
					{
						pch = strtok (NULL, " ");
						if(pch!=NULL)
						{
							strcpy(sendto_data,"IS");
							strcat(sendto_data,pch);
							pch = strtok (NULL, " ");
							if(pch!=NULL)
							{
								strcat(sendto_data," ");
								strcat(sendto_data,pch);
								printf("sendto_data : %s\n",sendto_data);
								sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
					
								//replace this with fiel catcher 
								while(1)
								{
									bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
									recvfrom_data[bytes_recieved] = '\0';
									if(strcmp(recvfrom_data,"End Of File") == 0)break;
									fwrite(recvfrom_data,1,bytes_recieved,stdout);
						
								}
								printf("\nout now\n");
								continue;
							}
						}		
					}
				//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TILL HERE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
					
				//=======================    	IndexGet Regex   =================================
				if(strcmp(pch,"Regex")==0)
				{
					pch = strtok (NULL, " ");
					if(pch!=NULL)
					{
					strcpy(sendto_data,"IR");
					strcat(sendto_data,pch);
					printf("sendto_data : %s\n",sendto_data);
					sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
					
					//replace this with fiel catcher 
					while(1)
					{
						bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
						recvfrom_data[bytes_recieved] = '\0';
						if(strcmp(recvfrom_data,"End Of File") == 0)break;
						fwrite(recvfrom_data,1,bytes_recieved,stdout);
						
						/*if(recvfrom_data[0]=='A' && recvfrom_data[1]=='N' && recvfrom_data[2]=='S')
						{
							printf("\nANS REGEX CAUGHT\n");
							char arr[100];
							strncpy(arr,recvfrom_data+4,strlen(recvfrom_data)-1);
						
							//file to be received here
						
							printf("\n%s\n",arr);
							fflush(stdout);
							break;
						}*/
					}
					printf("\nout now\n");
					continue;
					}
					else
					{
						printf("no filename given\n");
					}
				}
				
			//=======================    	IndexGet LongList   =================================	
			
			//if(strcmp(copy,"IndexGet LongList")==0 )
				else if(strcmp(pch,"LongList")==0)
				{
					strcpy(sendto_data,"IL");
					printf("------SENDING IL\n");
					sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(server_addr)); 
					printf("------ready to receive file\n");
					/*bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
						recvfrom_data[bytes_recieved] = '\0';
						printf("%s\n",recvfrom_data);
						fflush(stdout);*/
					while(1)
					{
						//printf("\nstuck 181\n");
						bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
						recvfrom_data[bytes_recieved] = '\0';
						
						/*printf("%s\n",recvfrom_data);
						fflush(stdout);*/
						if(strcmp(recvfrom_data,"End Of File") == 0)break;
							fwrite(recvfrom_data,1,bytes_recieved,stdout);
						
						/*if(recvfrom_data[0]=='A' && recvfrom_data[1]=='N' && recvfrom_data[2]=='S')
						{
							printf("\nANS Longlist CAUGHT\n");
							char arr[100];
							strncpy(arr,recvfrom_data+4,strlen(recvfrom_data)-1);
						
							//file to be received here
						
							printf("\n%s\n",arr);
							fflush(stdout);
							break;
						}*/
						
					}
					printf("\nout now\n");
					continue;
					}
				}
				}
			
			else if(strcmp(pch,"Upload") == 0)
			{
				pch = strtok (NULL, " ");
				//	strcpy(sendto_data,"IR");
				char arr[100];
				strcpy(arr,pch);
				//strcat(arr,pch);
				printf("opening %s\n",arr);
					
				strcpy(sendto_data,"U ");
				strcat(sendto_data,pch);
				sendto(connected, sendto_data, 1024, 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
//=================adding protocol=====================

				//===================ending protocol==================
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				/*FILE *fp = fopen(arr,"r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

					fflush(stdout);
					//void *temp = data;
					sentN =  sendto(connected, sendto_data, 1024, 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(connected, sendto_data, 1024, 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
				fclose(fp);

*/
			}
			else if(strcmp(pch,"Download") == 0)
			{
				pch = strtok (NULL, " ");
				if(pch!=NULL)
				{
					strcpy(sendto_data,"D ");
				strcat(sendto_data,pch);
				sendto(connected, sendto_data, 1024, 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
				
			printf("printing %s\n",pch);
			// sendto(connected,recvfrom_data,1024,0);

			FILE *fp1 = fopen(pch,"wb");
			//char dup[1024];
			memset(recvfrom_data,0,1024);
			while(1){
				//bytes_recieved=read(connected,recvfrom_data,1024);
				bytes_recieved=recvfrom(connected,recvfrom_data,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
				recvfrom_data[bytes_recieved] = '\0';
				printf("got %s number %d-----\n",recvfrom_data,bytes_recieved);

				if(strcmp(recvfrom_data,"End Of File")==0)
				{
					break;
				}	
				//else break;
				fwrite(recvfrom_data, 1,bytes_recieved, fp1);
				
				//sleep(1);
			}
			printf("File closed\n");
			fclose(fp1);
			}
				
				else printf("Wrong use of download");
				
			}
			else if(strcmp(pch,"Allow") == 0)
			{	
				
				close(fd[1]);
				int nbytes = read(fd[0],fileName,sizeof(fileName));
				strcpy(sendto_data,"Download ");
				strcat(sendto_data,fileName);
				goto shortcut;
			}
			else if(strcmp(pch,"Stop") == 0)
			{
				//close(fd[1]);
				printf("Process stopped\n");
			}
			else{
				//normal text===================================================
				if ((strcmp(sendto_data , "q") == 0 || strcmp(sendto_data , "Q") == 0) || timeToclose ==1)
				{
					if(timeToclose)printf("bbye\n");
					sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr)) ;
					fflush(stdout);
					close(connected);
					exit(0);
					break;
				}

				else
					sendto(connected, sendto_data, strlen(sendto_data), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
			}

		}


	}
	return;
}

void userver(int s1){
	int sock, connected, true = 1,bytes_recieved,addr_len;  
	char sendto_data [1024],recvfrom_data[1024],copy[1024];       
	char regex[100];
	struct sockaddr_in server_addr,client_addr;    
	int sin_size;

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	//int s1;

	server_addr.sin_family = AF_INET;         
	server_addr.sin_port = htons(s1);     
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	//bzero(&(server_addr.sin_zero),8); 
	//binded socket to required port
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
			== -1) {
		perror("Unable to bind");
		exit(1);
	}

	printf("till here\n");
	/*if (listen(sock, 5) == -1) {
		perror("Listen");
		exit(1);
	}*/
	addr_len = sizeof(struct sockaddr);

	printf("\nUDPServer Waiting for client on port 5000");
	fflush(stdout);



	//sin_size = sizeof(struct sockaddr_in);
	//connected represents the client server connection
	//connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

	//printf("\n I got a connection from (%s , %d)",
	//		inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	char * pch;
	fflush(stdout);
	char command[1024];
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SOME VARIABLES FOR SHORTLIST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	char lower[100],upper[100],cpy[1000];
	int cntr=0;
	char buff[1000];
	//char * pch;
	FILE *fpr;
	FILE *fpr2;
	int place=0;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	while (1)
	{
		//waits for server to sendto data
		bytes_recieved=recvfrom(sock,recvfrom_data,1024,0,
				(struct sockaddr *)&client_addr, &addr_len);
		recvfrom_data[bytes_recieved] = '\0';
		if (strcmp(recvfrom_data , "q") == 0 || strcmp(recvfrom_data , "Q") == 0)
		{	printf("have to close\n");
			timeToclose = 1;
			//sendto(connected, sendto_data,strlen(sendto_data), 0); 
			close(connected);
			//kill(childPid, SIGTERM);
			//exit(0);
			break;
		}
		else if(recvfrom_data[0]=='F' && recvfrom_data[1]=='C')
		{
			system("find . -type f -exec sh -c 'printf \"%s %s \n\" \"$(ls -l --time-style=+%Y%m%d%H%M%S $1 )\" \"$(md5sum $1 | cut -d\" \" -f1)\"' '' '{}' '{}' \\; | awk '{print $7, $6, $8}' > checkall");
			
			//file to be sent here checkall
			
			FILE *fp = fopen("checkall","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				fclose(fp);
			
			//when sent file comment next 2 lines
			//strcpy(sendto_data,"ANS here is the filehash checkall...... :P"); 
			//sendto(connected, sendto_data,strlen(sendto_data), 0);
			printf("recvfrom_data after check all : %s \n",recvfrom_data);
			continue;
		}
		else if(recvfrom_data[0]=='F' && recvfrom_data[1]=='V')
		{
			printf("Identified FV\n");
			strncpy(regex,(char*)recvfrom_data+2,100);
			printf("Filename is %s\n",regex);
			
			strcpy(command,"openssl md5 ");
			strcat(command,regex);
			strcat(command," | cut -d\" \" -f2 > md5");
			system(command);
			strcpy(command,"date -r ./");
			strcat(command,regex);
			strcat(command," +%Y%m%d%H%M%S > date");
			system(command);
			strcpy(command,"paste md5 date > verify");
			//strcat(command," > ir");
			system(command);
			strcpy(command,"rm md5 date");
			system(command);
			
			FILE *fp = fopen("verify","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				fclose(fp);
			
			//strcpy(sendto_data,"ANS here is the filehash verify...... :P"); 
			//sendto(connected, sendto_data,strlen(sendto_data), 0);
			printf("recvfrom_data after verify : %s \n",recvfrom_data);
			continue;
		}
		
		else if(recvfrom_data[0]=='I' && recvfrom_data[1]=='L')
		{
			printf("IL RECEIVED\n");
			//system("ls -l > longlist");
			system("find . -printf '%p %TY%Tm%Td%TH%Tm%Tm %k \n' > il");
			//file to be sent here longlist
			
			FILE *fp = fopen("il","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				/*strcpy(sendto_data,"ack");
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				printf("sent an ack\n");
				*/
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(server_addr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(server_addr));
					
				fclose(fp);
			
			//strcpy(sendto_data,"ANS here is the list...... :P"); 
			//int p =sendto(sock, sendto_data, 1024, 0,
			//		(struct sockaddr *)&client_addr, sizeof(server_addr));
			//if(p ==-1) perror("hello");
			//printf("recvfrom_data after longlist : %s \n",recvfrom_data);
			continue;
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  SHORTLIST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TO BE COPIED BEFORE IR
		else if(recvfrom_data[0] == 'I' && recvfrom_data[1]=='S')
		{
			printf("Identified IR\n");
			strncpy(regex,(char*)recvfrom_data+2,100);
			printf("Timestamps are is %s\n",regex);
			pch = strtok (regex," ");
			strcpy(lower,pch);
			//printf("timestamp 1 : %s\n",pch);
			pch = strtok (NULL, " ");
			strcpy(upper,pch);
			//printf("timestamp 2 : %s\n",pch);
			system("ls -l --time-style=+%Y%m%d%H%M%S -t > ls");
			
			fpr = fopen( "ls", "r" );
			fpr2 = fopen( "is", "w" );
			while ( fgets( buff, 1000, fpr ) != NULL )
			{	
				if(cntr!=0 && cntr!=1)
				{
					printf("%d hahaha    %s",cntr,buff);
					strcpy(cpy,buff);
					place=0;
					pch = strtok (buff," ");
					while (pch != NULL)
					{
						if(place==5)
						{
							printf("%s\n", pch);
							if(strcmp(pch,lower)>0 && strcmp(pch,upper)<0)
							{
								printf("printing\n");
								fprintf(fpr2,"%s",cpy);
							}
						}
						place++;
						pch = strtok (NULL," ");
					}
				}
				cntr++;
			}
			fclose( fpr );
			fclose( fpr2 );
			
			FILE *fp = fopen("is","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				fclose(fp);
			
			//strcpy(sendto_data,"ANS here is the list...... :P"); 
			//sendto(connected, sendto_data,strlen(sendto_data), 0);
			printf("recvfrom_data after regex : %s \n",recvfrom_data);
			continue;
			
			
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		else if(recvfrom_data[0]=='I' && recvfrom_data[1]=='R')
		{
			printf("Identified IR\n");
			strncpy(regex,(char*)recvfrom_data+2,100);
			printf("Regex is %s\n",regex);
			
			strcpy(command,"find . -name \"");
			strcat(command,regex);
			strcat(command,"\" > ir");
			system(command);
			
			//file to be sent here longlist
			
			FILE *fp = fopen("ir","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				fclose(fp);
			
			//strcpy(sendto_data,"ANS here is the list...... :P"); 
			//sendto(connected, sendto_data,strlen(sendto_data), 0);
			printf("recvfrom_data after regex : %s \n",recvfrom_data);
			continue;
		}
		else if(strlen(recvfrom_data)>2 && recvfrom_data[0]=='U' && recvfrom_data[1]==' ')
		{
			char arr[100];
			strncpy(arr,(char*)recvfrom_data+2,100);
			printf("Someone wants to Upload File : %s\n Type \"Allow\" to let them; \"Stop\" to prevent them\n",arr);
			// sendto(connected,recvfrom_data,1024,0);
				close(fd[0]);
				write(fd[1],arr,strlen(arr)+1);		
			/*FILE *fp1 = fopen(arr,"wb");
			//char dup[1024];
			memset(recvfrom_data,0,1024);
			while(1){
				bytes_recieved=read(connected,recvfrom_data,1024);
				//recvfrom_data[bytes_recieved] = '\0';
				printf("got %s number %d-----\n",recvfrom_data,bytes_recieved);

				if(strcmp(recvfrom_data,"End Of File")==0)
				{
					break;
				}	
				//else break;
				fwrite(recvfrom_data, 1,bytes_recieved, fp1);
				//bytes_recieved=read(connected,recvfrom_data,1024);
				//sleep(1);
			}
			printf("File closed\n");
			fclose(fp1);*/
		}
		else if(strlen(recvfrom_data)>2 && recvfrom_data[0]=='D' && recvfrom_data[1]==' ')
		{
			char arr[100];
				strcpy(arr,recvfrom_data+2);
				//strcat(arr,pch);
				printf("opening %s\n",arr);
				FILE *fp = fopen(arr,"r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(sendto_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(sendto_data,0,1024);
					byteR = fread(sendto_data,1,1024,fp);
					sendto_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  sendto(sock, sendto_data, byteR, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
					printf("%s",sendto_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(sendto_data,0,1024);
				char end[]= "End Of File";
				strcpy(sendto_data,end);
				sendto(sock, sendto_data, 1024, 0,
					(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				fclose(fp);

		}
		
		
		else{//prints out all of it

			printf("%s\n" , recvfrom_data);
			fflush(stdout);
		}

		/*
		   bytes_recieved = recvfrom(connected,recvfrom_data,1024,0);

		   recvfrom_data[bytes_recieved] = '\0';
		   if(bytes_recieved == 0) continue;

		   if (strcmp(recvfrom_data , "q") == 0 || strcmp(recvfrom_data , "Q") == 0)
		   {
		   close(connected);
		   break;
		   }

		   else 
		   printf("\n RECIEVED DATA = %s " , recvfrom_data);
		   fflush(stdout);*/
	}


	close(sock);
	//waitpid(pid,NULL,0);

}



//client handles tcp requests
void client( int c1){
	int connected, bytes_recieved;  
	char send_data [1024],recv_data[1024];
	char regex[100];
	char fileName[100];
	struct hostent *host;
	struct sockaddr_in server_addr;  
	host = gethostbyname("127.0.0.1");
	//gives me the socket
	if ((connected = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		fprintf(stderr,"fck\n");
		exit(1);
	}


	server_addr.sin_family = AF_INET;     
	server_addr.sin_port = htons(c1);   
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(server_addr.sin_zero),8); 


	//establishes connection bw client and server
		
	while (connect(connected, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1) ;

	char *pch;
	char copy[1024];
	while(1)
	{
		gets(send_data); // DATA which is got in the input buffer
		//printf("wtf %s\n",send_data);
		
shortcut :		
		strcpy(copy,send_data);
		pch = strtok (copy," ");

		//=======================    	IndexGet =================================
		if(pch!=NULL)
		{
			if(strcmp(pch,"FileHash")==0) // FileHash Verify or FileHash CheckAll
				{
					pch = strtok (NULL, " ");
					if(pch !=NULL)
					{
						if(strcmp(pch,"Verify")==0)
						{
							pch = strtok (NULL, " ");
							if(pch!=NULL)
							{
								strcpy(send_data,"FV");
								strcat(send_data,pch);
								//printf("send_data : %s\n",send_data);
								send(connected, send_data,strlen(send_data), 0);
								while(1)
								{
									bytes_recieved=recv(connected,recv_data,1024,0);
									recv_data[bytes_recieved] = '\0';
									if(strcmp(recv_data,"End Of File") == 0)break;
									fwrite(recv_data,1,bytes_recieved,stdout);
									
								}
								//printf("\nout now\n");
								continue;
							}
						
						}
						else if(strcmp(pch,"CheckAll")==0)
						{
							strcpy(send_data,"FC");
							send(connected, send_data,strlen(send_data), 0);
							while(1)
							{
								bytes_recieved=recv(connected,recv_data,1024,0);
								recv_data[bytes_recieved] = '\0';
								if(strcmp(recv_data,"End Of File") == 0)break;
									fwrite(recv_data,1,bytes_recieved,stdout);
									
							}
							//printf("\nout now\n");
							continue;
						}
					}
					else printf("wrong usage of FileHash\n");
				}
			else if(strcmp(pch,"IndexGet")==0)	
			{
				printf ("%s\n",pch);
				pch = strtok (NULL, " ");
				if(pch!=NULL)
				{
				//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Indexget ShortList >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	Add Before Regex
					if(strcmp(pch,"ShortList")==0)
					{
						pch = strtok (NULL, " ");
						if(pch!=NULL)
						{
							strcpy(send_data,"IS");
							strcat(send_data,pch);
							pch = strtok (NULL, " ");
							if(pch!=NULL)
							{
								strcat(send_data," ");
								strcat(send_data,pch);
								//printf("send_data : %s\n",send_data);
								send(connected, send_data,strlen(send_data), 0);
					
								//replace this with fiel catcher 
								while(1)
								{
									bytes_recieved=recv(connected,recv_data,1024,0);
									recv_data[bytes_recieved] = '\0';
									if(strcmp(recv_data,"End Of File") == 0)break;
									fwrite(recv_data,1,bytes_recieved,stdout);
						
								}
								printf("\nout now\n");
								continue;
							}
						}
						else printf("Wrong Usage. Please Type \"IndexGet ShortList <filename>\"	\n");	
					}
				//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TILL HERE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
					
				//=======================    	IndexGet Regex   =================================
				if(strcmp(pch,"Regex")==0)
				{
					pch = strtok (NULL, " ");
					if(pch!=NULL)
					{
					strcpy(send_data,"IR");
					strcat(send_data,pch);
					printf("send_data : %s\n",send_data);
					send(connected, send_data,strlen(send_data), 0);
					
					while(1)
					{
						bytes_recieved=recv(connected,recv_data,1024,0);
						recv_data[bytes_recieved] = '\0';
						if(strcmp(recv_data,"End Of File") == 0)break;
						fwrite(recv_data,1,bytes_recieved,stdout);		
					}
					continue;
					}
					else
					{
						printf("Regular Expression not Given, please try again\n");
					}
				}
				
			//=======================    	IndexGet LongList   =================================	
			
			//if(strcmp(copy,"IndexGet LongList")==0 )
				else if(strcmp(pch,"LongList")==0)
				{
					strcpy(send_data,"IL");
					send(connected, send_data,strlen(send_data), 0); 
				
					while(1)
					{
						//printf("\nstuck 181\n");
						bytes_recieved=recv(connected,recv_data,1024,0);
						recv_data[bytes_recieved] = '\0';
						if(strcmp(recv_data,"End Of File") == 0)break;
						fwrite(recv_data,1,bytes_recieved,stdout);
						//printf("rec - %s\n",recv_data)
					
					}
				//	printf("\nout now\n");
					continue;
					}
				}
				}
			
			else if(strcmp(pch,"Upload") == 0)
			{ 
				// Upload uses the Download functionality of the other user.
				pch = strtok (NULL, " ");
				//	strcpy(send_data,"IR");
				char arr[100];
				strcpy(arr,pch);
				printf("Waiting for permission to Upload %s\n",arr);	
				strcpy(send_data,"U ");
				strcat(send_data,pch);
				write(connected,send_data,1024);

			}
			else if(strcmp(pch,"Download") == 0)
			{
				pch = strtok (NULL, " ");
				if(pch!=NULL)
				{
resend:			strcpy(send_data,"D ");
				strcat(send_data,pch);
				write(connected,send_data,1024);
				
			//printf("printing %s\n",pch);
			// send(connected,recv_data,1024,0);
			
	//pch is the file to be downloaded and written to
			FILE *fp1 = fopen(pch,"w");
			
			memset(recv_data,0,1024);
			while(1){
				bytes_recieved=read(connected,recv_data,1024);

				if(strcmp(recv_data,"End Of File")==0)
				{
					break;
				}	
				fwrite(recv_data, 1,bytes_recieved, fp1);
				
			}
			//printf("File closed\n");
			fclose(fp1);

			//code to ensure integrity of data.....		=====================================	
			bytes_recieved=read(connected,recv_data,1024);
			
			char dt[1024];
			strcpy(dt,recv_data);
			char * hsh = strtok(dt," ");
			
			if(hsh == NULL) 
				hsh = strtok(NULL," ");
		//hsh and pch contain name of file under transfer. Both should be same in working case	
			if(strcmp(hsh,pch) == 0){
				hsh = strtok(NULL," ");
			char fname[100];
	strcpy(fname,pch);
	char packet[1024];//will have the final md5 string
	char cmd[1000],temp[100];
	int stlen,ii;
	
	//system commands==============================================
	strcpy(cmd,"md5sum ");
	strcat(cmd,fname);
	strcat(cmd," | awk '{print $1}'> t1");
	system(cmd);
	FILE *f1= fopen("t1","r");
	fgets( packet, 100, f1 );
	stlen=strlen(packet);
	packet[stlen-1]='\0';
	fclose(f1);
	strcpy(cmd,"rm t1");
	system(cmd);
	// Now packet and hsh have filehashes of the two files =======================
	
	if(strcmp(packet,hsh) == 0 ) printf(" TRANSFER COMPLETE\n");
	else {
		printf("ERROR md5 shows error, will RE_REQUEST FILE\n") ;
		goto resend;
		}		
	}
			else printf("ERROR unknown as file names dont match\n");
	}
			
			else printf("Wrong use of download");
				
			}
			else if(strcmp(pch,"Allow") == 0)
			{	
				
				close(fd[1]);
				int nbytes = read(fd[0],fileName,sizeof(fileName));
				strcpy(send_data,"Download ");
				strcat(send_data,fileName);
				goto shortcut;
			}
			else if(strcmp(pch,"Stop") == 0)
			{
				//close(fd[1]);
				printf("Process stopped\n");
			}
			else{
				//normal text===================================================
				if ((strcmp(send_data , "q") == 0 || strcmp(send_data , "Q") == 0) || timeToclose ==1)
				{
					if(timeToclose)printf("bbye\n");
					send(connected, send_data,strlen(send_data), 0); 
					fflush(stdout);
					close(connected);
					kill(childPid, SIGTERM);
					exit(0);
					break;
				}

				else
					send(connected, send_data,strlen(send_data), 0);  
			}

		}


	}
	return;
}

void server(int s1){
	int sock, connected, true = 1,bytes_recieved;  
	char send_data [1024],recv_data[1024],copy[1024];       
	char regex[100];
	struct sockaddr_in server_addr,client_addr;    
	int sin_size;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;         
	server_addr.sin_port = htons(s1);     
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server_addr.sin_zero),8); 
	//binded socket to required port
	
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
			== -1) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(sock, 5) == -1) {
		perror("Listen");
		exit(1);
	}

	printf("\nTCPServer Waiting for client on port %d\n",s1);
	fflush(stdout);



	sin_size = sizeof(struct sockaddr_in);
	//connected represents the client server connection
	connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

	printf("\n I got a connection from (%s , %d)",
			inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	char * pch;
	fflush(stdout);
	char command[1024];
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< SOME VARIABLES FOR SHORTLIST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	char lower[100],upper[100],cpy[1000];
	int cntr=0;
	char buff[1000];
	//char * pch;
	FILE *fpr;
	FILE *fpr2;
	int place=0;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	while (1)
	{
		//waits for client to send data
		bytes_recieved=recv(connected,recv_data,1024,0);
		recv_data[bytes_recieved] = '\0';
		
		if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
		{	printf("have to close\n");
			timeToclose = 1; 
			close(connected);
			
			//exit(0);
			break;
		}
		else if(recv_data[0]=='F' && recv_data[1]=='C')
		{//its FileHash CheckAll
			system("find . -type f -exec sh -c 'printf \"%s %s \n\" \"$(ls -l --time-style=+%Y%m%d%H%M%S $1 )\" \"$(md5sum $1 | cut -d\" \" -f1)\"' '' '{}' '{}' \\; | awk '{print $7, $6, $8}' > checkall");
			
			//file to be sent here checkall
			
			FILE *fp = fopen("checkall","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(send_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(send_data,0,1024);
					byteR = fread(send_data,1,1024,fp);
					send_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break
					
					sentN =  write(connected,send_data,1024);
					//printf("%s",send_data);
					//printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				//printf("End file\n");
				memset(send_data,0,1024);
				char end[]= "End Of File";
				strcpy(send_data,end);
				write(connected,send_data,1024);
				fclose(fp);
			
			//when sent file comment next 2 lines
			//strcpy(send_data,"ANS here is the filehash checkall...... :P"); 
			//send(connected, send_data,strlen(send_data), 0);
			//printf("recv_data after check all : %s \n",recv_data);
			continue;
		}
		else if(recv_data[0]=='F' && recv_data[1]=='V')
		{
		//	printf("Identified FV\n");
			strncpy(regex,(char*)recv_data+2,100);
			printf("Verifying %s\n",regex);
			
			strcpy(command,"openssl md5 ");
			strcat(command,regex);
			strcat(command," | cut -d\" \" -f2 > md5");
			system(command);
			strcpy(command,"date -r ./");
			strcat(command,regex);
			strcat(command," +%Y%m%d%H%M%S > date");
			system(command);
			strcpy(command,"paste md5 date > verify");
			//strcat(command," > ir");
			system(command);
			strcpy(command,"rm md5 date");
			system(command);
			
			FILE *fp = fopen("verify","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(send_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(send_data,0,1024);
					byteR = fread(send_data,1,1024,fp);
					send_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  write(connected,send_data,1024);
					//printf("%s",send_data);
					//printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
			//	printf("End file\n");
				memset(send_data,0,1024);
				char end[]= "End Of File";
				strcpy(send_data,end);
				write(connected,send_data,1024);
				fclose(fp);
			
			//strcpy(send_data,"ANS here is the filehash verify...... :P"); 
			//send(connected, send_data,strlen(send_data), 0);
			//printf("recv_data after verify : %s \n",recv_data);
			continue;
		}
		
		else if(recv_data[0]=='I' && recv_data[1]=='L')
		{
			//system("ls -l > longlist");
			system("find . -printf '%p %TY%Tm%Td%TH%Tm%Tm %k \n' > il");
			//file to be sent here longlist
			
			FILE *fp = fopen("il","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(send_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(send_data,0,1024);
					byteR = fread(send_data,1,1024,fp);
					send_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  write(connected,send_data,1024);
					printf("%s",send_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(send_data,0,1024);
				char end[]= "End Of File";
				strcpy(send_data,end);
				write(connected,send_data,1024);
				fclose(fp);
			
			//strcpy(send_data,"ANS here is the list...... :P"); 
			//send(connected, send_data,strlen(send_data), 0);
			
			printf("recv_data after longlist : %s \n",recv_data);
			continue;
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  SHORTLIST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TO BE COPIED BEFORE IR
		else if(recv_data[0] == 'I' && recv_data[1]=='S')
		{
			printf("Identified ID\n");
			strncpy(regex,(char*)recv_data+2,100);
			printf("Timestamps are is %s\n",regex);
			pch = strtok (regex," ");
			strcpy(lower,pch);
			//printf("timestamp 1 : %s\n",pch);
			pch = strtok (NULL, " ");
			strcpy(upper,pch);
			//printf("timestamp 2 : %s\n",pch);
			system("ls -l --time-style=+%Y%m%d%H%M%S -t > ls");
			
			fpr = fopen( "ls", "r" );
			fpr2 = fopen( "is", "w" );
			while ( fgets( buff, 1000, fpr ) != NULL )
			{	
				if(cntr!=0 && cntr!=1)
				{
					printf("%d hahaha    %s",cntr,buff);
					strcpy(cpy,buff);
					place=0;
					pch = strtok (buff," ");
					while (pch != NULL)
					{
						if(place==5)
						{
							printf("%s\n", pch);
							if(strcmp(pch,lower)>0 && strcmp(pch,upper)<0)
							{
								printf("printing\n");
								fprintf(fpr2,"%s",cpy);
							}
						}
						place++;
						pch = strtok (NULL," ");
					}
				}
				cntr++;
			}
			fclose( fpr );
			fclose( fpr2 );
			
			FILE *fp = fopen("is","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				memset(send_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(send_data,0,1024);
					byteR = fread(send_data,1,1024,fp);
					send_data[byteR] = '\0';
					//   byteR = strlen(data);
					// if(byteR == 0) break

				//	fflush(stdout);
					//void *temp = data;
					sentN =  write(connected,send_data,1024);
					printf("%s",send_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
		//		printf("End file\n");
				memset(send_data,0,1024);
				char end[]= "End Of File";
				strcpy(send_data,end);
				write(connected,send_data,1024);
				fclose(fp);
			
	//		printf("recv_data after regex : %s \n",recv_data);
			continue;
			
			
		}
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		//Regex uses find to get output of files and then 
		else if(recv_data[0]=='I' && recv_data[1]=='R')
		{
			//printf("Identified IR\n");
			strncpy(regex,(char*)recv_data+2,100);
			//printf("Regex is %s\n",regex);
			
			strcpy(command,"find . -name \"");
			strcat(command,regex);
			strcat(command,"\" > ir");
			system(command);
			
			//file to be sent here longlist
			
			FILE *fp = fopen("ir","r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				memset(send_data,0,1024);
				int byteR,sentN;
				while(!feof(fp))
				{	//memset(send_data,0,1024);
					byteR = fread(send_data,1,1024,fp);
					send_data[byteR] = '\0';
					sentN =  write(connected,send_data,1024);
					printf("%s",send_data);
					printf("read %d sent %d--------\n",sentN,byteR);
					//===============================file sent=================================================
				}
				printf("End file\n");
				memset(send_data,0,1024);
				char end[]= "End Of File";
				strcpy(send_data,end);
				write(connected,send_data,1024);
				fclose(fp);
				continue;
		}
		else if(strlen(recv_data)>2 && recv_data[0]=='U' && recv_data[1]==' ')
		{
			char arr[100];
			strncpy(arr,(char*)recv_data+2,100);
			printf("Someone wants to Upload File : %s\n Type \"Allow\" to let them; \"Stop\" to prevent them\n",arr);
			// send(connected,recv_data,1024,0);
				close(fd[0]);
				write(fd[1],arr,strlen(arr)+1);		
		
		}
		else if(strlen(recv_data)>2 && recv_data[0]=='D' && recv_data[1]==' ')
		{
			char arr[100];
				strcpy(arr,recv_data+2);
				//strcat(arr,pch);
				printf("Sending %s\n",arr);
				FILE *fp = fopen(arr,"r");
				if(fp == NULL)
				{
					printf("wrong file\n");
					continue;
				}
				
				//=================told the client that file is to be sent========================
				//fgets ( data, sizeof(data), fp ) != NULL
				// char data[1024];
				memset(send_data,0,1024);
				int byteR,sentN;
				
				while(!feof(fp))
				{	//memset(send_data,0,1024);
					byteR = fread(send_data,1,1024,fp);
					sentN =  write(connected,send_data,byteR);
			
					//===============================file sent=================================================
				}
		//		printf("End file\n");
				memset(send_data,0,1024);
				
				char end[]= "End Of File";
				strcpy(send_data,end);
				write(connected,send_data,1024);
				fclose(fp);
					//File sent fully
					
					//sending hash of this file for confirmation at other end
				char fname[100];
	//gets(fname);
	strcpy(fname,arr);
	char packet[1024];
	char cmd[1000],temp[100];
	int stlen,ii;
	strcpy(cmd,"md5sum ");
	strcat(cmd,fname);
	strcat(cmd," | awk '{print $2, $1}'> t1");
	system(cmd);
	strcpy(cmd,"stat -c%s ");
	strcat(cmd,fname);
	strcat(cmd," > t2");
	system(cmd);
	strcpy(cmd,"paste t1 t2 | awk '{print $1, $2, $3}' > md5");
	system(cmd);
	strcpy(cmd,"rm t1 t2");
	system(cmd);

	FILE *f1= fopen("md5","r");
	fgets( packet, 100, f1 );
	stlen=strlen(packet);
	packet[stlen-1]='\0';
	
	printf("length of packet now is %d\n",strlen(packet));
	printf("packet header : %s\n",packet);
	fclose(f1);
	strcpy(cmd,"rm md5");
	system(cmd);

				memset(send_data,0,1024);
				//char end[]= "End Of File";
				strcpy(send_data,packet);
				write(connected,send_data,1024);
		}
		
		
		else{//prints out all of it

			printf("%s\n" , recv_data);
			fflush(stdout);
		}

		
	}


	close(sock);
	//waitpid(pid,NULL,0);

}

int main()

{
	int pid;
	int s1,choice=0;
	printf("enter s port\n");
	scanf("%d",&s1);
	printf("enter 0 for tcp mode and 1 for udp mode\n");
	scanf("%d",&choice);
	timeToclose = 0;
	pipe(fd);
	childPid = getpid();
	
	pid = fork();
	
	if(!pid)
	{

		//-------------------client----------------------------------------------		
		//fprintf(stderr,"kiddo\n");

		int c1;

		scanf("%d",&c1);
		if(choice==0)
			client(c1);
		else
			uclient(c1);
	}
	else {
		//listening socket aka server
		
		if(choice==0)
			server(s1);
		else
			userver(s1);
	}
	return 0;
}
