#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

#include <unistd.h>//close()
int main()
{
	
	char serverMessage[256] = "You have reached the server";
	
	//create the server socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	//define the server address
	struct sockaddr_in serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(9002);
	serverAdress.sin_addr.s_addr = INADDR_ANY;
	
	//bind the socket to our specified IP and port
	bind(serverSocket, (struct sockaddr*) &serverAdress, sizeof(serverAdress));

	listen(serverSocket, 5);

	int clientSocket = accept(serverSocket, NULL, NULL);
	
	//send the message
	send(clientSocket, serverMessage, sizeof(serverMessage),0);
	
	//close the socket
	close(serverSocket);

	return 0;	
}
