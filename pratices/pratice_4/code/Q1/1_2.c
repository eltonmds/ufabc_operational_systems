#include <stdio.h>
#define Size 64

int main() {
    int A[Size][Size], B[Size][Size], C[Size][Size];
    int i, j;
    int page_faults = -3; // variável para contagem dos page_faults
    for (j = 0; j< Size; j ++) {
        for (i = 0; i< Size; i++) {
            C[j][i] = A[j][i] + B[j][i];
        }
        if (j % 3 == 0) page_faults += 3; // A cada 3 iterações, acontecem 3 page_faults
    }

    printf("page_faults: %d\n", page_faults);

    return 0;
}