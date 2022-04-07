#include <stdio.h>
#include <signal.h>
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


void sig_catch(int signo)
{
    if(signo == SIGINT){
        printf("catch you!! %d\n",signo);
    }else if(signo == SIGQUIT){
        printf("----catch you!! %d\n",signo);
    }
    
    return;
}


int main(int argc, char *argv[])
{
    struct sigaction act, oldact;
    
    act.sa_handler = sig_catch;       // 设置回调函数
    
    sigemptyset(&(act.sa_mask));      // 清空sa_mask屏蔽字，只在sig_catch工作时有效

    act.sa_flags = 0;                 // 默认值

    int ret = sigaction(SIGINT, &act, &oldact);
    if(ret == -1){
        sys_err("sigaction int error");
    }

    ret = sigaction(SIGQUIT, &act, &oldact);
    if(ret == -1){
        sys_err("sigaction quit error");
    }

    while(1);

    return 0;
}


