#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void sys_error(const char *str)
{
    perror(str);
    exit(1);
}


int main(int argc, char *argv[])
{
    pid_t pid;
    int ret,fd;

    pid = fork();    // 创建子进程
    if( pid>0 ){     // 父进程返回，子进程继续
        exit(0);
    }

    pid = setsid();  // 创建新会话
    if(pid == -1){
        sys_error("setsid error");
    }

    ret = chdir("/home/plingx/code/");    // 改变工作目录位置
    if(ret == -1){
        sys_error("chdir error");
    }

    umask(0022);                   // 文件访问权掩码限

    close(STDIN_FILENO);
    fd = open("/dev/null", O_RDWR);     // fd ---> 0 
    if(fd == -1){
        sys_error("open error");
    }

    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    while(1);

    return 0;
}


