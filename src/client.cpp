/*************************************************************************
	> File Name: client.cpp
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Mon 28 Apr 2014 09:40:02 AM CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<fstream>
#include<string>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdexcept>
int main(int argc, char *argv[])
{
    std::ifstream fin(argv[1]);
	std::string ip, port, word;
	fin >> ip >> port;
    std::cout<<ip<<" "<<" port "<<port <<std::endl;
    int server_fd=socket(AF_INET, SOCK_DGRAM, 0);
	if(server_fd==-1)
	{
	  throw std::runtime_error("socket");
	}
    struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(port.c_str()));
	server_addr.sin_addr.s_addr=inet_addr(ip.c_str());
    //int result;
    char buf[128]="";
    memset(buf, 0, 128);
	while(std::cin>>word)
	{
	  int iret=sendto(server_fd, word.c_str(),word.size(),0,(struct sockaddr*)&server_addr, 16);
	  recvfrom(server_fd, buf, 128, 0, NULL, NULL);
	 // std::cout<<"result: "<<result<<std::endl;
       std::cout<<buf<<std::endl;
	}
	return 0;
}
