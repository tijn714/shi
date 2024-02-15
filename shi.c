#include "shi.h"
#include <stdio.h>

int main() {
    char *str = "Hello, World!";
    char *salt = "salt";
    uint32_t *hash_one = shi(str);
    uint32_t *hash_two = shi_salt(str, salt);


    printf("Hash one (Hello, World): \n");
    for (int i = 0; i < 9; i++) {
        printf("%x", hash_one[i]);
    }

    printf("\n");


    printf("Hash two (Hello, World, salt): \n");
    for (int i = 0; i < 9; i++) {
        printf("%x", hash_two[i]);
    }

    printf("\n");


    printf("Hash three (README.md): \n");
    FILE *f = fopen("README.md", "r");
    uint32_t *hash_three = shi_file(f);

    for (int i = 0; i < 9; i++) {
        printf("%x", hash_three[i]);
    }

    printf("\n");

    printf("Hash four (README.md, salt): \n");
    FILE *f2 = fopen("README.md", "r");
    uint32_t *hash_four = shi_file_salt(f2, salt);

    for (int i = 0; i < 9; i++) {
        printf("%x", hash_four[i]);
    }

    printf("\n");


    return 0;
}
