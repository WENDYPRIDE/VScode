#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
/**
循环服务器客户端程序
**/
#define PORT 8888
#define BUFFERSIZE 1024
int main(int argc, char *argv[])
{
  int s;
  int ret;
  int size;
  struct sockaddr_in server_addr;
  char buffer[BUFFERSIZE];
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
  {
    perror("socket error");
    return -1;
  }
  bzero(&server_addr, sizeof(server_addr));
  //将地址结构绑定到套接字
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  //连接服务器
  ret = connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == -1)
  {
    perror("connect error");
    return -1;
  }
  memset(buffer, 0, BUFFERSIZE);
  strcpy(buffer, "TIME");
  size = send(s, buffer, strlen(buffer), 0);
  if (size < 0)
  {
    perror("send error");
    return -1;
  }
  memset(buffer, 0, BUFFERSIZE);
  size = recv(s, buffer, BUFFERSIZE, 0);
  if (size < 0)
  {
    perror("recv error");
    return;
  }

  printf("%s", buffer);
  close(s);
  return 0;
}