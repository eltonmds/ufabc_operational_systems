#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE_NAME "/tmp/cotacoes"

struct cotacao {
    char moeda_origem[4];
    char moeda_destino[4];
    float valor;
    char data_hora[20];
};

int main() {
    int fd;
    struct cotacao cotacoes[15] = {
        {"USD", "BRL", 5.25, "2023-03-20T10:30:00"},
        {"EUR", "BRL", 6.20, "2023-03-20T10:31:00"},
        // Adicionar outras cotações aqui
    };

    // Criação do pipe nomeado
    mkfifo(PIPE_NAME, 0666);

    // Abertura do pipe nomeado para escrita
    fd = open(PIPE_NAME, O_WRONLY);

    // Escrita das cotações no pipe nomeado
    for (int i = 0; i < 15; i++) {
        write(fd, &cotacoes[i], sizeof(struct cotacao));
    }

    // Fechamento do pipe nomeado
    close(fd);

    // Remoção do pipe nomeado
    unlink(PIPE_NAME);

    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PIPE_NAME "/tmp/cotacoes"

struct cotacao {
    char moeda_origem[4];
    char moeda_destino[4];
    float valor;
    char data_hora[20];
};

int main() {
    int fd;
    struct cotacao cotacao;

    // Abertura do pipe nomeado para leitura
    fd = open(PIPE_NAME, O_RDONLY);

    // Leitura e apresentação das cotações do pipe nomeado
    while (read(fd, &cotacao, sizeof(struct cotacao)) > 0) {
        printf("Moeda origem: %s\n", cotacao.moeda_origem);
        printf("Moeda destino: %s\n", cotacao.moeda_destino);
        printf("Valor: %.2f\n", cotacao.valor);
        printf("Data e hora: %s\n", cotacao.data_hora);
        printf("\n");
    }

    // Fechamento do pipe nomeado
    close(fd);

    return 0;
}
