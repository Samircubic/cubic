#include <stdio.h>     // функции с маленькой буквы
#include <math.h>      // ксонстанты капс
//#include <TXLib.h>     // переменный с маленькой буквы
#include <stddef.h>    // (size_of)
#include <string.h>

#define red     "\033[31m"
#define blue    "\x1b[34m"
#define white   "\x1b[37m"
#define green   "\x1b[32m"

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
    TWE_ROOT = 2
};

enum program_check
{
    CRASH,
    OK
};

enum function_check
{
    FUNCTION_COMPLIT,
    FUNCTION_ERROR
};

enum number_solutions   solve           (struct param_solution *test1);
enum program_check      run_expected    (struct param_solution_expected test);
enum function_check     test            (void);
enum function_check     output          (struct param_solution *test1);      //TODO rename
enum comparison         comparedouble   (double x, double z);

int     input_one                      (int *input);
void    input_twe                      (param_solution *test1);
int     check_input                    (double *v);
void    check_buffer                   ();
void    sorting_solutiong              (double *x, double *z);
void     re_entry                       (void);

const int    YOUR_DECISION  = 1;         //  ваши решения
const int    FOR_NAN        = 1000;      //  NAN
const double EPSILONT       = 0.0000001; //  минимальная погрешность

int main (void)
{
    int mode_selection = 0;

    printf ("What kind of check do you want to perform?\n"
            red "1 " white "- independent decision, " red "Any number " white "- automatic program check\n");

    input_one (&mode_selection);

    if (mode_selection == YOUR_DECISION)   //TODO rename основная прога
    {
        re_entry ();
    }

    else
    {
        test ();
    }
}

//-------------------------------------------------------------------------------

enum function_check output (struct param_solution *test1)//TODO rename
{
    int roots = solve (test1);      //TODO rename

    switch (roots)
    {
        case ZERO_ROOT: printf ("No solutions\n");
                break;

        case ONE_ROOT: printf ("x = %g\n", test1->x1);
                break;

        case TWE_ROOT: printf ("x1 = %g, x2 = %g\n", test1->x1, test1->x2);
                break;

        case INF_ROOTS: printf ("Any number\n");
                break;

        default:        printf (red "Error\n     " white);
                return FUNCTION_ERROR;
    }

    return FUNCTION_COMPLIT;
}

//-------------------------------------------------------------------------------

enum number_solutions solve (struct param_solution *test1)
{
    double d = pow (test1->b,2) - 4*(test1->a)*(test1->c);         //TODO rename

    if (comparedouble (test1->a, 0) == EQUALS)       //TODO rename
    {
        if (comparedouble (test1->b, 0) == EQUALS)
        {
            return INF_ROOTS;
        }

        else   // b != 0
        {
            (test1->x1) = -test1->c/test1->b;

            if (comparedouble (test1->c, 0) == EQUALS)
            {
                (test1->x1) = 0;
            }
            return ONE_ROOT;
        }
    }

    else    // a != 0
    {
            if (comparedouble (d, 0) == LESS)
            {
                return ZERO_ROOT;
            }

            if (comparedouble (d, 0) == EQUALS)
            {
                (test1->x1) = (-test1->b + sqrt(d)) / (2*test1->a);
                return ONE_ROOT;
            }

            else
            {
                (test1->x1) = (-test1->b - sqrt(d)) / (2*test1->a);         //TODO check is -0   example: -1 2 0
                (test1->x2) = (-test1->b + sqrt(d)) / (2*test1->a);
                return TWE_ROOT;
            }
    }
}

//------------------------------------------------------------------------------------------------------

enum program_check run_expected (struct param_solution_expected *test)     //TODO rename
{
    struct param_solution test_expected = {test->a, test->b, test->c, test->x1, test->x2};     //TODO param_solution_expected->param_solution

    int nroots = solve (&test_expected);

    sorting_solutiong (&(test->x1), &(test->x2));   //TODO rename

    if ((test->nroots) == 2)
    {
        if (nroots != (test->nroots) || comparedouble(test->x1, test_expected.x1) != EQUALS || comparedouble(test->x2, test_expected.x2) != EQUALS)
        {
            printf (red "Error: " white "test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
                    "Necessary: x1 = %g, x2 = %g, nroots = %d\n",
                    test->ntest, test_expected.a, test_expected.b, test_expected.c, test_expected.x1, test_expected.x2, nroots,
                    test->x1, test->x2, test->nroots);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }

    if ((test->nroots) == 1)
    {
        if (nroots != (test->nroots) || comparedouble(test->x1, test_expected.x1) != EQUALS)
        {
            printf (red "Error: " white "test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
                    "Necessary: x1 = %g, x2 = %g, nroots = %d\n",
                    test->ntest, test_expected.a, test_expected.b, test_expected.c, test_expected.x1, test_expected.x2, nroots,
                    test->x1, test->x2, test->nroots);
            return CRASH;  // есть ошибка
        }

        else
        {
            return OK;  // нет ошибки
        }
    }

    else
    {
        if (nroots != (test->nroots))
        {
            printf (red "Error: " white "test %d, a = %g, b = %g, c = %g, x1 = %g, x2 = %g, nroots = %d\n"
                    "Necessary: x1 = %g, x2 = %g, nroots = %d\n",
                    test->ntest, test_expected.a, test_expected.b, test_expected.c, test_expected.x1, test_expected.x2, nroots,
                    test->x1, test->x2, test->nroots);
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
                                                {10, 1, 0, -4, -2, +2, 2}};   //TODO выравнивание
    int n = (sizeof(test) / sizeof (struct param_solution_expected));          //TODO

    int i = 0, expected = 0;

    for (i = 0; i < n; i++)
    {
        expected = run_expected (test + i);//(test + i)
        //*(test + 2) не байты  test[i] == &*(test + i)
        if (expected == CRASH)
        {
            printf (red "Test failed, program aborted." white);     //TODO all - test
            break;
        }
    }
    if (expected != CRASH)
    {
        printf (green "All tests passed successfully." white);
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
        while ((ch = getchar ()) != '\n'); //TODO func check_buf

        printf (red "Invalid input\n"
                "You must enter a number\n");
    }

    return OK;
}

//----------------------------------------------------------------------

void input_twe (param_solution *test1)
{
    printf ("Enter the parameters of the equation in the format (ax**2 + bx + c = 0):\n"
            "Enter parametr" blue " a = " white);
    check_input (&(test1 -> a));

    printf ("Enter parametr" blue " b = " white);            //TODO assert
    check_input (&(test1 -> b));

    printf ("Enter parametr" blue " c = " white);
    check_input (&(test1 -> c));

}

//----------------------------------------------------------------------

int check_input (double *param)  //TODO rename
{
    int ch = 0;

    while (scanf ("%lf", param) != 1)
    {
        check_buffer (ch);

        printf ("You must enter a number\n"
                "Parametr = ");
    }
    check_buffer ();

        return OK;       //TODO void
}

//----------------------------------------------------------------------

void check_buffer ()
{
    int ch = 0;
    while ((ch = getchar ()) != '\n');
}

void sorting_solutiong(double *x, double *z)
{
    double n;     //TODO    assert
    if ((*x) > (*z))
    {
         n = *x;
        *x = *z;
        *z =  n;
    }
}

void re_entry(void)
{
    while (1)
    {
        param_solution test1 = {NAN, NAN, NAN, NAN, NAN};       //TODO rename

        input_twe (&test1);   //TODO rename

        output (&test1);      //TODO 2 func solve and output

        printf ("Want to solve another equation\n");

        char buff[100] = "";

        fgets (buff, 100, stdin);       //TODO flesh buf stdin

        if ((strcmp (buff, "no\n")) == 0 || (strcmp (buff, "No\n")) == 0 || (strcmp (buff, "NO\n")) == 0)
        {
            break;
        }
    }
}
