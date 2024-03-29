//
//  Author:  Tijn Rodrigo (tijn714)
//  date:    13-02-2024 
// 
//  @file: shi.h
//  @brief: This file contains the implementation of a Modified SHA-256 named shi algorithm.
//
//////////////////////////////

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

const uint32_t constants[256] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t rotr(uint32_t x, int n) {
    return (x >> n) | (x << (32 - n));
}

uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t sigma0(uint32_t x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

uint32_t sigma1(uint32_t x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

uint32_t gamma0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

uint32_t gamma1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

uint32_t* shi(char *data) {
    uint32_t sg = 0x564c4748;
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xdd67fe85;
    uint32_t h2 = 0x386ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b056c8c;
    uint32_t h6 = 0x1c23d9ab;
    uint32_t h7 = 0x5eb07d19;
    
    int len = strlen(data); 
    int bit_len = len * 8;
    int new_len = len + 1;
    
    while (new_len % 64 != 56) {
        new_len++;
    }
    
    char *padded_data = (char *)malloc(new_len + 8);
    memcpy(padded_data, data, len);
    padded_data[len] = 0x80;
    
    for (int i = len + 1; i < new_len; i++) {
        padded_data[i] = 0x00;
    }
    
    for (int i = 0; i < 8; i++) {
        padded_data[new_len + i] = (bit_len >> (8 * (7 - i))) & 0xFF;
    }
    
    uint32_t *words = (uint32_t *)padded_data;
    
    for (int i = 0; i < new_len / 4; i += 16) {
        uint32_t w[64];
        
        for (int j = 0; j < 16; j++) {
            w[j] = words[i + j];
        }
        
        for (int j = 16; j < 64; j++) {
            w[j] = gamma1(w[j - 2]) + w[j - 7] + gamma0(w[j - 15]) + w[j - 16];
        }
        
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        for (int j = 0; j < 64; j++) {
            uint32_t t1 = h + sigma1(e) + ch(e, f, g) + constants[j] + w[j];
            uint32_t t2 = sigma0(a) + maj(a, b, c);
            
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    uint32_t temp = sg;
    sg = h0;
    h0 = h1;
    h1 = h2;
    h2 = h3;
    h3 = h4;
    h4 = h5;
    h5 = h6;
    h6 = h7;
    h7 = temp;

    uint32_t* result = (uint32_t*)malloc(9 * sizeof(uint32_t));
    sg = gamma0(sg) + gamma1(h0) + ch(h0, h1, h2) + constants[0] + sg;
    h0 = gamma0(h0) + gamma1(h1) + ch(h1, h2, h3) + constants[1] + h0;
    h1 = gamma0(h1) + gamma1(h2) + ch(h2, h3, h4) + constants[2] + h1;
    h2 = gamma0(h2) + gamma1(h3) + ch(h3, h4, h5) + constants[3] + h2;
    h3 = gamma0(h3) + gamma1(h4) + ch(h4, h5, h6) + constants[4] + h3;
    h4 = gamma0(h4) + gamma1(h5) + ch(h5, h6, h7) + constants[5] + h4;
    h5 = gamma0(h5) + gamma1(h6) + ch(h6, h7, sg) + constants[6] + h5;
    h6 = gamma0(h6) + gamma1(h7) + ch(h7, sg, h0) + constants[7] + h6;
    h7 = gamma0(h7) + gamma1(sg) + ch(sg, h0, h1) + constants[8] + h7;


    result[0] = sg;
    result[1] = h0;
    result[2] = h1;
    result[3] = h2;
    result[4] = h3;
    result[5] = h4;
    result[6] = h5;
    result[7] = h6;
    result[8] = h7;

    
    
    return result;
}

uint32_t* shi_salt(const char *data, const char *salt) {
    char *salted_data = (char *)malloc(strlen(data) + strlen(salt) + 32);
    strcpy(salted_data, data);
    strcat(salted_data, salt);
    return shi(salted_data);
}


uint32_t* shi_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(len + 1);
    fread(data, 1, len, file);
    data[len] = 0;
    return shi(data);
}