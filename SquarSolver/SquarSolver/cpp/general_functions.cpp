#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "../square_solver.h"

//-------- все используемы функции без привязки к логической последовательности -----------

/*!
проверка числа double на равенство нулю\n
\param[in] param проверяемый параметр
*/

void check_zero (double param)
{
    if (compare_double (param, 0) == EQUALS)
    {
        param = 0;
    }
}

//-------------------------------------------------------------------------------------

/*!
на вход принимаются два числа double для сравнения, функция возвращает итог сравнения\n
\param[in] x первый сравниваемый параметр\n
\param[in] z второй сравниваемый параметр\n
\return возврат результата сравнения
*/

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

/*!
данная функция выполняет сортировку двух чисел типа double, в возрастающем порядке\n
\param[in] x первый аргумент сортировки\n
\param[in] z второй аргумент сортировки
*/

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


