#include "stdio.h"
#include "stdint.h"
#include "memory.h"

int main() {
    printf("hola amigos");

    uint32_t a, b;


    b = 24;
    printf("\n%u -> %u\n", b, a);
    copy(&a, &b, sizeof(b));
    printf("%u -> %u\n", b, a);

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

    printf("\nheap start\n");

    uint8_t * aLocation = allocate(sizeof(c));
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", *(aLocation + i)); }
    printf("\n");

    copy(aLocation, c, 4);
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", *(aLocation + i)); }
    printf("\n");

    uint8_t * bLocation = allocate(sizeof(c));
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", *(bLocation + i)); }
    printf("\n");

    copy(bLocation, &c[5], 4);
    for (int i = 0; i < sizeof(c); i++) { printf("%d ", *(bLocation + i)); }
    printf("\n");

    deallocate(bLocation);

    return 1;
}