#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex_t;    // 定义一把互斥锁


void *tfn(void *arg)
{
    srand(time(NULL));

    while(1){
        pthread_mutex_lock(&mutex_t);
        printf("hello ");
        sleep(rand()%3);
        printf("world\n");
        pthread_mutex_unlock(&mutex_t);
        sleep(rand()%3);
    } 

    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret; 

    srand(time(NULL));

    ret = pthread_mutex_init(&mutex_t, NULL);    // 初始化互斥锁
    if(ret != 0){
        fprintf(stderr, "mutex_t init error:%s", strerror(ret));
        exit(1);
    }

    pthread_create(&tid, NULL, tfn, NULL);
    while(1){
        pthread_mutex_lock(&mutex_t);
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex_t);
        sleep(rand()%3);
    }

    pthread_join(tid, NULL);

    return 0;
}


