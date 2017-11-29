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


void printsin(struct sockaddr_in *sin, char *pname, char* msg)
{
  printf("%s \n%s ip= %s port= %d \n", pname, msg, inet_ntoa(sin->sin_addr), sin->sin_port);
}

int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  //struct { char head; u_long  body; char tail;} msg; /* sets how the socket would look */
  char nameServer[50] = "Friend";
  char name[50]; /* client name */
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); /* creates socket descriptor type ipv4 and DGRAM (UDP) */

  memset((char *) &s_in,0, sizeof(s_in));  /* zero the struct */

  s_in.sin_family = (short)AF_INET; /* Address family, AF_INET unsigned  */
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /*Internet address long - binds the socket to all available interfaces */
  s_in.sin_port = htons((u_short)0x3333); /* short, network byte order port value */

  printsin( &s_in, "RECV_UDP:", "Local socket is:"); 
  fflush(stdout);
  
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); /* assigning a name - the address to a socket */

  while(1) { 
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&name,50,0,(struct sockaddr *)&from,&fsize); /* message recieved from client */
    printsin( &from, "recv_udp: ", "Packet from:");
     fflush(stdout);
    printf("Got data :: %s\n",name); /* print message recieved */
    // printf("Got data ::%c%ld%c\n",msg.head,(long) ntohl(msg.body),msg.tail);  /* the server message */
    fflush(stdout); /* clean buffer */
     sendto(socket_fd, nameServer,50,0,(struct sockaddr *)&from, sizeof(from));
  }
  
  return 0;
}

