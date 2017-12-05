#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10 
#define PORT 1337 

int main(int argc, char* argv[])
{ 
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  printf("Client is alive and establishing socket connection.\n");
  
    sock = socket(AF_INET, SOCK_STREAM, 0); /* creates socket -Internet domain, TCP */
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
    
  if (argc != 2) {  /* error running hostname */
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


  memset((char *)&cli_name,0, sizeof(cli_name)); 
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(hostaddr);  //changed here IP_ADDRESS to the host address IP
  cli_name.sin_port = htons(PORT);

   /* connect a socket, 0-successful, (-1) for error*/
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }


  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

} 