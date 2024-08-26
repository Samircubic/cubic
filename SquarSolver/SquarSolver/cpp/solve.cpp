#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "../square_solver.h"

//-------------------------------------------------------------------------------

void solve (struct param_solution *data)  ///< вызов функции решающей уравнения
{
    assert (data);

    if (compare_double (data->a, 0) == EQUALS)
    {
        program_liner (data);
    }

    else    // a != 0
    {
        program_squar (data);
    }
}

//-------------------------------------------------------------------------------

void program_liner (struct param_solution *data)      //линейные
{
    assert (data);
    if (compare_double (data->b, 0) == EQUALS)
    {
        (data->nroots) = INF_ROOTS;
    }

    else   // b != 0
    {
        (data->x1) = -data->c/data->b;

        if (compare_double (data->c, 0) == EQUALS)
        {
            (data->x1) = 0;
        }
        (data->nroots) = ONE_ROOT;
    }
}

//-------------------------------------------------------------------------------

void program_squar (struct param_solution *data)       //квадратные
{
    assert (data);

    double discriminant = pow (data->b,2) - 4*(data->a)*(data->c);

    if (compare_double (discriminant, 0) == LESS)
    {
        (data->nroots) = ZERO_ROOT;
    }

    else if (compare_double (discriminant, 0) == EQUALS)
    {
        (data->x1) = (-data->b + sqrt(discriminant)) / (2*data->a);
        check_zero (data->x1);
        (data->nroots) = ONE_ROOT;
    }
    else
    {
        (data->x1) = (-data->b - sqrt(discriminant)) / (2*data->a);
        check_zero (data->x1);

        (data->x2) = (-data->b + sqrt(discriminant)) / (2*data->a);
        check_zero (data->x1);
        (data->nroots) = TWO_ROOT;
    }
}
