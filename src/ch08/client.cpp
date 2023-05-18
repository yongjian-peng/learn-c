#include <iostream>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
using namespace std;
//客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端
//客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端
//客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端
//客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端
//客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端-客户端
int main()
{
	int socketfd = 0;
	int acceptfd = 0;
	int len = 0;
	char buf[255] = { 0 };//初始化
 
	//网络-初始化
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
	{
		perror("socket error");
	}
	else
	{
		struct sockaddr_in s_addr;
 
		s_addr.sin_family = AF_INET;
 
		s_addr.sin_addr.s_addr = inet_addr("192.168.101.136");//Linux ubantu ip地址
 
		s_addr.sin_port = htons(10086);  //端口号为10086
 
		len = sizeof(s_addr);
 
		//绑定IP地址和端口号
		int res = connect(socketfd, (struct sockaddr*)&s_addr, len);
		if (res == -1)
		{
			perror("connect error");//连接失败
		}
		else
		{
			cout << "connect success" << endl;//连接成功
			while (1)
			{
				fgets(buf, sizeof(buf), stdin);//控制台输入
				write(socketfd, buf, sizeof(buf));
				bzero(buf, sizeof(buf));
			}
		}
	}
	return 0;
}