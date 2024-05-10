#include "stdio.h"

int main() {
    printf("\nloop 0");
    for (int i = 0; i < 5; i++) {
        printf("\n%d", i);
    }

    printf("\nloop 1");
    for (int i = 0; i < 5; ++i) {
        printf("\n%d", i);
    }
    printf("\n");

    return 0;
}