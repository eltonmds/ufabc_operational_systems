#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int matrixA[3][3];
int matrixB[3][3];
int matrixF[3][3];

void *somaMatriz(void *pos) {
    int k = (int *)pos;

    for (int i = 0; i < 3; i++) {
        printf("Eu sou uma thread criada pelo programador. Trato a linha %d.\n", k);
        matrixF[k][i] = matrixA[k][i] + matrixB[k][i];
        printf("MatrixA %d, MatrixB %d, MatrixF %d.\n", matrixA[k][i], matrixB[k][i], matrixF[k][i]);
        sleep(15);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thr[3];
    printf("O processo principal é %d\n", getpid());

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixA[i][j] = rand() % 10 + 1;
            matrixB[i][j] = rand() % 50 + 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if(pthread_create(&thr[i], NULL, somaMatriz, (void *)i)) {
            printf("Ops... Houve um erro na criação da thread %d.\n", i);
            return 0;
        }
    }

    printf("As threads são iguais? Resp: %d.\n", pthread_equal(thr[0], thr[1]));
    printf("As threads são iguais? Resp: %d.\n", pthread_equal(thr[0], thr[2]));
    printf("As threads são iguais? Resp: %d.\n", pthread_equal(thr[2], thr[1]));

    (void) pthread_join(thr[0], NULL);
    (void) pthread_join(thr[1], NULL);
    (void) pthread_join(thr[2], NULL);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("O valor da MatrixF na linha %d e coluna %d eh %d.\n", i, j, matrixF[i][j]);
        }
    } 

    pthread_exit(NULL);

}