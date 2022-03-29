#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


// P98 回收多个子进程
int main(int argc, char* argv[])
{
    int status,i;
    pid_t pid,wpid;

    for(i=0;i<5;i++)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }

        if(pid <0)
        {
            perror("fork error");
            exit(1);
        }

    }

    if(i==5){           // 父进程
        // 使用阻塞方式回收子进程  start
        // while(wpid = waitpid(-1, &status, 0))
        // {
        //     if(wpid == -1)
        //     {
        //         printf("wait child error:-1 , game over\n");
        //         break;
        //     }
            
        //     printf("wait child pid:%d \n",wpid);
        // }
        // 使用阻塞方式回收子进程  end

        // 使用非阻塞方式回收子进程 start
        while((wpid = waitpid(-1, &status, WNOHANG) != -1))
        {
            if(wpid == 0)
            {
                sleep(2);continue;
            }
            else if(wpid > 0){
                printf("wait pid:%d success\n",wpid);
            }
        }
        printf("wait child error:-1 , game over\n");
        // 使用非阻塞方式回收子进程 end
    }
    else {
        sleep(i);
        printf("i'm %dth child,pid = %d\n",i+1,getpid());
    }

    return 0;
}