#include "funcs.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
  printf("%s \n%s ip= %s port= %d \n", pname, msg, inet_ntoa(sin->sin_addr), sin->sin_port);
}


double randDouble()
{
   return (double)rand() / (double)RAND_MAX ;
}