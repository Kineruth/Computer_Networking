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
#define PORT_CLIENT 3000
#define PORT_ROUTER 3001


int main(int argc, char *argv[])
{
  int socket_fd ,fsize;
  struct sockaddr_in  s_in, dest_R;  /* destination - server address */
  // struct hostent *hostptr;
  char userInput[MAX_INPUT_LENGTH];
  
   socket_fd = socket (AF_INET, SOCK_DGRAM, 0); /* creates socket -Internet domain, UDP */
 
   memset((char *) &s_in,0, sizeof(s_in));  /* zero the struct */
   s_in.sin_family = (short)AF_INET; /* Address family, AF_INET unsigned  */
   s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /*Internet address long - binds the socket to all available interfaces */
   s_in.sin_port = PORT_CLIENT; /* set port */
  
   dest_R.sin_family = (short)AF_INET;
   dest_R.sin_addr.s_addr = htonl(INADDR_ANY);
   dest_R.sin_port = PORT_ROUTER; /* set port */
  
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); /* assigning a name - the address to a socket */
  
  
  
 while(1){
   // fflush(stdout); /* clean buffer */
   bzero(userInput,MAX_INPUT_LENGTH); /* cleans input */
   fgets(userInput,MAX_INPUT_LENGTH,stdin); /* gets input */
   
   if(strcmp(userInput,"exit\n")==0)
   { /* user request to exit */
     strcpy(userInput,"Client signed off\n");
     sendto(socket_fd,&userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_R,sizeof(dest_R)); /* send request to router */
     fflush(stdout);
     close(socket_fd);
     break;
   }
       
       sendto(socket_fd,&userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_R,sizeof(dest_R));
       fsize=sizeof(dest_R);
       bzero(userInput,MAX_INPUT_LENGTH); /* cleans input */
       recvfrom(socket_fd, &userInput, MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_R,&fsize); /* get message from router */
       printf("%s\n",userInput); /* print message recieved */
       fflush(stdout); /* clean buffer */
   
 }

  return 0;
}