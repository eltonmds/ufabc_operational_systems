#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


int main() {
    const char* pipeF = "fifoF";

    if (mkfifo(pipeF, 0777) < 0) {
        printf("Ops...erro:");
        exit(1);
    }
    else {
        printf("Queue named pipe feita!!!\n");
    }
}
