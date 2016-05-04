#include <stdio.h>
#include "../lib/fixedXor.h"

int main(int argc, char *argv[])
{
    int retVal = FixedXORTest();

    printf("Test Result: %s\n", retVal ? "True" : "Fa;se");
    return retVal;
}
