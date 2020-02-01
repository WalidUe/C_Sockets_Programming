#include <netdb.h>
#include <string.h>



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
//CONSTANTS
#define MESSAGE "Knowledge without action is Wastefulness and action without knowledge is Foolishness"
#define BUFFER_SIZE 255

int main()
{
	//create a socket
	int networkSocket;
	networkSocket = socket(AF_INET, SOCK_STREAM, 0);
	char buffer[BUFFER_SIZE];
	//specify an address for the socket
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9003);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	//connect to the server
	int connectionStatus = connect(networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	//check for error with the connection
	if(connectionStatus == -1)
	{
		fprintf(stderr,"ERROR: Connection Failed!\n");
	}
	
	
	 // Send echo message
  if (0 > send(networkSocket, MESSAGE, strlen(MESSAGE), 0)) {
    fprintf(stderr, "client failed to send echo message");
    close(networkSocket);
    exit(1);
  }

	 // Process response from server
  bzero(buffer, BUFFER_SIZE);
  if(0 > read(networkSocket, buffer, BUFFER_SIZE)) {
    fprintf(stderr, "client could not read response from server\n");
    close(networkSocket);
    exit(1);
  } else {
    fprintf(stdout, "echo from server: %s\n", buffer);
  }


	//closing the socket
	close(networkSocket);

	return 0;
}
