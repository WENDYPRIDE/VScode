#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
/**
UDP循环服务器
原理:服务器在recv函数与处理业务之间轮循处理
**/
#define PORT 8888
#define BUFFERSIZE 1024
int main(int argc, char *argv[])
{
   int s;
   struct sockaddr_in server_addr, client_addr; //分别表示客户端地址与服务器端地址
   time_t now;
   int ret;
   int size;
   char buffer[BUFFERSIZE];
   //建立数报套接字
   s = socket(AF_INET, SOCK_DGRAM, 0); //数据报
   if (s < 0)
   {
      perror("socket error");
      return -1;
   }
   //地址绑定
   bzero(&server_addr, sizeof(server_addr)); //地址结构清0
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   server_addr.sin_port = htons(PORT);
   ret = bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
   if (ret == -1)
   {
      perror("bind error");
      return -1;
   }
   //数据报套接字没有流量控制所以没有监听listen，也没有三次握手，所以没有接受连接accept
   while (1)
   {
      memset(buffer, 0, BUFFERSIZE); //清0
      int len = sizeof(client_addr);
      size = recvfrom(s, buffer, BUFFERSIZE, 0, (struct sockaddr *)&client_addr, &len);
      if (size <= 0)
      {
         perror("recvfrom");
      }
      else
      {
         if (!strncmp(buffer, "TIME", 4))
         { //判断是否是合法数据
            memset(buffer, 0, BUFFERSIZE);
            now = time(NULL);                                                           //获得当前时间
            sprintf(buffer, "%24s", ctime(&now));                                       // ctime所指向的最后一个字符是\n
            sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, len); //发送数据，第3项表示发送数据的长度
         }
      }
   }
   close(s);
   return 0;
}