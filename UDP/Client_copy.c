#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
/**
UDP客店端，客户端向服务器发送时间请求，服务器返回相应的时间
**/
#define PORT 8888
#define BUFFERSIZE 1024
int main(int argc, char *argv[])
{
  int s;   //套接字描述符
  int ret; //建立套接字的返回值
  int size;
  struct sockaddr_in server_addr; //地址结构
  int len;
  char buffer[BUFFERSIZE];
  /***********************/
  char temp[20];
  printf("Enter Your Number:");
  gets(temp);
  // printf(temp);
  /*********************/

  s = socket(AF_INET, SOCK_DGRAM, 0); //建立流式套接字
  if (s < 0)
  {
    perror("socket error");
    return -1;
  }
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  memset(buffer, 0, BUFFERSIZE);
  strcpy(buffer, temp);
  //向服务器发送数据
  size = sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (size < 0)
  {
    perror("sendto error");
    return -1;
  }
  //从服务器接收数据
  len = sizeof(server_addr);
  int temp_1 = atoi(buffer); 
  while (temp_1)
  {
    temp_1--;
    size = recvfrom(s, buffer, BUFFERSIZE, 0, (struct sockaddr *)&server_addr, &len);
    if (size < 0)
    {
      perror("recvfrom error");
      return -1;
    }
    // write(1,buffer,size);
    printf("%s\n", buffer);
  }

  close(s);
  return 0;
}