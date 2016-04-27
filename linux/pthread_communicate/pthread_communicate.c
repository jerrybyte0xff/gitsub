/******************************************************************
Function：通过互斥锁的方式实现线程间通信
	  1 线程1 获取数据
	  2 线程2 接收线程1获取的数据
	  3 只要线程1 取到数据线程2随时可以取走。但是当线程1取到的数据存储不能超过10个
athuor:   liuzunchang
version:  2014/12/25
*****************************************************************/  
#include<stdio.h>  
#include<memory.h>  
#include<pthread.h>  

#define SEND_NUM 100

/* 共享内存  */
int ShareMemory[101];  
/* 是读指针，w是写指针  */
int iwriteposition = 0,ireadposition = 0; 
/* 缓冲区大小  */
int ibuffersize = 10; 
/* 锁  */
pthread_mutex_t pthreadmutex_lock;  
pthread_cond_t pthread_cond_empty; //缓冲区是否为空  
pthread_cond_t pthread_cond_full;  //缓冲区是否已满  
void *sender(void)     //发送100个数据  
{  
    int icount;   
    for (icount = 0; icount < SEND_NUM; icount++)   //总共100个数据  
    {  
        pthread_mutex_lock(&pthreadmutex_lock);  //锁  
        if (iwriteposition - ireadposition > ibuffersize)     //缓冲区是否已满  
        { 
            printf("send Waiting");
	        pthread_cond_wait(&pthread_cond_full, &pthreadmutex_lock);  //满了，等待接受线程把数据取走  
        }         
        ShareMemory[iwriteposition++] = icount;  //缓冲区有空间，发送  
        printf("send:--->%d\n", icount); //打印出来  
        pthread_cond_signal(&pthread_cond_empty);  //缓冲区里至少有一个数据，读线程可以把他取走  
        pthread_mutex_unlock(&pthreadmutex_lock);    //解锁  
    }  
}  
void *receiver(void)    //接受数据  
{  
    int idata;  
    while(1)  
    {  
        pthread_mutex_lock(&pthreadmutex_lock);  //锁  
        if (ireadposition == iwriteposition)     //缓冲区没有数据  
        {
             printf("receive Waiting");
	         pthread_cond_wait(&pthread_cond_empty,&pthreadmutex_lock);  //没有数据，等待发送线程发数据 
             
        } 
        idata = ShareMemory[ireadposition++];   //有数据了，取走  
        if(idata != (SEND_NUM - 1))  
        {
        	printf("receive--->%d\n",idata);  //打印出来
	        pthread_cond_signal(&pthread_cond_full);  //缓冲区至少还有一个空间可以让发送进程发送数据  
	        pthread_mutex_unlock(&pthreadmutex_lock);     //解锁  
        }
        else  
        {
            printf("receive--->%d\n",idata);  //打印出来
	        pthread_mutex_unlock(&pthreadmutex_lock); 
           	break;    //数据发送->接受完了，结束线程  
        }
    }    
}  
int main()  
{  
    void *recycle;  //线程结束时，存放回收的数据  

    memset(ShareMemory,0,sizeof(ShareMemory));  
    pthread_t pthread_receive,pthread_send; //创建两个线程  typedef unsigned long int pthread_t 只是创建两个长整型来记录线程的ID 
    //初始化  
    pthread_mutex_init(&pthreadmutex_lock,NULL); 

    pthread_cond_init(&pthread_cond_full,NULL);  
    pthread_cond_init(&pthread_cond_empty,NULL); 

    //线程开始工作  
    pthread_create(&pthread_send, NULL, receiver, NULL);  
    pthread_create(&pthread_receive, NULL, sender, NULL);  


    printf("waiting Recive\n");
    pthread_join(pthread_receive, &recycle); //回收资源 
    printf("waiting send\n"); 
    pthread_join(pthread_send, &recycle);  //回收资源  
    return 0;  
}  

