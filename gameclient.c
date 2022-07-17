//client source code

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#define BUFFER_SIZE 1000

int main(int argc, char *argv[])
{

char *ip="192.168.8.105";
const int port=21;
int sockfd,j;
struct sockaddr_in serv_send;
char text[80];
char buffer[BUFFER_SIZE];
int send_length;
int bytes_sent;

/* Create the socket. */
sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
printf("sockfd = %d\n", sockfd);
if (sockfd < 0)
{
printf("Create socket() failed\n");
exit(EXIT_SUCCESS);
}
printf("Client socket created\n");

/* Create address structure */
memset(&serv_send, 0, sizeof(serv_send));
serv_send.sin_family = AF_INET;
serv_send.sin_addr.s_addr = inet_addr(ip);
serv_send.sin_port=port;

/* Connect to the server. */
j = connect(sockfd, (struct sockaddr *)&serv_send, sizeof(serv_send));
if (j < 0)
{
printf("connect failed\n");
exit(EXIT_SUCCESS);
}
printf("Client Has connected to server\n");

while (1)
{
printf("\nrock, paper, or scissors? ");
scanf("%s", text);
if (strcmp(text, "quit") == 0)
{
break;
}

strcpy(buffer, text);
send_length = strlen(text);
bytes_sent = send(sockfd, buffer, send_length, 0);
}

close(sockfd);

return 0;
}
