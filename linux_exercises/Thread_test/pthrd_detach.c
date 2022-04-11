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
    printf("thread pid:%d, tid:%ld \n", getpid(), pthread_self());   

    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, tfn, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread create error:%s\n", strerror(ret)); //线程中的errno使用strerror()来解析，perror()是为进程中出错解析使用
	exit(1);
    }

    ret = pthread_detach(tid);               // 设置线程分离
    if( ret != 0){
        fprintf(stderr, "pthread detach error:%s\n", strerror(ret));    
	exit(1);
    }

    sleep(1);

    ret = pthread_join(tid, NULL);
    printf("join ret = %d\n", ret); 
    if( ret != 0){
        fprintf(stderr, "pthread join error:%s\n", strerror(ret));
	exit(1);
    }

    printf("main: pid = %d, tid = %lu \n", getpid(), pthread_self());

    pthread_exit((void*)0);
}


