#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
/**
TCP并发服务器，预先建立进程，同时到来的客户端分别由不同的进程并发处理
**/
#define PORT 8888
#define BUFFERSIZE 1024
#define PIDNUM 2
static void handle(int s)
{
  int sc;
  struct sockaddr_in client_addr; //客户端地址
  char buffer[BUFFERSIZE];
  int len;
  int ret;
  int size;
  len = sizeof(client_addr);
  time_t now;
  //接收客户端的连接
  while (1)
  {
    memset(buffer, 0, BUFFERSIZE);
    sc = accept(s, (struct sockaddr *)&client_addr, &len);
    size = recv(sc, buffer, BUFFERSIZE, 0);
    if (size > 0 && !strncmp(buffer, "TIME", 4))
    {
      memset(buffer, 0, BUFFERSIZE);
      now = time(NULL);
      sprintf(buffer, "%24s\r\n", ctime(&now));
      send(sc, buffer, strlen(buffer), 0); //发送到客户端
    }
    close(sc);
  }
}

int main(int argc, char *argv[])
{
  int s;
  int ret;
  struct sockaddr_in server_addr;
  pid_t pid[PIDNUM];
  int i;
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
  {
    perror("socket error");
    return -1;
  }
  //绑定地址到套接字
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ret = bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0)
  {
    perror("bind error");
    return -1;
  }
  ret = listen(s, 10); //监听
                       //建立子进程处理同时到来的客户端请求
  for (i = 0; i < PIDNUM; i++)
  {
    pid[i] = fork();
    if (pid[i] == 0)
    {
      handle(s);
    }
  }

  while (1)
    ;
  close(s);
}