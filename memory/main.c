#include "stdio.h"
#include "stdint.h"
#include "memory.h"

int main() {
    printf("hola amigos");

    uint32_t a, b;

    printf("%d -> %d\n", a, b);
    b = 0xaabbccdd;
    copy(&a, &b, sizeof(b));
    printf("%d -> %d\n", a, b);

    uint8_t c[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint8_t d[sizeof(c)];
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", c[i]); }
    printf("\n");
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", d[i]); }
    printf("\n");

    copy(d, c, sizeof(c));
    printf("\n");

    for (int i = 0; i < sizeof(c); i++) { printf("%d ", c[i]); }
    printf("\n");
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", d[i]); }
    printf("\n");

    return 0;
}