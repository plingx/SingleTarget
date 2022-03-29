#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


/*
wait function
*/
/*   P93 & P94
int main(int argc, char* argv[])
{
    int status;
    pid_t pid = fork();
    pid_t p2;

    if(pid == -1){
        perror("fork error\n");
    }else if(pid == 0){
        printf("---child is created, pid= %d, parent-pid = %d\n",getpid(),getppid());

        sleep(10);                           // kill -9 child_pid

        printf("---------------child die---------------\n");

        return 73;

    }else if(pid > 0){
 
        // p2 = wait(NULL);                 // 不关心子进程结束原因。

        p2 = wait(&status);                 // 如果子进程未终止，父进程阻塞在此。

        if(WIFEXITED(status)){              // 为真，说明子进程正常终止。
            printf("child normal exit with %d\n",WEXITSTATUS(status));
        }

        if(WIFSIGNALED(status)){           // 为真，说明子进程是被信号终止的。
            printf("child signaled exit with %d\n",WTERMSIG(status)); 
        }

        printf("---parent process(pid:%d):child pid= %d terminate, status:%d\n",getpid(),p2,status);

    }

    return 0;
}
*/

// P95
int main(int argc, char* argv[])
{
    int status,i;
    pid_t pid,wpid,rpid;

    for(i=0;i<5;i++)
    {
        pid = fork();
        if(pid == 0)
        {
            // printf("i'm %dth child\n",i+1);
            break;
        }

        if(pid <0)
        {
            perror("fork error");
            exit(1);
        }

        if(i==2)
        {
            rpid = pid;
        }
    }

    if(i==5){           // 父进程

        // wpid = waitpid(-1,&status,WNOHANG);    // 回收任意子进程

        sleep(5);

        wpid = waitpid(rpid,&status,WNOHANG);    // 回收任意子进程

        if(wpid == -1){

            perror("waitpid error");

            exit(1);
        }

        printf("i'm parent ,wait a child finish : %d ,wpid:%d \n", rpid,wpid);
    }
    else {
        sleep(i);
        printf("i'm %dth child,pid = %d\n",i+1,getpid());
    }

    return 0;
}



