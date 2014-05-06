/*************************************************************************
  > File Name: workthread.cpp
  > Author: crooked
  > Mail:812665244@qq.com 
  > Created Time: Wed 23 Apr 2014 11:32:02 AM CST
 ************************************************************************/
#include"../inc/threadpool.h"
#include<iostream>
#include<stack>
//#include"workthread.h"
using namespace std;

void WorkThread::run()
{
	while(true)
	{
		Task task;
		/*
		 *如果获取任务时，返回值为false,那么说明线程池已经关闭，
		 *所以此时线程需要退出死循环
		 */
		bool ret=_p_thread_pool->get_task_queue(task);
		if(ret==false)
		{
			return;
		}
		compute_task(task);
	}
}


void WorkThread::compute_task(struct Task &task)
{
    char buf[]="hello";
  //  std::cout<<"i get here"<<std::endl;
  	sendto(_client_fd,buf,strlen(buf),0,(struct sockaddr*)&task._addr,sizeof(task._addr) );
   //	sendto(_client_fd,&result,sizeof(int),0,(struct sockaddr*)&task._addr,sizeof(task._addr) );
}
void WorkThread::register_thread_pool(ThreadPool *p_thread_pool)
{
  _p_thread_pool=p_thread_pool;
}
