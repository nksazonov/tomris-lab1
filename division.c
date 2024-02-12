#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "division.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>

int division(const char *x, const char *y, const int base, int *rest)
{
    const int n = strlen(x);
    const int t = strlen(y);
    const int resultSize = n - t + 1;                        // +1 for extra carry, +1 for null-terminator
    char *result = (char *)calloc(resultSize, sizeof(char)); // Initialize with zeros

    if (!result)
        return NULL; // Allocation check

    for (int i = 0; i < resultSize - 2; i++)
    {
        result[i] = '0';
    }

    result[resultSize - 1] = 0;
    while (x > y * pow(base, n - t))
    {
        result[n - t] = val2Ch(result[n - t] + 1);
        x = x - y * pow(base, n - t);
    }

    for (int i = n; i >= t + 1; i--)
    {
        if (ch2val(x[i]) == ch2val(y[i]))
        {
            result[i - t - 1] = val2Ch(base - 1);
        }
        else
        {
            result[i - t - 1] = val2Ch(floor((x[i] * base + x[i - 1]) / y[t]));
        }

        while (result[i - t - 1] * (y[t] * base + y[t - 1]) > x[i] * base * base + x[i - 1] * base + x[i - 2])
        {
            result[i - t - 1] = val2Ch(result[i - t - 1] - 1);
        }

        x = add(x, result[i - t - 1] * y * pow(base, i - t - 1));
        if (x < 0)
        {
            x = x + y * pow(base, i - t - 1);
            result[i - t - 1] = val2Ch(result[i - t - 1] - 1);
        }
    }

    // Remove leading zeros from the result
    int start = 0;
    while (start < resultSize - 2 && result[start] == '0')
    {
        start++;
    }

    char *finalResult = strdup(result + start);

    free(result);

    return finalResult;
}
