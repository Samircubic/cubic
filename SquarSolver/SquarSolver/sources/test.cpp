#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

#include "../headers/test.h"

void test (int number_of_test, testing_parameters_t *test);

//---------------------------------------------------------------------
                                                    //точность данных должна быть не меньше 5 знаком после запятой
void test_from_program (void)                       //param_solution_expected
{                                                   //ntest, {а,        в,      с,      x1,             x2          nroots}
    testing_parameters_t test_program[] =    {{1,  {1,        0,      -4,     +2,             -2,         TWO_ROOT}},
                                                        {2,  {1,        0,      0,      0,              NAN,        ONE_ROOT}},
                                                        {3,  {0,        2,      0,      0,              NAN,        ONE_ROOT}},
                                                        {4,  {0,        0,      0,      NAN,            NAN,        INF_ROOTS}},
                                                        {5,  {2,        1,      1,      NAN,            NAN,        ZERO_ROOT}},
                                                        {6,  {1e-3,     -2e-3,  1,      NAN,            NAN,        ZERO_ROOT}},
                                                        {7,  {-1e-2,    -2e-4,  3,      -17.330511,     17.310511,  TWO_ROOT}},
                                                        {8,  {-4,       -4,     -4,     NAN,            NAN,        ZERO_ROOT}},
                                                        {9,  {-1.5,     5,      5,      4.13873,        -0.805399,  TWO_ROOT}},
                                                        {10, {-10.67,   10,     15,     1.74352,        -0.806308,  TWO_ROOT}}};
    int number_of_test = (sizeof (test_program) / sizeof (testing_parameters_t));

    test (number_of_test, test_program);
}

//------------------------------------------------------------------------------------------------------

/*!
функция последовательно передает каждый тест из массива структур на исследование, \n
где одна структура выступает одним тестом
*/

void test (int number_of_test, testing_parameters_t *test)
{
    int test_execution_check = 0;

    for (int i = 0; i < number_of_test; i++)
    {
        test_execution_check = run_expected (test + i);

        if (test_execution_check == OK)
        {
            printf (green "test %d passed\n" white, i + 1);
        }
        else
        {
            /////////////CRASH////////assert ()
            break;
        }
    }
}

//------------------------------------------------------------------------------------------------------

enum program_check run_expected (testing_parameters_t *test)
{
    assert (test);

    test->parametrs = test->parametrs_expected;

    solve (&(test->parametrs));

    sorting_solutiong (&((test->parametrs_expected).x1), &((test->parametrs_expected).x2));
    sorting_solutiong (&((test->parametrs).x1), &((test->parametrs).x2));

    if (test->parametrs_expected.nroots == 2)
    {
        if (test->parametrs_expected.nroots != (test->parametrs.nroots) || compare_double (test->parametrs.x1, test->parametrs_expected.x1) != EQUALS || compare_double(test->parametrs.x2, test->parametrs_expected.x2) != EQUALS)
        {
            output_test (test);

            return CRASH;  // есть ошибка
        }
        else
        {
            return OK;  // нет ошибки
        }
    }
    else if (((test->parametrs_expected).nroots) == 1)
    {
        if (test->parametrs_expected.nroots != (test->parametrs.nroots) || compare_double (test->parametrs.x1, test->parametrs_expected.x1) != EQUALS)
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

//------------------------------------------------------------------------------------------------------

void test_from_file (void)
{
    // char buff[100];
    // fgets (buff, 100, stdin); // TODO сделать ввод имени файла и очистку буфера
    // fflush(stdin);

    // char buff[100];
    // for (int i = 0; i < 100; i++)
    // {
    //     // char ch = getchar ();
    //     buff[i] = getchar ();
    // }
//     fgets (buff, 100, stdin);
//     fflush(stdin);
//     printf("%s", buff);
//
//     for (int i = 0; i < 100; i++)
//     {
//         if (buff[i] == '\0')
//         {
//             buff[i] = 0;
//         }
//     }

    char* file_name = (char*) calloc(100, sizeof(char));

    printf ("enter the file name with parameters: ");
    scanf ("%s", file_name);

    FILE *file = NULL;
    file = fopen (file_name, "rb");

    free (file_name);

    if (!file)                                     //проверка на верно указанный файл и возврат верного указателя
    {
        printf ("error opening a file with the same name");
    }

    int number_of_test = 0;
    fscanf (file, "%d", &number_of_test);

    testing_parameters_t test_file[20] = {};

    for (int i = 0; i < number_of_test; i++)
    {
        test_file[i].ntest = i + 1;

        fscanf (file, "%lf %lf %lf %lf %lf %d", &(test_file[i].parametrs_expected.a), &(test_file[i].parametrs_expected.b),
                &(test_file[i].parametrs_expected.c), &(test_file[i].parametrs_expected.x1), &(test_file[i].parametrs_expected.x2),
                &(test_file[i].parametrs_expected.nroots));
    }

    test (number_of_test, test_file);

    fclose (file);
}

