#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void print_set(sigset_t *set)
{
    int i;

    for(i=1;i<32;i++){
        if(sigismember(set,i)){
	    putchar('1');
	}else{
	    putchar('0');
	}
    }
    putchar('\n');
}

int main(int argc, char *argv[])
{
    sigset_t set,oldset,ret_set;

    int ret = 0;

    sigemptyset(&set);
    sigaddset(&set, SIGINT); // 将ctrl+c设置为屏蔽

    ret = sigprocmask(SIG_BLOCK, &set, &oldset);   // 用于读取or改变被调线程的signal mask
    if(ret == -1){
        sys_err("sigprocmask error");
    }

    while(1){
    	ret = sigpending(&ret_set);    // 返回被调线程的pending信号集
    	if(ret == -1){
       		sys_err("sigpending error");
    	}

    	print_set(&ret_set);
    
	sleep(2);
    }
    return 0;
}

