#include <stdint.h>

uint8_t GAdd(uint8_t u, uint8_t v)
{
    return u ^ v;
}

uint8_t GMul(uint8_t u, uint8_t v)
{
    uint8_t p = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (u & 0x01)
            p ^= v;
        int flag = (v & 0x80);
        v <<= 1;
        if (flag)
            v ^= 0x1B; // Polynomial from the description of the AES algorithm
        u >>= 1;
    }
    return p;
}

uint8_t GPow(uint8_t v, unsigned int n) 
{
    if (n == 0)
    {
        return 1;
    }
    else if (n % 2 == 0)
    {
        return GPow(GMul(v, v), n / 2);
    }
    else
    {
        uint64_t square = GMul(v, v);
        return GMul(GPow(square, n / 2), v);
    }
}
uint8_t GInv(uint8_t v)
{
    return GPow(v, 254);
}