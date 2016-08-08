int HammingDistance(char *str1, char *str2, int len)
{

    int i, score;
    char bits;
    for (i = 0; i < len; i++) {
        bits = str1[i] ^ str2[i];

        while (bits != 0)
        {
            score++;
            bits &= bits - 1;
        }
    }

    return score;
}

int GetCharIndex(char c, char* arr)
{
    char *ptr = strchr(arr, c);

    return ptr ? (int)(ptr - arr) : -1;
}

void Upper(char *str)
{
    int i;
    for (i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

int GetUniqueArray(char *result, char *charArray, int len)
{
    int i;
    char *ptr;
    int charLen = 1;
    int charCount = 0;
    for (i = 0; i < len; i++) {
        ptr = strchr(result, charArray[i]);

        if (ptr == NULL) {
            result = (char *)realloc(result, charLen++);
            result[charCount++] = charArray[i];
        }
    }

    return charCount;
}

int *GetCountArray(char *uniqueArray, char *originalArray, int len)
{
    int *countArray = (int *)calloc(len, sizeof(int));

    printf("Len: %d\n", len);
    int i;
    for (i = 0; i < len; i++)
    {
        //printf("%c, %d\n", originalArray[i], (int)(strchr(uniqueArray, originalArray[i]) - uniqueArray));
        countArray[(int)(strchr(uniqueArray, originalArray[i]) - uniqueArray)] += 1;
    }

    return countArray;
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
    dblArray = realloc(dblArray, sizeof(void *) * (currentSize + n));

    int i;
    for (i = 0; i < n; i++) {
        dblArray[(currentSize - 1) + i] = malloc(size);
    }
}

void FreeDoubleArray(void **dblArray, int currentSize)
{
    int i;
    for (i = 0; i < currentSize; i++)
    {
        free(dblArray[i]);
    }

    free(dblArray);
}

double ChiSquare(double charFreq, double expectedFreq)
{
    return pow(charFreq - expectedFreq, 2) / expectedFreq;
}

double ScoreString(char *charArray, int len)
{
    int i, count, index;
    double score = 0.0;
    double tScore;
    double expectedFreq, actualFreq;

    char *uniqueChars = malloc(0);
    int uCharCount = GetUniqueArray(uniqueChars, charArray, len);
    int *charFrequencies = GetCountArray(uniqueChars, charArray, len);
    printf("%s", "asdf");

    for (i = 0; i < uCharCount; i++)
    {
        actualFreq = (double)charFrequencies[i] / (double)len;

        index = GetCharIndex(uniqueChars[i], DistributiveFrequencyMap);

        if (index > -1 && index < 26)
            expectedFreq = DistributiveFrequency[index];
        else
            expectedFreq = 0.00001;

        score += ChiSquare(actualFreq, expectedFreq);
    }

    return score;
}

char *RepeatByte(char byte, int n)
{
    char *newString = malloc(n + 1);
    memset(newString, byte, n);
    newString[n] = '\0';

    return newString;
}
