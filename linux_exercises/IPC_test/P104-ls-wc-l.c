#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>



void sys_err(const char *str)
{
    perror(str);
    exit(1);
}


int main(int argc, char* argv[])
{
    int fd[2];
    int ret;
    pid_t pids;
    
    ret = pipe(fd);

    if(ret != 0)
    {
        sys_err("pipe created error");
    }

    pids = fork();
    if(pids == -1){
        sys_err("fork created error");
    }
    else if(pids == 0){        
        close(fd[0]);                        // close pipe read,open pipe write

        dup2(fd[1],STDOUT_FILENO);           // write <cmd result> to pipe

        execlp("ls", "ls", "-l", NULL);

        sys_err("exclp ls error");
    }else if(pids > 0){
        close(fd[1]);                        // close pipe write,open pipe read

        dup2(fd[0],STDIN_FILENO);

        execlp("wc", "wc", "-l", NULL);

        sys_err("exclp wc error");

    }

    return 0;
}





