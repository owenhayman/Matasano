#include <stdio.h>
#include "../lib/hexToB64.h"

int main (int argc, char *argv[]) {
    int retVal = HexToB64Test();
    printf("Test Result: %s\n", (retVal) ? "True" : "False");
    return retVal;
}
