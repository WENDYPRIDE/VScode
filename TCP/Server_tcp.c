#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
/**
TCP循环服务器
在accept处阻塞等待客户端的连接，并处理请求
**/
#define PORT 8888
#define BUFFERSIZE 1024
#define LISTEN 10
int main(int argc, char *argv[])
{
  int s;
  int ret;
  int len;
  int size;
  int sc;
  time_t now;
  char buffer[BUFFERSIZE];
  struct sockaddr_in server_addr, client_addr;
  //建立流式套接字
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
  {
    perror("socket error");
    return -1;
  }
  //将地址绑定到套接字上
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  ret = bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0)
  {
    perror("bind error");
    return -1;
  }
  //监听队列的长度
  listen(s, LISTEN);
  len = sizeof(client_addr);
  //接受客户端的请求
  while (1)
  {
    sc = accept(s, (struct sockaddr *)&client_addr, &len); //等待客户端的连接，client_addr存放的是客户端的信息
    memset(buffer, 0, BUFFERSIZE);
    size = recv(sc, buffer, BUFFERSIZE, 0); //利用套接字描述符sc进行通信

    /***************************/
    int temp = atoi(buffer);
    /***************************/
    if (size < 0)
    {
      perror("recv error");
      break;
    }
    else if (temp)
    {
      for (int i = temp; i > 0; i--)
      {
        memset(buffer, 0, BUFFERSIZE);
        sprintf(buffer, "%d", i);
        send(sc, buffer, strlen(buffer), 0);
      }

      // now = time(NULL);
      // sprintf(buffer, "%24s", ctime(&now));
      // send(sc, buffer, strlen(buffer), 0);
    }

    close(sc); //关闭本次通信的客户端连接
  }

  close(s);
  return 0;
}