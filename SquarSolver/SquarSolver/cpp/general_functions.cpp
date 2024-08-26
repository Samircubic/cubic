#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../square_solver.h"

//-------- все используемы функции без привязки к логической последовательности -----------

void check_zero (double param)
{
    if (compare_double (param, 0) == EQUALS)
    {
        param = 0;
    }
}

//-------------------------------------------------------------------------------------

enum comparison compare_double (double x, double z)
{
    if (fabs (x - z) < EPSILONT)
    {
        return EQUALS;
    }

    if ((x - z) > EPSILONT)
    {
        return MORE;
    }

    else
    {
        return LESS;
    }
}

//----------------------------------------------------------------------

void sorting_solutiong (double *x, double *z)
{
    assert (x);
    assert (z);
    double n;
    if ((*x) > (*z))
    {
         n = *x;
        *x = *z;
        *z =  n;
    }
}

//--------------------------------------------------------------------------------------


