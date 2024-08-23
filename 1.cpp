#include <stdio.h>     // функции с маленькой буквы
#include <math.h>      // ксонстанты капс
#include <TXLib.h>     // переменный с маленькой буквы
#include <stddef.h>    // (size_of)

struct param_solution
{
    double a, b, c;
    double x1, x2;
};

struct param_solution_expected
{
    int ntest;
    double a, b, c;
    double x1, x2;
    int nroots;
};

enum comparison {
    MORE,
    EQUALS,
    LESS
};

enum number_solutions {INF_ROOTS = 3, ZERO_ROOT = 0, ONE_ROOT = 1, TWE_ROOT = 2};
enum program_check {CRASH, OK};
enum function_check {FUNCTION_COMPLIT, FUNCTION_ERROR};

enum number_solutions   solve           (double a, double b, double c, double *x1, double *x2);
enum program_check      run_expected    (int ntest, double a, double b, double c, double x1expected, double x2expected, int nrootsexpected);
enum function_check     test            (void);
enum function_check     output          (double a, double b, double c, double *x1, double *x2);
enum comparison         comparedouble   (double x, double z);

int input_one                       (int *input);
void input_twe                      (param_solution *test1);
int input_check                     (double *v);
void check_buffer                   (int ch);
void sorting_solutiong              (double *x, double *z);

const int YOUR_DECISION     = 1;         //  ваши решения
const int FOR_NAN           = 1000;      //  NAN
const double EPSILONT       = 0.0000001; //  минимальная погрешность

int main (void)
{
    int mode_selection = 0;

    printf ("Какую проверку вы хотите осуществить?\n"
            "1 - самостоятельная решение уравнений, любое число - автоматическая проверка программы\n");

    input_one(&mode_selection);

    if (mode_selection == YOUR_DECISION)
    {
        param_solution test1 = {NAN, NAN, NAN, NAN, NAN};

        input_twe(&test1);

        output (test1.a, test1.b, test1.c, &test1.x1, &test1.x2);  //приоритет у оператора .
    }

    else
    {
        test ();
    }
}

//-------------------------------------------------------------------------------

enum function_check output (double a, double b, double c, double *x1, double *x2)
{
    int roots = solve (a, b, c, x1, x2);

    switch (roots)
    {
        case ZERO_ROOT: printf ("нет решений\n");
                break;

        case ONE_ROOT: printf ("x = %g", *x1);
                break;

        case TWE_ROOT: printf ("x1 = %g, x2 = %g", *x1, *x2);
                break;

        case INF_ROOTS: printf ("бесконечно решений");
                break;

        default:        printf ("ошибка");
                return FUNCTION_ERROR;
    }

    return FUNCTION_COMPLIT;
}

//-------------------------------------------------------------------------------

enum number_solutions solve (double a, double b, double c, double *x1, double *x2)
{
    double d = pow (b,2) - 4*a*c;

    if (comparedouble (a, 0) == EQUALS)
    {
        if (comparedouble (b, 0) == EQUALS)
        {
            return INF_ROOTS;
        }

        else   // b != 0
        {
            *x1 = -c/b;

            if (comparedouble (c, 0) == EQUALS)
            {
                *x1 = 0;
            }
            return ONE_ROOT;
        }
    }

    else    // a != 0
    {
            if (d < 0)
            {
                return ZERO_ROOT;
            }

            if (comparedouble (d, 0) == EQUALS)
            {
                *x1 = (-b + sqrt(d)) / (2*a);
                return ONE_ROOT;
            }

            else
            {
                *x1 = (-b - sqrt(d)) / (2*a);
                *x2 = (-b + sqrt(d)) / (2*a);
                return TWE_ROOT;
            }
    }
}

//------------------------------------------------------------------------------------------------------

enum program_check run_expected (int ntest, double a, double b, double c, double x1expected, double x2expected, int nrootsexpected)
{
    double x1 = NAN, x2 = NAN;

    int nroots = solve (a, b, c, &x1, &x2);

    sorting_solutiong (&x1expected, &x2expected);

    if (nrootsexpected == 2)
    {
        if (nroots != nrootsexpected || comparedouble(x1, x1expected) != EQUALS || comparedouble(x2, x2expected) != EQUALS)
        {
            printf ("Ошибка: test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
                    "Нужно: x1 = %g, x2 = %g, nroots = %d\n",
                    ntest, a, b, c, x1, x2, nroots,
                    x1expected, x2expected, nrootsexpected);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }

    if (nrootsexpected == 1)
    {
        if (nroots != nrootsexpected || comparedouble (x1, x1expected) != EQUALS)
        {
            printf ("Ошибка: test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
                    "Нужно: x1 = %g, x2 = %g, nroots = %d\n",
                    ntest, a, b, c, x1, x2, nroots,
                    x1expected, x2expected, nrootsexpected);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }

    else
    {
        if (nroots != nrootsexpected)
        {
            printf ("Ошибка: test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
                    "Нужно: x1 = %g, x2 = %g, nroots = %d\n",
                    ntest, a, b, c, x1, x2, nroots,
                    x1expected, x2expected, nrootsexpected);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }
}

//---------------------------------------------------------------------

enum function_check test (void)
{
    struct param_solution_expected test [] =   {{1, 1, 0, -4, +2, -2, 2},
                                                {2, 1, 0, 0, 0, FOR_NAN, 1},
                                                {3, 0, 2, 0, 0, FOR_NAN, 1},
                                                {4, 0, 0, 0, FOR_NAN, FOR_NAN, INF_ROOTS},
                                                {5, 2, 1, 1, FOR_NAN, FOR_NAN, ZERO_ROOT},
                                                {6, 1, 0, -4, -2, +2, 2},
                                                {7, 1, 0, -4, -2, +2, 2},
                                                {8, 1, 0, -4, -2, +2, 2},
                                                {9, 1, 0, -4, -2, +2, 2},
                                                {10, 1, 0, -4, -2, +2, 2}};
    int n = (sizeof(test) / sizeof (struct param_solution_expected));

    int i = 0, expected = 0;

    for (i = 0; i < n; i++)
    {
        expected = run_expected (test[i].ntest, test[i].a, test[i].b, test[i].c, test[i].x1, test[i].x2, test[i].nroots);
        if (expected == CRASH)
        {
            printf ("Тест провален, программа прервана.");
            break;
        }
    }
    if (expected != CRASH)
    {
        printf ("Все тесты, успешно пройдены.");
    }

    return FUNCTION_COMPLIT;
}

//----------------------------------------------------------------------

enum comparison comparedouble (double x, double z)
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

int input_one (int *input)
{
    int ch = 0;

    while (scanf ("%d", input) != 1)
    {
        while ((ch = getchar ()) != '\n');

        printf ("Неверный ввод\n"
                "Необходимо ввести число\n");
    }

    return OK;
}

//----------------------------------------------------------------------

void input_twe (param_solution *test1)
{
    printf ("ведите параметры уравнения формата (ax**2 + bx + c = 0):\n"
            "введите параметр а = ");
    input_check (&(test1 -> a));

    printf ("введите параметр в = ");
    input_check (&(test1 -> b));

    printf ("введите параметр с = ");
    input_check (&(test1 -> c));

}

//----------------------------------------------------------------------

int input_check (double *v)
{
    int ch = 0;

    while (scanf ("%lf", v) != 1)
    {
        check_buffer (ch);

        printf ("Необходимо ввести число\n"
                "параметр = ");
    }
    check_buffer (ch);

        return OK;
}

//----------------------------------------------------------------------

void check_buffer (int ch)
{
    while ((ch = getchar ()) != '\n');
}

void sorting_solutiong(double *x, double *z)
{
    double n;
    if ((*x) > (*z))
    {
        n = *x;
        *x = *z;
        *z = n;
    }
}
