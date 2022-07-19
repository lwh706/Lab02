#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef NUM_THREADS
#define NUM_THREADS 5   
#endif

void signal_handler(int);

void* myThread(void* threadid){
    while(1){
        long tid;
        tid = (long)threadid + 1;
        printf("I am thread %ld by 23219731\n", tid);
    //隨機睡眠
        int time_sleep;
        time_sleep = rand() % 11 + 0;
        printf("------------%ld------------wait %d sec\n", tid, time_sleep);
        sleep(time_sleep);
    }
    pthread_exit(NULL);
}

//主程式部分
int main(void){
    //
    srand(time(NULL));
    //
    struct sigaction act;
    act.sa_handler=signal_handler;
    sigemptyset(&act.sa_mask);
    //act.sa_flags=0;                  undo raise()
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGTSTP,&act,NULL);
    //
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, myThread, NULL);
        if (rc) {
            printf("ERORR; return code from pthread_create() is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
    for (t = 0; t < NUM_THREADS; t++) {
        void *retval;
        pthread_join(threads[t], &retval);
    }
    return 0;
}
//SIGINT handler
void signal_handler(int singo){
    if(singo==2){
        printf("\nSIGINT Caught!\n");
        exit(0);
    }
    else if(singo==20){
        printf("\nSIGTSTP Caught!\n");
    }
    else{
        exit(0);
    }
}