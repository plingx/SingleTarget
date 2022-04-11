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

void *tfn1(void *arg)
{
    printf("thread 1 running \n");    // 返回到调用线程的地方，返回值为111

    return (void*)111;
}

void *tfn2(void *arg)
{
    printf("thread 2 exiting \n");    // 退出线程，返回值为222

    pthread_exit((void*)222);
}

void *tfn3(void *arg)
{
    while(1)
    {  
        printf("thread3 I'm going to die in 3 seconds ...\n");
        sleep(1);
/*	 pthread_testcancel();  // 自己添加取消点 */ 
    }

    return (void *)666;
}




int main(int argc, char *argv[])
{
    pthread_t tid;
    void *tret=NULL;
    int ret;

    pthread_create(&tid, NULL, tfn1, NULL);
    ret = pthread_join(tid, &tret);                 // 等待指定线程终止并回收，获取线程返回值
    if(ret != 0){
        sys_err("pthread1 join error");
    }
    printf("thread 1 exit code = %d \n\n", (int)tret);

    pthread_create(&tid, NULL, tfn2, NULL);
    ret = pthread_join(tid, &tret);
    if(ret != 0){
        sys_err("pthread2 join error");
    }
    printf("thread 2 exit code = %d \n\n", (int)tret);

    pthread_create(&tid, NULL, tfn3, NULL);
    sleep(3);
    ret = pthread_cancel(tid);                            // 发送终止线程3请求，
    if(ret != 0){
        sys_err("pthread3 cancel error");
    }

    ret = pthread_join(tid, &tret);                      // 回收线程3
    if(ret != 0){
        sys_err("pthread3 join error");
    }
    printf("thread 3 exit code = %d \n\n", (int)tret);

    return 0;
}


