#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<conio.h>
#include<stdlib.h>
#define MAX_PID 1000
#define MIN_PID 100

int var=MIN_PID;

struct pid{
	int address;
	pid *next;
}*generator;

int allocateMap()
{
	  	    	
	generator = NULL;
	return 1;
	
}
int check(int x)
{
	int flag=0;
	struct pid *temp=generator;
	while(temp!=NULL)
	{
	
		if(temp->address==x)
		{
			
			flag=1;
			break;
		}
	    temp=temp->next;
		
	}
	if(flag==1)
	{
		return 0;
	}
	else
	{
	
		return 1;
	}
	
}



int allocatePID()
{
	int flag=0;
	while(flag!=1)
	{
		flag=check(var);
		if(flag==0)
		{
			var++;
		}
		
	}
	struct pid *temp;
	temp= (struct pid*)malloc(sizeof(struct pid));
	temp->address=var;
	temp->next=generator;
	generator=temp;
	temp=generator;

	return var;
	
	

	 
}


void release(int pp)
{
	struct pid *temp,*np,*prev=NULL;
	temp=generator;
	while(temp->next!=NULL)
	{
		if(temp->address==pp)
		{
			break;
		}
		prev=temp;
		temp=temp->next;
		
	}
	if(prev==NULL)
	{
		generator=generator->next;
	}
	else if(temp->next=NULL)
	{
		prev->next=NULL;
		
	}
	else
	{
		prev->next=temp->next;
	}
}


void* func1()
{
	int x = allocatePID();
	printf("the allocated process id is %d",x);
	printf("Thread completed process id released");
	release(x);
	
}

void* func2()
{
	int x = allocatePID();
	printf("id allocated %d",x);
	printf("Thread completed id released");
	release(x);
}

void* func3()
{
	int x = allocatePID();
	printf("Id allocated %d",x);
	printf("Thread completed id released");
	release(x);
}

main()
{
	if(allocateMap())
	{
		printf("Generator set correctly");
		
	}
	pthread_t pid1,pid2,pid3;
	pthread_create(&pid1,NULL,func1,NULL);
	pthread_create(&pid2,NULL,func2,NULL);	
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	pthread_create(&pid2,NULL,func3,NULL);
	pthread_join(pid3,NULL);
	
	
	
}
