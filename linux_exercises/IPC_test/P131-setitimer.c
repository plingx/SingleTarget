#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

void myfunc(int signo)
{
    printf("hello world\n");
}


int main(void)
{
    struct itimerval it, oldit;

    signal(SIGALRM, myfunc);     //  注册SIGALARM信号的捕捉处理函数

    it.it_value.tv_sec = 2;      // 设置定时的时长为2s 即第一次执行helloworld是在运行后2s
    it.it_value.tv_usec = 0;

    it.it_interval.tv_sec = 10;   // 设置2次定时任务之间的间隔为5s 即第2,3,4...次执行是在12s,22s,32s,42s,52s...时执行heloworld
    it.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &it, &oldit) == -1){
	    perror("setitimer error");
	    return -1;
    }

    while(1);

    return 0;
}
