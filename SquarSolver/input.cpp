#include <stdio.h>
#include "square_solver.h"

//----------------------------------------------------------------------

void input_program (int *input)  ///< проверка корректности ввода выбора программы
{
    while (scanf ("%d", input) != 1)
    {
        check_buffer ();

        printf (red "Invalid input\n" white
                "You must enter a number\n");
    }
}

//----------------------------------------------------------------------

void check_buffer (void)
{
    int ch = 0;
    while ((ch = getchar ()) != '\n');
}
