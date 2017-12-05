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
#include <string.h>

#define MAX_INPUT_LENGTH 1024
#define PORT_ROUTER 3001
#define PORT_SERVER 3002



int main(int argc, char *argv[])
{
  int socket_fd, fsize;
  struct sockaddr_in  s_in, dest_R;
  char userInput[MAX_INPUT_LENGTH];
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); /* creates socket descriptor type ipv4 and DGRAM (UDP) */

   memset((char *) &s_in,0, sizeof(s_in));  /* zero the struct */
   memset((char *) &dest_R,0, sizeof(dest_R));
   
   dest_R.sin_addr.s_addr = htonl(INADDR_ANY); /* Address family, AF_INET unsigned  */
   dest_R.sin_family =(short)AF_INET;   /*Internet address long - binds the socket to all available interfaces */
   dest_R.sin_port = PORT_ROUTER;  /* set port */
    
  s_in.sin_family = (short)AF_INET; 
  s_in.sin_addr.s_addr = htonl(INADDR_ANY); 
  s_in.sin_port = PORT_SERVER;  /* set port */
  
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); /* assigning a name - the address to a socket */

   printsin( &s_in, "RECV_UDP:", "Local socket is:"); 
   fflush(stdout);
  
  while(1)
  { 
    
     fsize = sizeof(dest_R);
     bzero(userInput,MAX_INPUT_LENGTH); /* cleans input */
     recvfrom(socket_fd,&userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_R,&fsize); /* message recieved from client */
     printf("%s\n", userInput); /* print message recieved */
     fflush(stdout);
     bzero(userInput,MAX_INPUT_LENGTH); 
    
    fgets(userInput,MAX_INPUT_LENGTH,stdin); /* gets input */
    
    if(strcmp(userInput,"exit\n")==0){
    strcpy(userInput,"Server signed off");
    sendto(socket_fd, &userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_R, sizeof(dest_R));
    fflush(stdout);
    close(socket_fd);
    break;
    }
     sendto(socket_fd, &userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_R, sizeof(dest_R));

  }
  return 0;
}

