#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t uint32;

#define FULL_MASK(n) (uint32) (1<<((n) + 1)) - 1
#define PHI ((tmpN & 1) == 0x1 && \
             (tmpL & 1) == 0x0 && \
             (tmpU & 1) == 0x1)

uint32 find_mask(uint32 N, uint32 L, uint32 U)
{
    uint32 tmpN = N;
    uint32 tmpL = L;
    uint32 tmpU = U;
    uint32 shift = 0;
    uint32 sol = U;

    while(shift < 32)
    {
        do
        {
            tmpN >>= 1;
            tmpL >>= 1;
            tmpU >>= 1;
            ++shift;
        }
        while(!PHI && shift < 32);

        if (PHI)
        {
            sol &= ~FULL_MASK(shift -1);  
            sol |= FULL_MASK(shift - 1);
            printf("%u\n", sol);
        }
    }

    tmpN = N;
    tmpL = L;
    tmpU = sol;
    for(shift = 0; shift < 32; ++shift)
    {
        if ((tmpN & 1) == 1 && (sol & 1) == 1 && (tmpL & 1) == 0)
        {
            sol &= ~(1 << shift);
        }
        tmpN >>= 1;
        tmpU >>= 1;
        tmpL >>= 1;
    }

    return sol;
}


int main(int  argc, char *argv[])
{
    uint32 N, L, U;
    if (argc != 4) return 1;

    N = (uint32) atol(argv[1]);
    L = (uint32) atol(argv[2]);
    U = (uint32) atol(argv[3]);

    printf("%u\n",find_mask(N,L,U));
}
