#include <stdio.h>
#include <string.h>
#include "hexToB64.h"

#define ArraySize(x) (sizeof(x) / sizeof(x[0]))

static char const HexString1[] = "1c0111001f010100061a024b53535009181c";
static char const HexString2[] = "686974207468652062756c6c277320657965";
static char const XorResult[] = "746865206b696420646f6e277420706c6179";

struct FixedXORParams {
    unsigned char *rawBytes1;
    unsigned char *rawBytes2;
    unsigned char *xorBytes;

    unsigned int rawBytesLen;
    unsigned int bufLen;
};

int _FixedXor(struct FixedXORParams *params)
{
    int i;
    for (i = 0; i < params->rawBytesLen; i++) {
        params->xorBytes[i] = params->rawBytes1[i] ^ params->rawBytes2[i];
    }

    return 1;
}

void XORParamsInit(struct FixedXORParams *params)
{
    memset(params->rawBytes1, 0, params->rawBytesLen);
    memset(params->rawBytes2, 0, params->rawBytesLen);
    memset(params->xorBytes, 0, params->rawBytesLen);
}

void XORParamsCleanup(struct FixedXORParams *params)
{
    free(params->rawBytes1);
    free(params->rawBytes2);
    free(params->xorBytes);

    return;
}

int FixedXor(unsigned char *result, unsigned char *hexString1, unsigned char *hexString2)
{
    struct FixedXORParams xor_params;
    char *hexBytes;

    if (strlen(hexString1) != strlen(hexString2)) {
        return 0;
    }

    xor_params.bufLen = (unsigned int)strlen((char *)hexString1);
    xor_params.rawBytesLen = xor_params.bufLen / 2;

    xor_params.rawBytes1 = (unsigned char *)calloc(xor_params.rawBytesLen, sizeof(unsigned char));
    xor_params.rawBytes2 = (unsigned char *)calloc(xor_params.rawBytesLen, sizeof(unsigned char));
    xor_params.xorBytes =  (unsigned char *)calloc(xor_params.rawBytesLen, sizeof(unsigned char));

    XORParamsInit(&xor_params);

    HexDecode(xor_params.rawBytes1, (char *)HexString1, xor_params.rawBytesLen);
    HexDecode(xor_params.rawBytes2, (char *)HexString2, xor_params.rawBytesLen);

    if (!_FixedXor(&xor_params)) {
        XORParamsCleanup(&xor_params);
        return 0;
    }

    if (!HexEncode(result, xor_params.xorBytes, xor_params.bufLen)) {
        XORParamsCleanup(&xor_params);
        return 0;
    }

    XORParamsCleanup(&xor_params);

    return 1;
}

int FixedXORTest() {
    char *hexResult = (char *)calloc(strlen(HexString1) + 1, 1);
    memset(hexResult, 0, strlen(HexString1) + 1);

    if (!FixedXor(hexResult, (char *)HexString1, (char *)HexString2)) {
        return 0;
    }

    return strcmp(hexResult, XorResult) == 0;
}
