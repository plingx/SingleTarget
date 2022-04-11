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


struct thrd{
    int var;
    char str[100];
};

void *tfn(void *arg)
{
    struct thrd *pval;

    pval = malloc(sizeof(struct thrd));
    
    pval->var = 100;
    strcpy(pval->str, "hello thread");

    return (void*)pval;
}


int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret;
    struct thrd *rpval;
    
    ret = pthread_create(&tid, NULL, tfn, NULL); // 
    if(ret != 0){
        perror("pthread_create error");
    }

    ret = pthread_join(tid, (void **)&rpval);    
    if(ret != 0){
        perror("pthread_join error");
    }
   
    printf("child thread exit with var = %d, str = %s \n", rpval->var, rpval->str);

    pthread_exit(NULL);
}


