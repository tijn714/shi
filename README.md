# Modified SHA-256 (shi) Algorithm

**Author:** Tijn Rodrigo

## Overview

This repository contains the implementation of a Modified SHA-256 (shi) algorithm in C. The SHA-256 algorithm is widely used for secure hashing and cryptographic applications. This implementation includes the core hashing function, constants, and auxiliary functions required for SHA-256.

**Note:** The modified version of SHA-256 provided in this repository is intended for educational purposes only and should not be used in real-world scenarios. It has not undergone the rigorous testing and validation required for cryptographic applications.


## Files

- **shi.h**: Header file containing function prototypes and constants for the Modified SHA-256 algorithm.
- **shi.c**: Source code file with the implementation and usage in C

## Constants

- **constants**: An array of 256 32-bit constants used in the SHA-256 algorithm.

## Functions

- **rotr**: Circular right shift operation on a 32-bit integer.
- **ch**: SHA-256 "choose" operation.
- **maj**: SHA-256 "majority" operation.
- **sigma0**: SHA-256 sigma0 operation.
- **sigma1**: SHA-256 sigma1 operation.
- **gamma0**: SHA-256 gamma0 operation.
- **gamma1**: SHA-256 gamma1 operation.

### Core Modified SHA-256 Algorithm

- **shi**: Function to compute the Modified SHA-256 hash of a given message.
  - Takes a character array (`data`) as input and returns a pointer to a 9-element array of 32-bit integers.

- **shi_salt**: Function to compute the Modified SHA-256 hash of a message combined with a salt.
  - Takes two character arrays (`data` and `salt`) as input.
  - Combines the message and salt, then computes the Modified SHA-256 hash using the `shi` function.

## Usage

1. Include the `shi.h` header file in your C program.
2. Use the `shi` function to compute the Modified SHA-256 hash of a message.
3. Optionally, use the `shi_salt` function to compute the Modified SHA-256 hash with a salt. call it using `shi_salt(message, salt)`

*Example implementation: (Also found in [shi.c](shi.c)*)

```c
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
```

## Important Notes

- This implementation is provided for educational purposes and may not be suitable for production use without thorough testing and validation.
- Ensure proper memory management, including freeing dynamically allocated memory, to avoid memory leaks.

Feel free to explore, modify, and integrate this Modified SHA-256 implementation into your projects. If you have any questions or suggestions, feel free to reach out to the author (Tijn Rodrigo).
