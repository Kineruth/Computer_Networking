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

#define PORT_ROUTER 3001
#define PORT_CLIENT 3000
#define PORT_SERVER 3002
#define MAX_INPUT_LENGTH 1024


int main(int argc, char *argv[])
{
   
    int socket_fd , cc, recv ,fsize; 
    struct sockaddr_in  s_in, from, dest_C, dest_S;
    char userInput[MAX_INPUT_LENGTH];
    double x, random_num ;
    
    
      socket_fd = socket (AF_INET, SOCK_DGRAM, 0); /* creates socket descriptor type ipv4 and DGRAM (UDP) */
      // bzero(userInput,MAX_INPUT_LENGTH);
      sscanf(argv[1], "%lf", &x);
    
      memset((char *) &s_in,0, sizeof(s_in)); /* zero the struct */
      memset((char *) &from,0, sizeof(from));
      
       s_in.sin_family = (short)AF_INET; /* Address family, AF_INET unsigned  */
       s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /*Internet address long - binds the socket to all available interfaces */
       s_in.sin_port = PORT_ROUTER; /* set port */
        
       dest_C.sin_family = (short)AF_INET; 
       dest_C.sin_addr.s_addr = htonl(INADDR_ANY);   
       dest_C.sin_port = PORT_CLIENT; /* set port */
       
       dest_S.sin_family = (short)AF_INET; 
       dest_S.sin_addr.s_addr = htonl(INADDR_ANY);   
       dest_S.sin_port = PORT_SERVER; /* set port */
     
       cc = bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); /* assigning a name - the address to a socket */
        

      while(1)
      {
         
         fsize = sizeof(from);
         bzero(userInput,MAX_INPUT_LENGTH); /* cleans input */
         recv = recvfrom(socket_fd, &userInput, MAX_INPUT_LENGTH,0,(struct sockaddr *)&from,&fsize); /* get message from router */
         printsin( &from, "recv_udp: ", "Packet from:");
         printf("%s\n", userInput);
         fflush(stdout); /* prints all the input */
         
         if(from.sin_port==PORT_CLIENT){
   
             random_num=randDouble(); /* gets random number */
             
             if(random_num>x )
             {
                  sendto(socket_fd,&userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_S,sizeof(dest_S));
             }
             else 
             { /* delete client's message */
                 strcpy(userInput,"Message lost\n");
                 sendto(socket_fd,&userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_C,sizeof(dest_C));
             }

         }
         else
         {
              sendto(socket_fd,&userInput,MAX_INPUT_LENGTH,0,(struct sockaddr *)&dest_C,sizeof(dest_C)); 
         }
     
      }
    
    
    
    return 0;
}