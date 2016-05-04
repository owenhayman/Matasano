#include <stdio.h>
#include "../lib/hexToB64.h"

char DistributiveFrequencyMap[] = {
    'E', 'T', 'A', 'O', 'I', 'N',
    'S', 'H', 'R', 'D', 'L', 'C',
    'U', 'M', 'W', 'F', 'G', 'Y',
    'P', 'B', 'V', 'K', 'J', 'X',
    'Q', 'Z'
};

float DistributiveFrequency[] = {
    12.702, 9.095, 8.167, 7.507,
     6.966, 6.749, 6.327, 6.094,
     5.987, 4.254, 4.025, 2.782,
     2.758, 2.406, 2.361, 2.228,
     2.015, 1.974, 1.929, 1.492,
     0.978, 0.772, 0.153, 0.150,
     0.095, 0.074
};

char FirstLetterFrequencyMap[] = {
    'T', 'A', 'S', 'H', 'W', 'I',
    'O', 'B', 'M', 'F', 'C', 'L',
    'D', 'P', 'N', 'G', 'E', 'R',
    'Y', 'U', 'V', 'J', 'K', 'Q',
    'Z', 'X'
};

float FirstLetterFrequency[] = {
    16.671, 11.602, 7.755, 7.232,
     6.753,  6.286, 6.264, 4.702,
     4.383,  3.779, 3.551, 2.705,
     2.670,  2.545, 2.365, 2.007,
     1.950,  1.653, 1.620, 1.487,
     0.649,  0.597, 0.590, 0.173,
     0.034,  0.017
};

char *GetUniqueArray(char *charArray) {
    char *uniqueChars = malloc(1);
    memset(uniqueChars, 0, 1);

    int charLen = 2;

    int i;
    for (i = 0; i < strlen(charArray); i++) {
        char *p = strchr(uniqueChars, charArray[i]);

        if (p == NULL) {
            uniqueChars[strlen(uniqueChars)] = charArray[i];
            uniqueChars = (char *)realloc(uniqueChars, charLen++);
            uniqueChars[charLen - 2] = '\0';
            continue;
        }
    }

    return uniqueChars;
}

int *GetCountArray(char *uniqueArray, char *originalArray)
{
    int *countArray = (int *)calloc(strlen(uniqueArray), sizeof(int));

    int i;
    for (i = 0; i < strlen(originalArray); i++)
        countArray[(int)(strchr(uniqueArray, originalArray[i]) - uniqueArray)] += 1;

    return countArray;
}

void PrintCharacterFrequencies(char *string)
{
    char *uniqueChars = GetUniqueArray(string);
    int *charFrequencies = GetCountArray(uniqueChars, string);

    int i;
    for (i = 0; i < strlen(uniqueChars); i++)
        printf("The character: 0x%x occurs %d times.\n", uniqueChars[i], charFrequencies[i]);
}

int GetClosestCharIndex(float f)
{

    if (f >= DistributiveFrequency[0]) {
        return 0;
    }

    float currentFreq, lastFreq;
    int i;
    for (i = 0; i < 25; i++) {
        currentFreq = DistributiveFrequency[i];

        if (f < currentFreq) {
            return ((currentFreq))
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

/*char ***/ void AnalyseFrequency(char *charArray)
{
    char *uniqueChars = GetUniqueArray(charArray);
    int *charFrequencies = GetCountArray(uniqueChars, charArray);

    float frequencyPercentage;
    char **stringPermutations;
    char *closestChars, c;

    int i, f;
    for (i = 0; i < strlen(uniqueChars); i++) {
        c = uniqueChars[i];
        f = charFrequencies[i];

        frequencyPercentage = ((float)f / (float)strlen(charArray)) * 100;
        //printf("Character: 0x%x\nAverage: %.2f\n", c, frequencyAverage);

        closestChars = GetClosestChars(frequencyPercentage);

    }

}

int main(int argc, char *argv[])
{
    char *c = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    char r[strlen(c) / 2 + 1];

    HexDecode(r, c, strlen(c) / 2 + 1);
    //PrintCharacterFrequencies(c);
    AnalyseFrequency(r);
}
