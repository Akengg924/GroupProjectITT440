//Server Code

#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_SIZE 1000

int main(int argc, char *argv[])
{
char *ip="192.168.8.105";
const int port=21;
int socket_listen;
int sockfd;

struct sockaddr_in serv_address;
struct sockaddr_in receive_address;

int j;
int address_size;
int bytes_received;

int receive_message_size;
char buffer[BUFFER_SIZE];

/* Create a socket for listening for incoming connections. */
socket_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
printf("socket_listen = %d\n", socket_listen);
if (socket_listen < 0)
{
printf("Create socket() failed\n");
exit(EXIT_SUCCESS);
}
printf("Server socket created\n");

/* Make address structure for my local address. */
memset(&serv_address, 0, sizeof(serv_address));
serv_address.sin_family = AF_INET;
serv_address.sin_addr.s_addr=inet_addr(ip);
serv_address.sin_port =port;

/* Bind socket to the local address. */
j = bind(socket_listen, (struct sockaddr *)&serv_address, sizeof(serv_address));
if (j < 0)
{
printf("bind failed\n");
exit(EXIT_SUCCESS);
}
printf("Server socket bound\n");

/* Listen for incoming connections. */
j = listen(socket_listen, 5);
if (j < 0)
{
printf("listen failed\n");
exit(EXIT_SUCCESS);
}
printf("Server waiting for client connection\n");

/* Accept the incoming connection. */
address_size = sizeof(receive_address);
sockfd = accept(socket_listen, (struct sockaddr *) &receive_address, &address_size);

printf("sockfd = %d\n", sockfd);

printf("Server received a connection\n");

int player2;

while (1)
{
bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
buffer[bytes_received] = '\0';
printf("\nPlayer 1 used: %s\n", buffer);

if (strcmp(buffer, "scissors")==0)
{

srand(time(NULL));
player2 = (rand() % 3);

if (player2 == 0)
{
printf("Player 2 used: scissors\n its a draw!\n\n");
}
else if (player2 == 1)
{
printf("Player 2 used: rock\n Player 2 wins!\n\n");
}
else if (player2 == 2)
{
printf("Player 2 used: paper\n Player 1 wins!\n\n");
}

}


else if (strcmp(buffer, "rock")==0)
{

srand(time(NULL));
player2 = (rand() % 3);

if (player2 == 0)
{
printf("Player 2 used: scissors\n Player 1 wins!\n\n");
}
else if (player2 == 1)
{
printf("Player 2 used: rock\n its a draw!\n\n");
}
else if (player2 == 2)
{
printf("Player 2 used: paper\n Player 2 wins!\n\n");
}

}

else if (strcmp(buffer, "paper")==0)
{

srand(time(NULL));
player2 = (rand() % 3);

if (player2 == 0)
{
printf("Player 2 used: scissors\n Player 2 wins!\n\n");
}
else if (player2 == 1)
{
printf("Player 2 used: rock\n Player 1 wins!\n\n");
}
else if (player2 == 2)
{
printf("Player 2 used: paper\n its a draw!\n\n");
}

}

else if (strcmp(buffer, "quit")==0)
{
break;
}
else
{
printf("Wrong input, try again\n\n");
}

}

close(sockfd);
close(socket_listen);

return 0;
}
