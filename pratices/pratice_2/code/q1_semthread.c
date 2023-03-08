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
    if (RECURSO_MAXIMO < recurso_desejado)
        return -1;
    else {
        RECURSO_MAXIMO -= recurso_desejado;
        return 0;
    }
}

// Essa função devolve uma certa quantidade de recursos alocados
int desaloca_recurso(int recurso_devolvido) {
    RECURSO_MAXIMO += recurso_devolvido;
    return 0;
}


int main() {
    pthread_t thr[4];
    int i;

    

    for (i = 0; i < 10; i++)
    {
        aloca_recurso(rand() % 10 + 1);
        desaloca_recurso(rand() % 10 + 1);

        if (RECURSO_MAXIMO > 10) {
            printf("RECURSO: %d\n", RECURSO_MAXIMO);
            break;
        }
        
    }
    
    printf("Final: RECURSO_MAXIMO: %d\n", RECURSO_MAXIMO);
}