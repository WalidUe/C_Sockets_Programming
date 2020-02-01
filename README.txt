*TCP Client:
program that creates, initializes, and connects a client socket to a server socket with a way to specify the connecting server address and port.
*TCP Server:
program that creates and initializes a server socket. Once initialized, the server should accept a client connection, close the connection, and then exit. It also has a way to specify the server's listening port.

*Echo Protocol Client & Server:
Based On Previous example, it's a program that implements the fictitious "echo protocol".The server should accept any string from the client, and then return that string with all letters capitalized (if letters exist).
As soon as the server responds to a client, it may close. And, as soon as the clients receives a response, it may close.
Echo Protocol Example:
Client sends "Hello EveryOne"
Server echoes "HELLO EVERYONE".

*HTTP Client &HTTP Server:
building upon the TCP example, we will look
how to implement the http protocol.
