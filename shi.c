#include "shi.h"
#include <stdio.h>

int main() {
    char *str = "Hello, World!";
    char *salt = "salt";
    uint32_t *hash_one = shi(str);
    uint32_t *hash_two = shi_salt(str, salt);

    for (int i = 0; i < 9; i++) {
        printf("%x", hash_one[i]);
    }

    printf("\n");


    for (int i = 0; i < 9; i++) {
        printf("%x", hash_two[i]);
    }

    printf("\n");

    return 0;
}
