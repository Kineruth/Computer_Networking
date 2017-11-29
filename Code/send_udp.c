#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int socket_fd , fsize;
  struct sockaddr_in  dest, from;  /* destination - server address */
  struct hostent *hostptr;
 // struct { char head; u_long body; char tail; } msgbuf; /* sets how the socket would look */
  char name[50]  = "Kineret";
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); /* creates socket descriptor type ipv4 and DGRAM (UDP) */
  memset((char *) &dest,0, sizeof(dest)); /* zero the struct */
  hostptr = gethostbyname(argv[1]);  /* resolve the dest hostname recieved as an argument */
  dest.sin_family = (short) AF_INET; /* set address family */
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length); /* copy the dest address to our hostent struct */
  dest.sin_port = htons((u_short)0x3333); /* short, network byte order port value */

  // msgbuf.head = '<'; 
  // msgbuf.body = htonl(getpid()); /* server message body - long network byte order */
  // msgbuf.tail = '>';
  
  sendto(socket_fd,&name,50,0,(struct sockaddr *)&dest,sizeof(dest)); /* send message through socket to server */
  bzero(name,50);
  fsize=sizeof(socket_fd);
  recvfrom(socket_fd, name, 50,0,(struct sockaddr *)&socket_fd,&fsize); /* getsocket info from server */
  printf("Got data :: %s\n",name); /* print message recieved */
  fflush(stdout); /* clean buffer */
  return 0;
}