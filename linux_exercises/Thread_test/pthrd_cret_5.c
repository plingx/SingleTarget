#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


void sys_err(const char *str)
{
    perror(str);
    exit(1);
}


void *tfn(void *arg)
{
    int i;

    i = (int)arg;
    sleep(i+3);  
    printf("i'm %dth thread: pid = %d, tid = %lu \n", i+1, getpid(), pthread_self());

    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret,i;

    for( i=0 ; i<5 ; i++){
	ret = pthread_create(&tid, NULL, tfn, (void*)i); // 此处进行值传递，若传递地址则在线程执行时i值已变化
        if(ret != 0){
            perror("pthread_create error");
        }
    }

    sleep(i*2);
    
    printf("i'm Main: pid = %d, tid = %lu \n",getpid(), pthread_self());

    return 0;
}


