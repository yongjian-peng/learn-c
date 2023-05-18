#include <iostream>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
using namespace std;
//服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器
//服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器
//服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器
//服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器
//服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器-服务器
int main()
{
	int socketfd = 0;
	int acceptfd = 0;
	int len = 0;
	int pid = 0;
	char buf[255] = { 0 };//存放客户端发过来的信息
 
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
	{
		perror("socket error");//socket 报错
	}
	else
	{
		struct sockaddr_in s_addr;
		s_addr.sin_family = AF_INET;
		//默认提供IP地址（服务器自己）因为服务器是被动，需要客户端来连接所以网路通道打开是服务器自己
		s_addr.sin_addr.s_addr = inet_addr("192.168.101.136");//linux ubantu iP地址 
		//端口号（服务器自己）大小端模式 内存存储字节转换
		s_addr.sin_port = htons(10086);	//端口号为10086
 
		len = sizeof(s_addr);
 
		//绑定IP地址和端口号
		int res = bind(socketfd, (struct sockaddr*)&s_addr, len);
		if (res == -1)
		{
			perror("bind error");//bind 报错
		}
		else
		{
			//监听：地址和端口有没有客户端连接上
			if (listen(socketfd, 2) == -1)
			{
				//listen 监听失败
				perror("listen error");
			}
			cout << "socket 网络搭建成功" << endl;
 
			//设置死循环：保证服务器一直在线
			while (1)
			{
				cout << "稍等片刻-等待连接-客户端" << endl;
 
				//阻塞式函数  acceptfd
				acceptfd = accept(socketfd, NULL, NULL);
				cout << "恭喜恭喜-连接成功-客户端 socketfd = " << acceptfd << endl;
 
				pid = fork();//创建子进程 子进程：保持运行提供服务到结束
				if (pid == 0)
				{
					while (1)
					{
						int res = read(acceptfd, buf, sizeof(buf));
						cout << "pid = " << getpid() << "res = "<< res << endl;
						cout << " 输入内容: " << buf << endl;
						bzero(buf, sizeof(buf));
					}
				}
			}
		}
	}
}