#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int HexDecode_len(int charLen)
{
    return charLen / 2;
}

int HexDecode (unsigned char *bytes, char *str, unsigned int bytesLen) {
    const char *pos = str;
    int count;

    if (!strlen(str) % 2)
    {
        str = strcat(str, "0");
    }

    for (count = 0; count < bytesLen; count++)
    {
        sscanf(pos, "%2hhx", &bytes[count]);
        pos += 2;
    }

    return 1;
}

int HexEncode_len(int bytesLen)
{
    return (bytesLen * 2) + 1;
}

int HexEncode (char *str, unsigned char *bytes, unsigned int bytesLen)
{
    int count;
    int byte;

    for (count = 0, byte = 0; count < bytesLen; count += 2, byte++) {
        sprintf(&str[count], "%02x", bytes[byte]);
    }

    return 1;
}
