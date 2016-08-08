#include <stdio.h>
#include "../lib/xor.h"

int FixedXORTest()
{
    // Implement test here since code change
    printf("Test Result: %s\n", retVal ? "True" : "False");
    return retVal;
}

int RepeatedXORTest()
{
    char *str = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    char *retval = (char *)malloc(RepeatedXor_len(str));

    RepeatedXor(str, retval, "ICE");

    char *hex = malloc((strlen(retval) * 2) + 1);

    HexEncode(hex, retval, strlen(retval) * 2);
    free(retval);

    printf("%s", hex);

    free(hex);
}

int main()
{
    if (FixedXorTest() && RepeatedXorTest())
        return 1;

    return 0;
}
