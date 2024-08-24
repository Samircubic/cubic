#include <stdio.h>
#include <math.h>
#include <stddef.h>    // (size_of) //TODO прочитать про горячие клавиши в vscode
#include <string.h>
#include <assert.h>
#include "square_solver.h"

struct param_solution                           ///< структура несущая в себе параметры и решения квадратного уравнения
{
    double a, b, c;
    double x1, x2;
    int    nroots;
};

struct param_solution_expected
{
    int                   ntest;
    struct param_solution parametrs_expected;
    struct param_solution parametrs;
};

enum comparison
{
    MORE,
    EQUALS,
    LESS
};

enum number_solutions
{
    INF_ROOTS = 3,
    ZERO_ROOT = 0,
    ONE_ROOT = 1,
    TWO_ROOT = 2
};

enum program_check
{
    CRASH,
    OK
};

enum check_function
{
    FUNCTION_COMPLIT,
    FUNCTION_ERROR
};

void                    solve           (struct param_solution *data);
enum program_check      run_expected    (struct param_solution_expected *test);
enum check_function     test_program    (void);
void                    output          (struct param_solution *data);
enum comparison         compare_double  (double x, double z);
void output_test                        (struct param_solution_expected *test);

void    input_params                    (param_solution *data);
void    check_input                     (double *v);
void    sorting_solutiong               (double *x, double *z);
void    re_entry                        (void);
void    check_zero                      (double param);
void    program_liner                   (struct param_solution *data);
void    program_squar                   (struct param_solution *data);

const int    MAIN_PROGRAM   = 1;         //  основная программа
const int    FOR_NAN        = 1000;      //  NAN
const double EPSILONT       = 0.0000001; //  минимальная погрешность


//-------------------------------------------------------------------------------


int main (void)
{
    int mode_selection = 0;

    printf ("What kind of check do you want to perform?\n"
            red "1 " white "- independent decision, " red "Any number " white "- automatic program check\n");

    input_program (&mode_selection);

    if (mode_selection == MAIN_PROGRAM)
    {
        re_entry ();
    }

    else
    {
        test_program ();
    }
}

//--------------------------------------------------------------------------------------

void re_entry(void)  ///<вызов основной программы
{
    while (1)
    {
        param_solution data = {NAN, NAN, NAN, NAN, NAN, 0};

        input_params (&data);

        solve (&data);

        output (&data);

        printf ("Want to solve another equation\n");

        char buff[100] = "";

        fgets (buff, 100, stdin);  //////////////////////////////////////////
        check_buffer ();
        if ((strcmp (buff, "no\n")) == 0 || (strcmp (buff, "No\n")) == 0 || (strcmp (buff, "NO\n")) == 0)
        {
            break;
        }
    }
}

//----------------------------------------------------------------------

void input_params (param_solution *data)   ///<вызов программы считывающей параметры для решения уравнения
{
    printf ("Enter the parameters of the equation in the format (ax**2 + bx + c = 0):\n"
            "Enter parametr" blue " a = " white);
    check_input (&(data -> a));
    //assert ()

    printf ("Enter parametr" blue " b = " white);
    check_input (&(data -> b));
    //assert ()

    printf ("Enter parametr" blue " c = " white);
    check_input (&(data -> c));
    //assert ()

}

//----------------------------------------------------------------------

void check_input (double *param)   ///< проверка корректности ввода корней
{
    while (scanf ("%lf", param) != 1)
    {
        check_buffer ();

        printf ("\nYou must enter a number\n"
                "Parametr = ");
    }
    check_buffer ();
}

//-------------------------------------------------------------------------------

void solve (struct param_solution *data)  ///< вызов функции решающей уравнения
{
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

//-------------------------------------------------------------------------------

void output (struct param_solution *data)    ///< вывод корней для основной программы
{
    int roots = data->nroots;
    //assert ()

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
                test_program ();
    }
}

//---------------------------------------------------------------------

enum check_function test_program (void)                       //param_solution
{                                           //ntest, {а, в,  с, x1,        x2         nroots}
    struct param_solution_expected test [] =   {{1,  {1, 0, -4, +2,        -2,        TWO_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {2,  {1, 0,  0,  0,        FOR_NAN,   ONE_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {3,  {0, 2,  0,  0,        FOR_NAN,   ONE_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {4,  {0, 0,  0,  FOR_NAN,  FOR_NAN,   INF_ROOTS}, {0, 0, 0, 0, 0, 0}},
                                                {5,  {2, 1,  1,  FOR_NAN,  FOR_NAN,   ZERO_ROOT}, {0, 0, 0, 0, 0, 0}},
                                                {6,  {1, 0, -4, -2,        +2,        TWO_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {7,  {1, 0, -4, -2,        +2,        TWO_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {8,  {1, 0, -4, -2,        +2,        TWO_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {9,  {1, 0, -4, -2,        +2,        TWO_ROOT},  {0, 0, 0, 0, 0, 0}},
                                                {10, {1, 0, -4, -2,        +2,        TWO_ROOT},  {0, 0, 0, 0, 0, 0}}};
    int number_of_test = (sizeof(test) / sizeof (struct param_solution_expected));

    int test_execution_check = 0;

    for (int i = 0; i < number_of_test; i++)
    {
        test_execution_check = run_expected (test + i);

        if (test_execution_check == OK)
        {
            printf(green "test %d passed\n" white, i + 1);
        }
        else
        {
             /////////////CRASH////////assert ()
        }
    }
    return FUNCTION_COMPLIT;
}

//------------------------------------------------------------------------------------------------------

enum program_check run_expected (struct param_solution_expected *test)     //TODO rename
{
    (test->parametrs) = (test->parametrs_expected);
    solve (&(test->parametrs));

    sorting_solutiong (&((test->parametrs_expected).x1), &((test->parametrs_expected).x2));   //TODO rename

    if (test->parametrs_expected.nroots == 2)
    {
        if (test->parametrs_expected.nroots != (test->parametrs.nroots) || compare_double(test->parametrs.x1, test->parametrs_expected.x1) != EQUALS || compare_double(test->parametrs.x2, test->parametrs_expected.x2) != EQUALS)
        {
            output_test (test);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }

    if (((test->parametrs_expected).nroots) == 1)
    {
        if (test->parametrs_expected.nroots != (test->parametrs.nroots) || compare_double(test->parametrs.x1, test->parametrs_expected.x1) != EQUALS)
        {
            output_test (test);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }

    else
    {
        if (test->parametrs_expected.nroots != (test->parametrs.nroots))
        {
            output_test (test);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }
}

//----------------------------------------------------------------------

void output_test (struct param_solution_expected *test)
{
    printf (red "Test failed\n"
            blue "Error: " white "test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
            blue "Necessary:" white " x1 = %g, x2 = %g, nroots = %d\n",
            test->ntest, test->parametrs.a, test->parametrs.b, test->parametrs.c, test->parametrs.x1, test->parametrs.x2, test->parametrs.nroots,
            test->parametrs_expected.x1, test->parametrs_expected.x2, test->parametrs_expected.nroots);
}

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

void sorting_solutiong(double *x, double *z)
{
    assert (x != NULL);
    assert (z != NULL);
    double n;
    if ((*x) > (*z))
    {
         n = *x;
        *x = *z;
        *z =  n;
    }
}

//--------------------------------------------------------------------------------------


