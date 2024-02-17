#include "shi2.h"
#include <stdio.h>

int main(){
    char *data = "Hello, World!";
    printf("%s\n", data);

    uint64_t result[9];
    shi2(data, result);

    for (int i = 0; i < 9; i++){
        printf("%02llx", result[i]);
    }

    printf("\n");
    return 0;
}
