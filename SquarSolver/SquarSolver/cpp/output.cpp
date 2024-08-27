#include <stdio.h>
#include <assert.h>

#include "../square_solver.h"

//-------------------------------------------------------------------------------

/*!
вывод пользователю результатов вычислений\n
с несколькими режимами зависящими от верности выполнения программы и количества корней
*/

void output (struct param_solution *data)    ///< вывод корней для основной программы
{
    int roots = data->nroots;
    assert (data);

    switch (roots)
    {
        case ZERO_ROOT: printf ("No solutions\n");
                break;

        case ONE_ROOT: printf ("x = %g\n", data->x1);
                break;

        case TWO_ROOT: printf ("x1 = %g, x2 = %g\n", data->x1, data->x2);
                break;

        case INF_ROOTS: printf ("Any number\n");
                break;

        default:        printf (red "Error\n" white
                                "Running a program test\n");
                test_from_program ();
    }
}

//----------------------------------------------------------------------

/*!
выводит ошибку тестирования в случае вызова\n
выходными данными служит параемтры, рассчитанные ответы и верные ответы
*/

void output_test (struct param_solution_expected *test)
{
    assert (test);
    printf (red "Test failed\n"
            blue "Error: " white "test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
            blue "Necessary:" white " x1 = %g, x2 = %g, nroots = %d\n",
            test->ntest, test->parametrs.a, test->parametrs.b, test->parametrs.c, test->parametrs.x1, test->parametrs.x2, test->parametrs.nroots,
            test->parametrs_expected.x1, test->parametrs_expected.x2, test->parametrs_expected.nroots);
}
