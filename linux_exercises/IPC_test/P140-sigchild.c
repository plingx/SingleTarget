#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}


void child_catch(int signo)
{
    pid_t wpid;
    int status;

    ///while(wpid = wait(NULL)){
    while((wpid = waitpid(-1, &status, 0)) != -1){    // 循环回收，防止僵尸进程出现
	if(WIFEXITED(status))
        printf("--------------------catch child id %d,ret=%d \n",wpid,WEXITSTATUS(status));
   }
    
    return;
}


int main(int argc, char *argv[])
{
    pid_t pid;
    int i,ret;

    for(i=0;i<15;i++){
        if((pid = fork())==0)
	    break;
    }

    if(i == 15){
    
        struct sigaction act;
    
        act.sa_handler = child_catch;          // 设置回调函数
    
        sigemptyset(&(act.sa_mask));           // 设置捕捉函数执行期间屏蔽字

        act.sa_flags = 0;                      // 设置默认属性，本信号自动屏蔽
    
        ret = sigaction(SIGCHLD, &act, NULL);  // 注册信号捕捉函数

	printf("I'm parent, pid = %d \n",pid);

	while(1);
    
    }else{
        printf("I'm child pid=%d \n",getpid());
        return i;
    }

    return 0;
}


