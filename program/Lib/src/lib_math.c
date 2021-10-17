#include "lib_math.h"

int32_t lib_math_sqrt(int32_t x)
{
    if (x == 0 || x == 1)
        return x;

    int32_t i = 1, result = 1;
    while (result <= x)
    {
        i++;
        result = i * i;
    }
    return i - 1;
}

int32_t lib_math_pow(int32_t base_i, int32_t exponent_i)
{
    int32_t base = base_i;
    int32_t exponent = exponent_i;
    int32_t num = base;

    for (int32_t x = 1; x < exponent; x++)
    {
        num *= base;
    }

    return num;
}