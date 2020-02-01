#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h> 
#include<sys/socket.h>

#include<netinet/in.h> 

#include <unistd.h>//close()
/*
*Basic TCP Client to print data
*received from a remote connection.
*/

int main()
{
	//create a socket
	int networkSocket;
	networkSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	//specify an address for the socket
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9002);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	int connectionStatus = connect(networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	//check for error with the connection
	if(connectionStatus == -1)
	{
		printf("ERROR: Connection Failed!\n");
	}

	//receive data from the server
	char serverResponse[256];
	recv(networkSocket, &serverResponse, sizeof(serverResponse),0);

	//printing the server's response
	printf("The server sent the data: %s\n", serverResponse);

	//closing the socket
	close(networkSocket);

	return 0;
}
