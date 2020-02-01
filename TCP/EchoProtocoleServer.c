#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <string.h>



#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

#include <unistd.h>//close()

#define BUFFER_SIZE 256

void capitalizeBuffer(char *buffer) {
  do {
      *buffer = toupper((unsigned char) *buffer);
  } while (*buffer++);
}

int main()
{
  int max_pending_connections = 1;
  struct sockaddr_in client;
  struct hostent *client_host_info;
  char *client_host_ip;
  socklen_t client_addr_len; 
	
	char serverMessage[BUFFER_SIZE] = "You have reached the server";
	
	//create the server socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	int client_socket_fd =0;
	int num_bytes = 0;
	
	//define the server address
	struct sockaddr_in serverAdress;
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_port = htons(9002);
	serverAdress.sin_addr.s_addr = INADDR_ANY;
	
	//bind the socket to our specified IP and port
	bind(serverSocket, (struct sockaddr*) &serverAdress, sizeof(serverAdress));

	
	
	 // Listen on the socket for up to some maximum pending connections
  if (0 > listen(serverSocket, max_pending_connections)) {
    fprintf(stderr, "server failed to listen\n");
    exit(1);
  } else {
    fprintf(stdout, "server listening for a connection on port %d\n", serverAdress.sin_port);
  }
  
	  // Get the size client's address structure
  client_addr_len = sizeof(client);

  // Accept a new client
  if (0 > (client_socket_fd = accept(serverSocket, (struct sockaddr *)&client, &client_addr_len))) 
  {
    fprintf(stderr, "server accept failed\n");
  } else {
    fprintf(stdout, "server accepted a client!\n");    
  }
	

// Determine who sent the echo so that we can respond
  client_host_info = gethostbyaddr((const char *)&client.sin_addr.s_addr, sizeof(client.sin_addr.s_addr), AF_INET);
  if (client_host_info == NULL) {
    fprintf(stderr, "server could not determine client host address\n");
  } 
  client_host_ip = inet_ntoa(client.sin_addr);
  if (client_host_ip == NULL) {
    fprintf(stderr, "server could not determine client host ip\n");
  }
  fprintf(stdout, "server established connection with %s (%s)\n", client_host_info->h_name, client_host_ip);
    
  // Read echo from the client
  bzero(serverMessage, BUFFER_SIZE);
  num_bytes = read(client_socket_fd, serverMessage, BUFFER_SIZE);
  if (num_bytes == 0) {
    fprintf(stderr, "server could not read from socket\n");
  } else {
    fprintf(stdout, "server received %d bytes: %s\n", num_bytes, serverMessage);
  }
   
  // Optional: Modifying client message before echo'ing (correctness test)
  capitalizeBuffer(serverMessage);

  // Echo back to the client
  if (0 > write(client_socket_fd, serverMessage, strlen(serverMessage))) {
    fprintf(stderr, "server could not write back to socket\n");
  } else {
    fprintf(stdout, "server sending message back to client\n");
  }
	
	
	//close the socket
	close(serverSocket);

	return 0;	
}
