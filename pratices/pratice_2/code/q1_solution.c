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
