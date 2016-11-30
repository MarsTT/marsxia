#include <stdio.h>
#include <sys/socket.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH_OF_LISTEN_QUEUE 10 //length of listen queue in server
#define WELCOME_MESSAGE "welcome to connect the server."
#define SERVER_PORT 2000 // define the defualt connect port id
#define CLIENT_PORT ((2001+rand())%65536) // define the defualt client port as 
#define BUFFER_SIZE 255
#define REUQEST_MESSAGE "welcome to connect the server.\n"
