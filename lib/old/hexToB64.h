#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "./hex.h"

static char const HexString[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static char const B64String[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

static char const B64CharArray[] = {

    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'

};

int ShiftCharCode(int index, uint8_t charCode)
{
    if (index == 0) {
        return (charCode >> 2);
    }
    else if (index == 1) {
        return charCode >> 4 ;
    }
    else if (index == 2) {
        return charCode >> 6;
    }
    else if (index == 3) {
        return charCode;
    }
}

uint8_t GetRemainder(int index, uint8_t charCode)
{
    if (index == 0) {
        return (charCode & 0x03) << 4;
    }
    else if (index == 1) {
        return (charCode & 0x0F) << 2;
    }
    else if (index == 2) {
        return charCode & 0x3F;
    }
}

uint8_t GetB64Index(int index, uint8_t rawCharCode, uint8_t remainder)
{
    return ShiftCharCode(index, rawCharCode) | remainder;
}

int CheckForEnd(int remainder, uint8_t byte)
{
    return !(remainder + byte);
}

int B64Encode (char *buf, char *bytes)
{
    uint8_t b64IndexCode;
    uint8_t baseCounter;
    uint8_t rawCharCode;
    uint8_t remainder;
    uint8_t charCode;
    uint8_t i, j, counter;

    int bufLen = GetB64BufSize(strlen(bytes)) - 1;

    for (i = 0, counter = 0; i < bufLen; i += 3, counter++) {
        baseCounter = counter * 4;
        remainder = 0x00;

        if (CheckForEnd(remainder, bytes[i])) return 1;

        buf[baseCounter] = B64CharArray[GetB64Index(0, bytes[i], remainder)];
        remainder = GetRemainder(0, bytes[i]);
        if (CheckForEnd(remainder, bytes[i])) return 1;

        if (i + 1 < bufLen - 1) {
            buf[baseCounter + 1] = B64CharArray[GetB64Index(1, bytes[i + 1], remainder)];
            remainder = GetRemainder(1, bytes[i + 1]);
            if (CheckForEnd(remainder, bytes[i + 1])) return 1;

            if (i + 2 < bufLen - 1) {
                buf[baseCounter + 2] = B64CharArray[GetB64Index(2, bytes[i + 2], remainder)];
                remainder = GetRemainder(2, bytes[i + 2]);
                if (CheckForEnd(remainder, bytes[i + 2])) return 1;

                buf[baseCounter + 3] = B64CharArray[bytes[i + 2] & 0x3f];
            }
            else {
                buf[baseCounter + 3] = B64CharArray[remainder];
                buf[baseCounter + 4] = '=';
            }
        }
        else {
            buf[baseCounter + 1] = B64CharArray[remainder];
            buf[baseCounter + 2] = '=';
            buf[baseCounter + 3] = '=';
        }
    }

    return 1;
}

int HexToB64(char* hex, char* b64) {
    int rawBufSize = (strlen(hex) % 2) ? strlen(hex) + 1 : strlen(hex) / 2;

    unsigned char *rawBuf;
    rawBuf = (unsigned char *)calloc(rawBufSize, sizeof(unsigned char));

    if (!HexDecode(rawBuf, (char *)hex, rawBufSize))
    {
        free(rawBuf);
        return 0;
    }

    if (!B64Encode(b64, rawBuf)) {
        free(rawBuf);
        return 0;
    }

    free(rawBuf);
    return 1;
}

int HexToB64Test()
{
    char b64String[65];
    memset(b64String, 0, 66);

    if (!HexToB64((char *)HexString, b64String)) {
        return 0;
    }

    return strcmp((char *)B64String, b64String) == 0;
}
