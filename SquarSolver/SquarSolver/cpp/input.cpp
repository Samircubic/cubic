#include <stdio.h>
#include <assert.h>

#include "../square_solver.h"

//----------------------------------------------------------------------

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

void input_params (param_solution *data)   ///<вызов программы считывающей параметры для решения уравнения
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
