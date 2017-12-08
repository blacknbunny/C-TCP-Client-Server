#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

struct configuration {
  int myport;
  int backlog;
};


int main(int argc, char **argv){
  if(argc != 2){
    puts("Usage : ./tcpserver port");
    exit(1);
  }
  int sockfd, received_bytes, sended_bytes;
  char buffer[1024], buffer_to_send[1024];

  struct configuration conf={atoi(argv[1]), 20};
  struct configuration *confptr;
  confptr = &conf;

  struct sockaddr_in local_addr;
  struct sockaddr_in remote_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd == -1){
    perror("Socket error ");
    return 1;
  }

  char tr = '1';

  if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
    perror("Setsockopt ");
    exit(1);
  }

  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(confptr->myport);
  local_addr.sin_addr.s_addr = INADDR_ANY;
  memset(local_addr.sin_zero, '\0', sizeof(local_addr.sin_zero));

  int local_bind = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr));
  if(local_bind == -1){
    perror("Bind error ");
    return 1;
  }

  int local_listen = listen(sockfd, confptr->backlog);
  if(local_listen == -1){
    perror("Listen error ");
    return 1;
  }

  while(1){
    int sin_size = sizeof(struct sockaddr_in);
    int remote_accept = accept(sockfd, (struct sockaddr *)&remote_addr, &sin_size);
    if(remote_accept == -1){
      perror("Accept error ");
      return 1;
    }

    if((received_bytes = recv(remote_accept, buffer, sizeof(buffer)-1, 0)) == -1){
      perror("Recv ");
      exit(1);
    }

    buffer[received_bytes] = '\0';

    printf("Received : %s\n", buffer);

    printf("Message : ");
    fgets(buffer_to_send, sizeof(buffer), stdin);


    if((sended_bytes = send(remote_accept, buffer_to_send, strlen(buffer_to_send), 0)) == -1){
      perror("Send error ");
      return 1;
    }

    buffer_to_send[sended_bytes] = '\0';

    close(remote_accept);
  }

  return 0;

}
