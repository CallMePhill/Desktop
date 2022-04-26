#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;

void* roll_dice() {
    pthread_mutex_lock(&mutex);

    int value = ((rand() % 6) + 1);
    int* result = malloc(sizeof(int));
    *result = value;

    pthread_mutex_unlock(&mutex);
    return (void *) result;
}

int main(int argc, char* argv[]) {system("clear");
    pthread_mutex_init(&mutex, NULL);
    
    srand(time(NULL));

    int number_of_threads = (argc > 1)? atoi(argv[1]) : 1;
    pthread_t thr[number_of_threads];

    int* result = NULL;
    int total = 0;

    for(int i = 0; i < number_of_threads; i++) {
        if(pthread_create(&thr[i], NULL, &roll_dice, NULL)) 
            perror("ERROR: Failed to creating thread.");
    }

    for(int i = 0; i < number_of_threads; i++) {
        if(pthread_join(thr[i], (void**) &result))
            perror("ERROR: Failed to creating thread.");
        printf("Dice %d: %d\n", i+1, *result);
        total += *result;
    }

    printf("-------------\nTổng: %d\n", total);
    char* res1 = (total % 2)? "Lẻ" : "Chẵn";
    char* res2 = (total >= 10)? "Tài" : "Xỉu";
    printf("Kết quả 1: %s\n", res1);
    printf("Kết quả 2: %s\n", res2);

    free(result);
    pthread_mutex_destroy(&mutex);
    return 0;
}