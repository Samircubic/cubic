#include <stdio.h>
#include <assert.h>

#include "../square_solver.h"

//----------------------------------------------------------------------

/*!
данная функция добивается от пользователя корекктного выбора режима программы
функция check_buffer () используется для очистки буфера ввода
\param[in] input возвращает число определяющее режим программы
*/

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

/*!
функция используется для очистки буфера ввода
*/

void check_buffer (void)
{
    int ch = 0;
    while ((ch = getchar ()) != '\n');
}

//----------------------------------------------------------------------

/*!
функция отвечает за корекктный ввод пользователем параметров для уравнения
check_input () дожидается от пользователя корекктного ввода использую цикл
*/

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

/*!
check_input () дожидается от пользователя корекктного ввода использую цикл
*/


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
