#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>


int vector[20];
int min, max, mode;
float avg;

void *maxVector() {

    int iterator;
    max = vector[0];
    for (iterator = 1; iterator < 19; iterator++) {
       if (vector[iterator] > max) max = vector[iterator];
    }
    pthread_exit(NULL);
}

void *minVector() {

    int iterator;
    min = vector[0];
    for (iterator = 1; iterator < 19; iterator++) {
        if (vector[iterator] < min) min = vector[iterator];
    }
    pthread_exit(NULL);
}

void *avgVector() {

    int iterator;
    int ans = 0;
    for (iterator = 0; iterator < 19; iterator++) {
        ans += vector[iterator];
    }

    avg =  ans/20;
    pthread_exit(NULL);
}

void *modeVector() {
   
   int iterator;   
   int maxCount = 0, j;
   mode = 0;
   for (iterator = 0; iterator < 20; ++iterator) {
      int count = 0;
      
      for (j = 0; j < 20; ++j) {
         if (vector[j] == vector[iterator])
         ++count;
      }
      
      if (count > maxCount) {
         maxCount = count;
         mode = vector[iterator];
      }
   }
}

int main() {
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    printf("seconds : %ld\nmicro seconds : %ld",    
    current_time.tv_sec, current_time.tv_usec
    );
    printf("\n");


    pthread_t thr[4];

    for (int i = 0; i < 20; i++) {
        vector[i] = rand() % 10 + 1;
    }

    int i = 0;
    if(pthread_create(&thr[i], NULL, maxVector, NULL)) {
        printf("Ops... Houve um erro na criação da thread %d.\n", i);
        return 0;
    }
    i++;
    if(pthread_create(&thr[i], NULL, minVector, NULL)) {
        printf("Ops... Houve um erro na criação da thread %d.\n", i);
        return 0;
    }
    i++;
    if(pthread_create(&thr[i], NULL, avgVector, NULL)) {
        printf("Ops... Houve um erro na criação da thread %d.\n", i);
        return 0;
    }
    i++;
    if(pthread_create(&thr[i], NULL, modeVector, NULL)) {
        printf("Ops... Houve um erro na criação da thread %d.\n", i);
        return 0;
    }

    (void) pthread_join(thr[0], NULL);
    (void) pthread_join(thr[1], NULL);
    (void) pthread_join(thr[2], NULL);
    (void) pthread_join(thr[3], NULL);

    printf("O valor do vetor é:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    printf("O valor máximo é: %d.\n", max);
    printf("O valor mínimo é: %d.\n", min);
    printf("O valor da moda é: %d.\n", mode);
    printf("O valor da média é: %.2f.\n", avg);
    
    gettimeofday(&current_time, NULL);
    printf("seconds : %ld\nmicro seconds : %ld",    
    current_time.tv_sec, current_time.tv_usec
    );
    printf("\n");
    pthread_exit(NULL);
}

