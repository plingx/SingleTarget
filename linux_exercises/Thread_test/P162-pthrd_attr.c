#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>



void *tfn(void *arg)
{
    printf("thread: pid = %d, tid = %lu \n", getpid(), pthread_self());

    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret;
    pthread_attr_t attr;

    ret = pthread_attr_init(&attr);   // 初始化线程属性，将attr的值初始化为默认数值
    if(ret != 0){
        fprintf(stderr, "attr_init error:%s\n",strerror(ret));
	exit(1);
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//设置线程属性为分离态
    if(ret != 0){
        fprintf(stderr, "attr_setdetachstate error:%s\n",strerror(ret));
	exit(1);
    }

    ret = pthread_create(&tid, &attr, tfn, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error:%s\n",strerror(ret));
    }


    ret = pthread_attr_destroy(&attr);   // 销毁线程属性
    if(ret != 0){
        fprintf(stderr, "attr_destroy error:%s\n",strerror(ret));
	exit(1);
    }

    ret = pthread_join(tid, NULL); 
    if(ret != 0){
        fprintf(stderr, "pthread join error:%s\n",strerror(ret));
	exit(1);
    }

    printf("main: pid = %d, tid = %lu \n",getpid(), pthread_self());// 获取线程ID

    pthread_exit((void*)0);

}


