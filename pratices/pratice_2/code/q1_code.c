#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX 10;
int RECURSO_MAXIMO = MAX;

// Cada thread utiliza as mesmas funções

// Essa função aloca a quantidade de recursos desejada, se existir
int aloca_recurso (int recurso_desejado) {
    if (RECURSO_MAXIMO - recurso_desejado < 0)
        return 0;
    else {
        RECURSO_MAXIMO -= recurso_desejado;
        return 0;
    }
}

// Essa função devolve uma certa quantidade de recursos alocados
int desaloca_recurso(int recurso_devolvido) {
    if (RECURSO_MAXIMO + recurso_devolvido > 10)
        return 0;
    
    RECURSO_MAXIMO += recurso_devolvido;
    return 0;
}


void *thread1() {
    printf("Olá, sou a thread 1!\n");
    int i = 0;
    // Começo da sessão crítica
    while (i < 10) {
    aloca_recurso(i);
    sleep((rand() % 10 + 1)/10);
    desaloca_recurso(i);
    printf("t1: RECURSO_MAXIMO: %d\n", RECURSO_MAXIMO);
    i++;
    }
    // Fim da sessão crítica
    pthread_exit(NULL);
}

void *thread2() {
    printf("Olá, sou a thread 2!\n");
    int i = 0;
    // Começo da sessão crítica
    while (i < 10) {
    aloca_recurso(i);
    sleep((rand() % 10+1)/10);
    desaloca_recurso(i);
    printf("t2: RECURSO_MAXIMO: %d\n", RECURSO_MAXIMO);
    }
    // Fim da sessão crítica
    pthread_exit(NULL);
}

int main() {
    pthread_t thr[2];

    int i = 0;
    if(pthread_create(&thr[i], NULL, thread1, NULL)) {
        printf("Ops... Houve um erro na criação da thread %d.\n", i);
        return 0;
    }
    i++;

    if(pthread_create(&thr[i], NULL, thread2, NULL)) {
        printf("Ops... Houve um erro na criação da thread %d.\n", i);
        return 0;
    }
    printf("Final: RECURSO_MAXIMO: %d\n", RECURSO_MAXIMO);
}