/*************************************************************************
  > File Name: test.cpp
  > Author: crooked
  > Mail:812665244@qq.com 
  > Created Time: Wed 23 Apr 2014 12:17:05 PM CST
 ************************************************************************/

#include"threadpool.h"
#include"socket.h"
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<fstream>
#include<string.h>
using namespace std;

int main(int argc, char **argv)
{
	std::ifstream fin(argv[1]);
	std::string ip,port;
	fin>>ip>>port;
//  ip="192.168.21.136";
//	port="6688";
	std::cout<<ip<<" "<<port<<std::endl;
	const socklen_t len=1024;
	char buf[len];
	MySocket a_socket(ip, port);

	ThreadPool pool(10);
	pool.start_thread_pool();
	while(true)
	{
		memset(buf, 0, len);
		int ret=a_socket.recv_message(buf, len); 
		cout<<ret<<endl;
		Task tmp;
		tmp._addr=a_socket.get_client();
		tmp._expression=buf;
		pool.add_task_queue(tmp);
		sleep(1);
	}
    pool.stop_thread_pool();
	return 0;

}
