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
	string postfix=getPostfixExp(task._expression);
	//cout<<postfix<<endl;
	int result=postfixCalculate(postfix);
	sendto(_client_fd,&result,sizeof(int),0,(struct sockaddr*)&task._addr,sizeof(task._addr) );
}
void WorkThread::register_thread_pool(ThreadPool *p_thread_pool)
{
  _p_thread_pool=p_thread_pool;
}
string WorkThread::getPostfixExp(string &infix)
{
  stack<char> operator_stack;
  string postfix;
  for(int i=0;i<infix.size();i++)
  {
	char p=infix[i];
    if(isOperator(p))
	{
	  while(!operator_stack.empty()&&isOperator(operator_stack.top())&&priority(operator_stack.top())>=priority(p))
	  {
	    postfix.push_back(operator_stack.top());
		postfix.push_back(' ');
		operator_stack.pop();
	  }
	  operator_stack.push(p);
	}
	else if(p=='(')
	{
	  operator_stack.push(p);
	}
	else if(p==')')
	{
	  while(operator_stack.top()!='(')
	  {
	    postfix.push_back(operator_stack.top());
	    postfix.push_back(' ');
		operator_stack.pop();
	  }
	}
	else 
	{
	  postfix.push_back(p);
	  postfix.push_back(' ');
	}
  }
  while(!operator_stack.empty())
  {
     postfix.push_back(operator_stack.top());
     postfix.push_back(' ');
	 operator_stack.pop();
  }
  //postfix[postfix.size()-1]=' ';
  return postfix;
}

bool WorkThread::isOperator(char ch)
{
  switch(ch)
  {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
		  return true;
	  default:
		  return false;
  }
}

int WorkThread::priority(char a)
{
   int temp;
   if(a=='*'||a=='/')
	   temp=2;
   else if(a=='+'||a=='-')
	   temp=1;
   return temp;
}

int WorkThread::postfixCalculate(string &postfix)
{
   int first, second;
   stack<int> num_stack;
   for(int i=0;i<postfix.size();i++)
   {
     switch(postfix[i])
	 {
		 case '*':
			 getTwoNums(num_stack,first,second);
	         num_stack.push(first*second);
			 break;
		 case '/':
			 getTwoNums(num_stack,first,second);
	         num_stack.push(first/second);
			 break;
		 case '+':
			 getTwoNums(num_stack,first,second);
	         num_stack.push(first+second);
			 break;
		 case '-':
			 getTwoNums(num_stack,first,second);
	         num_stack.push(first-second);
			 break;
		 case ' ':
			 break;
		 default:
			 num_stack.push(postfix[i]-'0');
             break;
	 }
   }
   int result=num_stack.top();
   num_stack.pop();
   return result;
}

void WorkThread::getTwoNums(stack<int> &num_stack, int &first, int &second)
{
   second=num_stack.top();
   num_stack.pop();

   first=num_stack.top();
   num_stack.pop();
}

