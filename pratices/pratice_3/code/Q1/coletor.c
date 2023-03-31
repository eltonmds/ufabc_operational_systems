#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define FIFO_FILE "fifoF"

struct cotacao {
    char moeda_origem[4];
    char moeda_destino[4];
    float valor;
    char data_hora[20];
};

int main() {
    int fd;
    struct cotacao cotacoes[15] = {
        {"USD", "BRL", 5.25, "2023-01-20T10:31:00"},
        {"EUR", "BRL", 6.20, "2023-01-20T10:31:00"},
        {"CNY", "BRL", 0.76, "2023-01-20T10:31:00"},
        {"RUB", "BRL", 0.07, "2023-01-20T10:31:00"},
        {"ARS", "BRL", 0.03, "2023-01-20T10:31:00"},
        {"ASA", "BRL", 0.30, "2023-01-20T10:31:00"},
        {"ABL", "BRL", 0.35, "2023-01-20T10:31:00"},
        {"SFR", "BRL", 5.35, "2023-01-20T10:31:00"},
        {"LEV", "BRL", 1.35, "2023-01-20T10:31:00"},
        {"BAR", "BRL", 3.35, "2023-01-20T10:31:00"},
        {"THS", "BRL", 2.35, "2023-01-20T10:31:00"},
        {"BTC", "BRL", 145000.25, "2023-01-20T10:31:00"},
        {"ETH", "BRL", 9430.35, "2023-01-20T10:31:00"},
        {"ADA", "BRL", 1.55, "2023-01-20T10:31:00"},
        {"AJA", "BRL", 2.35, "2023-01-20T10:31:00"},
        {"BOC", "BRL", 0.75, "2023-01-20T10:31:00"},
    };

    fd = open(FIFO_FILE, O_WRONLY);

    if (fd < 0) {
        perror("open");
        exit(1);
    }

    for (int i = 0; i < 15; i++) {
        write(fd, &cotacoes[i], sizeof(struct cotacao));
    }

    close(fd);

    return 0;
}
