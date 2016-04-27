    #include<stdio.h>  
    #include<memory.h>  
    #include<pthread.h>  
    int buf[1000000];  
    int w=0,r=0; //r是读指针，w是写指针  
    int size=10; //缓冲区大小  
    pthread_mutex_t lock; //锁  
    pthread_cond_t is_empty; //缓冲区是否为空  
    pthread_cond_t is_full;  //缓冲区是否已满  
    void *sender(void *a)     //发送100个数据  
    {  
        int i,j,k;  
        for(i=1;i<=100;i++)   //总共100个数据  
        {  
            pthread_mutex_lock(&lock);  //锁  
            if(w-r>size)     //缓冲区是否已满  
            pthread_cond_wait(&is_full,&lock);  //满了，等待接受线程把数据取走  
            buf[w++]=i;  //缓冲区有空间，发送  
            printf("%d--->/n",i); //打印出来  
            pthread_cond_signal(&is_empty);  //缓冲区里至少有一个数据，读线程可以把他取走  
            pthread_mutex_unlock(&lock);    //解锁  
        }  
        return ;  
    }  
    void *receiver(void *a)    //接受数据  
    {  
        int x;  
        while(1)  
        {  
            pthread_mutex_lock(&lock);  //锁  
            if(r==w)     //缓冲区是否有数据  
            pthread_cond_wait(&is_empty,&lock);  //没有数据，等待发送线程发数据  
            x=buf[r++];   //有数据了，取走  
            if(x!=0)  
            printf("--->%d/n",x);  //打印出来  
            else  
            break;    //数据发送->接受完了，结束线程  
            pthread_cond_signal(&is_full);  //缓冲区至少还有一个空间可以让发送进程发送数据  
            pthread_mutex_unlock(&lock);     //解锁  
        }  
        return ;  
    }  
    int main()  
    {  
        memset(buf,0,sizeof(buf));  
        pthread_t a,b; //创建两个线程  
        //初始化  
        pthread_mutex_init(&lock,NULL);  
        pthread_cond_init(&is_full,NULL);  
        pthread_cond_init(&is_empty,NULL);  
        //线程开始工作  
        pthread_create(&a,NULL,sender,0);  
        pthread_create(&b,NULL,receiver,0);  
        void *recycle;  //线程结束时，存放回收的数据  
        pthread_join(a,&recycle); //回收资源  
        pthread_join(b,&recycle);  //回收资源  
        return 0;  
    }  
