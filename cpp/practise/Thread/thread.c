#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_NUM 4

pthread_mutex_t mtex;
pthread_cond_t condQ;

typedef struct Task {
    int a;
    int b;
} Task;

int taskNum = 0;
Task taskQueue[256];

void execute(Task* task) {
    usleep(50000);
    int result = task->a + task->b;
    printf("Task %d: %d + %d = %d\n", taskNum, task->a, task->b, result);
}

void submitTask(Task* task) {
    pthread_mutex_lock(&mtex);

    taskQueue[taskNum] = *task;
    taskNum++;
    pthread_cond_signal(&condQ);
    pthread_mutex_unlock(&mtex);
}

void* startExecute() {
    Task task;
    while(1) {
        pthread_mutex_lock(&mtex);
        while(taskNum == 0)
            pthread_cond_wait(&condQ, &mtex);

        task = taskQueue[0];
        for(int i = 0; i < taskNum - 1; i++) {
            taskQueue[i] = taskQueue[i + 1];
        }
        taskNum--;
        pthread_mutex_unlock(&mtex);
        execute(&task);
    };
}

int main(int argc, char* argv[]) {system("clear");
    pthread_t thr[THREAD_NUM];
    pthread_mutex_init(&mtex, NULL);
    pthread_cond_init(&condQ, NULL);

    for(int i = 0; i < THREAD_NUM; i++) {
        if(pthread_create(&thr[i], NULL, &startExecute, NULL))
            printf("ERROR: Failed creating Thread.\n");
    }

    for(int i = 0; i < 200; i++) {
        Task tsk = {
            .a = rand() % 100,
            .b = rand() % 100 
        };
        submitTask(&tsk);
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        if(pthread_join(&thr[i], NULL))
            printf("ERROR: Failed joining Thread.\n");
    }

    pthread_cond_destroy(&condQ);
    pthread_mutex_destroy(&mtex);
    return 0;
}