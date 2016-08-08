#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "constants.h"
#include "utils.h"
#include "xor.h"


void PrintCharacterFrequencies(char *string, int len)
{
    char *uniqueChars = malloc(0);
    int uCharCount = GetUniqueArray(uniqueChars, string, len);

    int *charFrequencies = GetCountArray(uniqueChars, string, len);

    int i;
    for (i = 0; i < uCharCount; i++)
        printf("The character: %c occurs %d times.\n", uniqueChars[i], charFrequencies[i]);
}

int GetClosestCharIndex(double f)
{

    if (f >= DistributiveFrequency[0]) {
        return 0;
    }

    double currentFreq, lastFreq;
    int i;
    for (i = 0; i < 25; i++) {
        currentFreq = DistributiveFrequency[i];

        if (f < currentFreq) {
            return ((f - lastFreq ) > (currentFreq - f)) ? currentFreq : lastFreq;
        }

        lastFreq = currentFreq;
    }
}

char *GetClosestChars(float freqPercentage)
{
    char *p = (char *)malloc(3);
    int f = GetClosestCharIndex(freqPercentage);

    memcpy(p, &(DistributiveFrequencyMap[f - (f ? 1 : 0)]), 3);
    return p;
}

char **SingleByteXorAnalysis(char *charArray, int len)
{
    char **bestXorKey = (char **)NewDoubleArray(2, len);
    double initialScore = ScoreString( charArray, len );
    double xorScore;
    char *currentXorKey;
    char *xorResult;

    int i;
    for (i = 0; i < 256; i++) {
        currentXorKey = RepeatByte(ASCII_CHARS[i], len);

        char *result = malloc(Xor_len(len));

        FixedXor(result, charArray, currentXorKey, len);
        xorScore = ScoreString(result, len);

        if ((xorScore < ScoreString( bestXorKey[1], len ) && xorScore != 0.0) || i == 0)
        {
            bestXorKey[0] = currentXorKey;
            bestXorKey[1] = xorResult;
        }
    }

    return bestXorKey;
}

char **TransposeBlocks(char **blockArray, int n, int blockSize)
{
    char **transposedBlocks = (char **)NewDoubleArray(n, blockSize);

    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < blockSize; j++)
            transposedBlocks[i][j] = blockArray[j][i];

    return transposedBlocks;
}

char **RepeatedXorAnalysis(char *charArray, int len)
{
    int upperBound = (len < 160) ? len / 4 + 1 : 41;
    printf("upperBound: %d", upperBound);
    char **blockGroup, **transposedBlocks;
    int insertIndex, keySize, ksize, i, j;
    int dist1, dist2, hdist = 9999;
    printf("Len: %d\n", len);

    for (i = 0, ksize = 2; i < upperBound; i++, ksize++)
    {
        blockGroup = (char **)NewDoubleArray(4, ksize);

        memcpy(blockGroup[0], &charArray[0], ksize);
        memcpy(blockGroup[1], &charArray[ksize], ksize);
        memcpy(blockGroup[2], &charArray[ksize * 2], ksize);
        memcpy(blockGroup[3], &charArray[ksize * 3], ksize);

        dist1 = HammingDistance(blockGroup[0], blockGroup[1], ksize) / ksize;
        dist2 = HammingDistance(blockGroup[2], blockGroup[3], ksize) / ksize;

        if ((dist1 + dist2) / 2 < hdist)
        {
            hdist = (dist1 + dist2) / 2;
            keySize = ksize;
        }

        FreeDoubleArray((void **)blockGroup, 4);
    }

    printf("Keysize is: %d", keySize);

    int transposedBlockCount = len / keySize;
    char **blockArray = (char **)NewDoubleArray(keySize, transposedBlockCount);

    for (j = 0; j < keySize; j++)
    {
        if ((keySize * j) + keySize < len)
            memcpy(blockArray[j], &charArray[keySize*j], keySize);
    }

    transposedBlocks = TransposeBlocks(blockArray, transposedBlockCount, keySize);
    FreeDoubleArray((void **)blockArray, keySize);

    printf("%s", transposedBlocks[0]);

    char **r;
    for (j = 0; j < transposedBlockCount; j++) {
        printf("Analysing block with keySize: %d\n", keySize);
        r = SingleByteXorAnalysis(transposedBlocks[j], keySize);

        printf("%c", r[0][0]);
    }

    FreeDoubleArray((void **)transposedBlocks, transposedBlockCount);
}
