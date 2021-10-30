#include <stdint.h>

uint8_t GF256_Add(uint8_t u, uint8_t v)
{
    return u ^ v;
}

uint8_t GF256_Mul(uint8_t u, uint8_t v)
{
    uint8_t p = 0;
    for (int i = 0; i < 8; i++)
    {
        if (u & 0x01)
            p ^= v;
        unsigned int flag = (v & 0x80);
        v <<= 1;
        if (flag)
            v ^= 0x1B; // Polynomial from the description of the AES algorithm
        u >>= 1;
    }
    return p;
}

uint8_t GF256_Pow(uint8_t v, unsigned int n) 
{
    if (n == 0)
    {
        return 1;
    }
    else if (n % 2 == 0)
    {
        return GF256_Pow(GF256_Mul(v, v), n / 2);
    }
    else
    {
        uint8_t square = GF256_Mul(v, v);
        return GF256_Mul(GF256_Pow(square, n / 2), v);
    }
}
uint8_t GF256_Inv(uint8_t v)
{
    return GF256_Pow(v, 254);
}