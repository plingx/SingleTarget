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
    printf("thread: pid = %d, tid = %lu \n", getpid(), pthread_self());

    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, tfn, NULL);
    if(ret != 0){
        perror("pthread_create error");
    }

    printf("main: pid = %d, tid = %lu \n",getpid(), pthread_self());// 获取线程ID

    sleep(1);    // 如果无此延时，则在进程执行返回后，其地址空间被回收，线程也无机会被执行。

    return 0;
}


