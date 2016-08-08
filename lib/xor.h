#include <stdio.h>
#include <string.h>

int Xor_len(int len)
{
    return len + 1;
}

void RepeatedXor(char *result, char *plaintext, char *key)
{
    int keyLen = strlen(key);

    int i, j;
    for (i = 0, j = 0; i < strlen(plaintext); i++, j = i % keyLen)
        result[i] = plaintext[i] ^ key[j];

    result[strlen(plaintext)] = '\0';
}

void FixedXor(char *result, char* arr1, char* arr2, int len)
{
    int i;
    for (i = 0; i < len; i++)
        result[i] = arr1[i] ^ arr2[i];
}
