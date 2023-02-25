#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep */
#include <stdio.h>

int G[5] = {0, 1, 2, 3, 4};

void executeSubtraction(int counter) {
    for (counter = 0; counter < 5; counter++) {
        G[counter]--;
    }    
}

void printVector(int counter) {
    for (counter = 0; counter < 4; counter++) {
        printf("%d ", G[counter]);
    }
    printf("%d\n", G[counter]);
}

int main(){
    int i;
    pid_t myFork = fork();
    if (myFork > 0) {
        printf("Eu sou o Pai e estou aguardando o filho realizar a subtração! Meu pid é %d\n", getpid());
        wait(NULL);
        printf("Pronto, o filho terminou a subtração! Vou apresentar o resultado. Meu pid é %d\n", getpid());
        printVector(i);
    }
    else if (!myFork) {
        printf("Eu sou o filho e vou subtrair 1 de cada posição do vetor! Meu pid é %d\n", getpid());
        executeSubtraction(i);
        printf("Subtração finalizada! Meu pid é %d\n", getpid());
    }
    else if (myFork <= -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }


    return 0;   
}

