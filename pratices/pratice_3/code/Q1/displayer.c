#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "fifoF"

struct cotacao {
    char moeda_origem[4];
    char moeda_destino[4];
    float valor;
    char data_hora[20];
};

int main() {
    int fd;
    struct cotacao cotacao;

    fd = open(FIFO_FILE, O_RDONLY);

    while (read(fd, &cotacao, sizeof(struct cotacao)) > 0) {
        printf("Moeda origem: %s\n", cotacao.moeda_origem);
        printf("Moeda destino: %s\n", cotacao.moeda_destino);
        printf("Valor: %.2f\n", cotacao.valor);
        printf("Data-hora: %s\n", cotacao.data_hora);
        printf("\n");
    }

    close(fd);

    return 0;
}
