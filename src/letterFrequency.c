#include <stdio.h>
#include "../lib/definitions.h"
#include "../lib/hexToB64.h"
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char DistributiveFrequencyMap[] = {
    'E', 'T', 'A', 'O', 'I', 'N',
    'S', 'H', 'R', 'D', 'L', 'C',
    'U', 'M', 'W', 'F', 'G', 'Y',
    'P', 'B', 'V', 'K', 'J', 'X',
    'Q', 'Z', '\0'
};

float DistributiveFrequency[] = {
    0.12702, 0.09095, 0.08167, 0.07507,
    0.06966, 0.06749, 0.06327, 0.06094,
    0.05987, 0.04254, 0.04025, 0.02782,
    0.02758, 0.02406, 0.02361, 0.02228,
    0.02015, 0.01974, 0.01929, 0.01492,
    0.00978, 0.00772, 0.00153, 0.00150,
    0.00095, 0.00074
};

char FirstLetterFrequencyMap[] = {
    'T', 'A', 'S', 'H', 'W', 'I',
    'O', 'B', 'M', 'F', 'C', 'L',
    'D', 'P', 'N', 'G', 'E', 'R',
    'Y', 'U', 'V', 'J', 'K', 'Q',
    'Z', 'X', '\0'
};

float FirstLetterFrequency[] = {
    0.16671, 0.11602, 0.07755, 0.07232,
    0.06753, 0.06286, 0.06264, 0.04702,
    0.04383, 0.03779, 0.03551, 0.02705,
    0.02670, 0.02545, 0.02365, 0.02007,
    0.01950, 0.01653, 0.01620, 0.01487,
    0.00649, 0.00597, 0.00590, 0.00173,
    0.00034, 0.00017
};

int GetCharIndex(char c, char* arr)
{
    char *ptr = strchr(arr, c);

    return ptr ? (int)(ptr - arr) : -1;
}

void upper(char *str)
{
    int i;
    for (i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

char *GetUniqueArray(char *charArray) {
    char *uniqueChars = malloc(1);
    memset(uniqueChars, 0, 1);

    int i;
    char *ptr;
    int charLen = 2;
    for (i = 0; i < strlen(charArray); i++) {
        ptr = strchr(uniqueChars, charArray[i]);

        if (ptr == NULL) {
            uniqueChars[strlen(uniqueChars)] = charArray[i];
            uniqueChars = (char *)realloc(uniqueChars, charLen++);
            uniqueChars[charLen - 2] = '\0';
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
        printf("The character: %c occurs %d times.\n", uniqueChars[i], charFrequencies[i]);
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

void **NewDoubleArray(int n, int size)
{
    void **ptrArray = (void **)calloc(n, sizeof(void *));

    int i;
    for (i = 0; i < n; i++) {
        ptrArray[i] = malloc(size);
    }

    return ptrArray;
}

void ExpandDoubleArray(void **dblArray, int currentSize, int n, int size)
{
    int i;
    for (i = 0; i < n; i++) {
        realloc(dblArray, sizeof(void *) * (currentSize + n));
        dblArray[(currentSize - 1) + i] = malloc(size);
    }
}

double ChiSquare(double charCount, double expectedCount)
{
    return pow(charCount - expectedCount, 2) / expectedCount;
}

double ScoreString(char *uniqueChars, int *charCounts)
{

    int i, count, index;
    double score = 0.0;
    double freq;
    for (i = 0; i < strlen(uniqueChars); i++)
    {
        count = charCounts[i];
        index = GetCharIndex(uniqueChars[i], DistributiveFrequencyMap);

        //printf("First '%c' Index: %d\n", uniqueChars[i], index);

        if (index > -1 && index < 26)
            freq = DistributiveFrequency[index];
        else
            //freq = -100;
            freq = 0.00001;

        score += ChiSquare(count, freq);
    }

    return score;
}

void CheckKeyScores(char **bestXorKeys, char *currentXorKey)
{
    int i;
    for (i = 0; i < 3; i++)
        // Blah blah
        bestXorKeys[i] = currentXorKey;
}

void SingleByteXORBrute(char *charArray, char **returnArray)
{
    char **bestXorKeys = NewDoubleArray(3, strlen(charArray));
    char *currentXorKey;

    int i;
    for (i = 0; i < 256; i++) {
        currentXorKey = RepeatByte(ASCII_CHARS[i], strlen(charArray));

        CheckKeyScores(char **bestXorKeys, currentXorKey);
    }
}

char **AnalyseFrequency(char *charArray)
{
    char *uniqueChars = GetUniqueArray(charArray);
    int *charFrequencies = GetCountArray(uniqueChars, charArray);
    char **returnArray = NewDoubleArray(1, strlen(charArray));

    double initialScore = ScoreString( charArray, charFrequencies );

    

    return returnArray;
}

int main(int argc, char *argv[])
{
    char *c = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    char r[strlen(c) / 2 + 1];

    HexDecode(r, c, strlen(c) / 2 + 1);
    upper(r);

    PrintCharacterFrequencies(r);
    AnalyseFrequency(r);

    //printf("%s\n%s\n%s", retval[0], retval[1], retval[2]);

    return 1;
}
