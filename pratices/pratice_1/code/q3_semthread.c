#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int vector[20];
int min, max, mode;
float avg;

void maxVector() {
    int iterator;
    max = vector[0];
    for (iterator = 1; iterator < 19; iterator++) {
        if (vector[iterator] > max) max = vector[iterator];
    }
}

void minVector() {
    int iterator;
    min = vector[0];
    for (iterator = 1; iterator < 19; iterator++) {
        if (vector[iterator] < min) min = vector[iterator];
    }
}

void avgVector() {
    int iterator;
    int ans = 0;
    for (iterator = 0; iterator < 19; iterator++) {
        ans += vector[iterator];
    }

    avg =  ans/20;
    
}

void modeVector() {
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

    for (int i = 0; i < 20; i++) {
        vector[i] = rand() % 10 + 1;
    }

    maxVector();
    minVector();
    avgVector();
    modeVector();

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

    return 0;
}    