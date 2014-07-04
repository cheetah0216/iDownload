#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "FileServer.h"

FileServer::~FileServer()
{

}

int FileServer::Start()
{
  struct sockaddr_in servaddr, cliaddr;
  socklen_t len;
  int listenfd, connfd; 
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr, 0, sizeof(struct sockaddr_in));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);
  
  if( -1 == bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) )
  {
    close(listenfd);
    return -1;
  }
 
  if( -1 == listen(listenfd, 500) )
  {
    close(listenfd);
    return -1;
  }

  for( ; ; )
  {
    len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
    std::cout << "Accept!" << std::endl;
  }
}
