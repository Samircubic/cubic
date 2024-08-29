#include <stdio.h>
#include <assert.h>

#include "../hhh/input_output.h"

//---------------input-------------------------------------------------------

void input_program (int *input)  ///< проверка корректности ввода выбора программы
{
    assert (input);

    int ch = 0;
    while (scanf ("%d", input) != 1 || (ch = getchar ()) != '\n' || ch == EOF)
    {
        check_buffer ();

        printf (red "Invalid input\n" white
                "Enter an integer\n");
    }
}

//----------------------------------------------------------------------

void check_buffer (void)
{
    int ch = 0;
    while ((ch = getchar ()) != '\n');
}

//----------------------------------------------------------------------

void input_params (equation_parameters_t *data)   ///<вызов программы считывающей параметры для решения уравнения
{
    assert (data);

    printf ("Enter the parameters of the equation in the format (ax**2 + bx + c = 0):\n"
            "Enter parametr" blue " a = " white);
    check_input (&(data -> a));
    assert (&(data -> a));

    printf ("Enter parametr" blue " b = " white);
    check_input (&(data -> b));
    assert (&(data -> b));

    printf ("Enter parametr" blue " c = " white);
    check_input (&(data -> c));
    assert (&(data -> c));
}

//----------------------------------------------------------------------

void check_input (double *param)   ///< проверка корректности ввода корней
{
    assert(param);

    int ch = 0;
    while (scanf ("%lf", param) != 1 || (ch = getchar ()) != '\n' || ch == EOF)
    {
        check_buffer ();
        printf ("\nYou must enter a number\n"
                "Parametr = ");
    }
}

//--------------output----------------------------output-------------------------------------

void output (equation_parameters_t *data)    ///< вывод корней для основной программы
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

void output_test (testing_parameters_t *test)
{
    assert (test);
    printf (red "Test failed\n"
            blue "Error: " white "test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
            blue "Necessary:" white " x1 = %g, x2 = %g, nroots = %d\n",
            test->ntest, test->parametrs.a, test->parametrs.b, test->parametrs.c, test->parametrs.x1, test->parametrs.x2, test->parametrs.nroots,
            test->parametrs_expected.x1, test->parametrs_expected.x2, test->parametrs_expected.nroots);
}
