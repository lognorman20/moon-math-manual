/*
 * Note
 * --------------
 *
 * This is a **SAMPLE** code, not designed for any kind of production use.
 * The focus is on the algorithm itself, not on making a generic, read-to-use, implementation.
 * Again, this is a proof-of-concept code.
 *
 * Vladislav K. Valtchev, 2021
 */

#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int divide(int n, int d)
{
    int r = 0;
    int q = 0;
    int sign = 1;
    bool n_is_min = false;

    // Division by zero
    assert(d != 0);

    if (d == 1)
        return n;

    if (d == INT_MIN)
        return n == INT_MIN ? 1 : 0;

    if (n == INT_MIN) {

        // (INT_MIN / -1) == -INT_MIN
        // and that is not representable in 'int'
        // We treat it like a division by zero.
        
        assert(d != -1);
        
        n_is_min = true;
        n++; // we'll handle that later.
    }

    if (n > 0 != d > 0)
        sign = -1;

    n = abs(n);
    d = abs(d);

    for (int i = 31; i >= 0; i--) {

        r <<= 1;           // left shift r by 1
        r |= (n >> i) & 1; // set bit r(0) = n(i)

        if (r >= d) {
            
            // 'r', made by the first 'i' digits of 'n',
            // is finally bigger than 'd'. Now subtract the divisor
            // from it and set the i-th bit in the quotient to 1.
            r -= d;
            q |= 1 << i;
        }
    }

    // handle the special case where n == INT_MIN
    if (n_is_min && r == d-1) {
        
        // The dividend was originally INT_MIN, but we made it be INT_MIN+1
        // in order to convert it to a positive value.
        //
        // Now the reminder is exactly equal to 'd-1', which means that,
        // if 'n' was just larger by 1, it would have been 0, which is exactly
        // our case here.
        
        r = 0; // reset the reminder, optional in this context
        q++;   // increase the quotient by one
    }

    return q * sign;
}
