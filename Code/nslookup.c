
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  struct addrinfo* res; 
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  if (argc != 2) { /* error running hostname */
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1]; /* get hostname from input */
  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) { /* nonzero for error returning information on a particular host name */
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr; 
  hostaddr = inet_ntoa(saddr->sin_addr); //get hostname IP

  printf("Address for %s is %s\n", hostname, hostaddr);
  exit(0);
}