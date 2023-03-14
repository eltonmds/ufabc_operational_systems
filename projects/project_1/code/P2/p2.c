#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep */
#include <stdio.h>

/* Lib - System Call Signal */
#include <signal.h>

// Variaveis globais
int file1Open = 1; /* Arquivo hipotetico 1 */
int file2Open = 1; /* Arquivo hipotetico 2 */
int valor1 = 500;

void finish_process() {
    file1Open = 0;
    file2Open = 0;
    printf("Arquivos fechados!\n");
    printf("O conteúdo de 'valor1' é: %d\n", valor1);
    printf("Encerrando o processo...\n");
    exit(0);
    printf("Processo encerrado.\n");
}

/* Definicao da funcao em C que ira tratar das interrupcoes */
void signal_handler(int signum) {
    if (signum == SIGTERM) {
        finish_process();
    }
    else if (signum == SIGINT) {
        char deseja_parar;
        printf("Deseja realmente parar o processo?\nSe sim, digite x.\n");
        scanf("&c", deseja_parar);
        if (deseja_parar == 'x' || deseja_parar == 'X') {
            finish_process();
        }
    } 
}





int main() {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    pid_t pid;
    pid = fork();
    if (!pid) {
        printf( "Sou o FILHO. %d\n", getpid() );
        return 0;
    }
    else if (pid) {
        printf( "Sou o PAI. %d\n", getpid() );
        valor1 /= 20;
        wait(NULL);
        while (1);
        printf("O status do file1Open eh %d e o file2Open eh %d \n", file1Open,
        file2Open);
        printf(" O valor1 = %d\n",valor1);
        return 0;
    }
}
