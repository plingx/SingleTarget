#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

/* 借助条件变量模拟 生产者-消费者 问题 */


/* 链表作为共享数据，需要被互斥量保护 */
struct msg{
    struct msg *next;
    int num;
};

struct msg *head;

/* 静态初始化 一个条件变量 和一个互斥量 */
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
    struct msg *mp;

    for(;;){
        pthread_mutex_lock(&lock);

        while( head == NULL){
            pthread_cond_wait(&has_product, &lock);
        }

        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&lock);

        printf("-Consume %lu---%d\n", pthread_self(), mp->num);

        free(mp);

        sleep(rand()%5);
    }
}

void *producer(void *p){
    struct msg *mp;

    for(;;){
        mp = malloc(sizeof(struct msg));
        mp->num = (rand()%1000) + 1;

        printf("-Produce ---------%d\n",mp->num);

        pthread_mutex_lock(&lock);

        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&has_product);

        sleep(rand()%5);
    }
}


int main(int argc, char* argv[])
{
    pthread_t pid, cid;

    srand(time(NULL));

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}
