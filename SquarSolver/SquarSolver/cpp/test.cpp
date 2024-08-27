#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

#include "../square_solver.h"

void test (int number_of_test, struct param_solution_expected *test);

//---------------------------------------------------------------------

/*!
функция инициализирует массив структур с заданными данными и передает в тестирующую часть
*/
                                                    //точность данных должна быть не меньше 5 знаком после запятой
void test_from_program (void)                       //param_solution_expected
{                                                   //ntest, {а,        в,      с,      x1,             x2          nroots}
    struct param_solution_expected test_program[] =    {{1,  {1,        0,      -4,     +2,             -2,         TWO_ROOT}},
                                                        {2,  {1,        0,      0,      0,              NAN,        ONE_ROOT}},
                                                        {3,  {0,        2,      0,      0,              NAN,        ONE_ROOT}},
                                                        {4,  {0,        0,      0,      NAN,            NAN,        INF_ROOTS}},
                                                        {5,  {2,        1,      1,      NAN,            NAN,        ZERO_ROOT}},
                                                        {6,  {1e-3,     -2e-3,  1,      NAN,            NAN,        ZERO_ROOT}},
                                                        {7,  {-1e-2,    -2e-4,  3,      -17.330511,     17.310511,  TWO_ROOT}},
                                                        {8,  {-4,       -4,     -4,     NAN,            NAN,        ZERO_ROOT}},
                                                        {9,  {-1.5,     5,      5,      4.13873,        -0.805399,  TWO_ROOT}},
                                                        {10, {-10.67,   10,     15,     1.74352,        -0.806308,  TWO_ROOT}}};
    int number_of_test = (sizeof (test_program) / sizeof (struct param_solution_expected));

    test (number_of_test, test_program);
}

//------------------------------------------------------------------------------------------------------

/*!
функция последовательно передает каждый тест из массива структур на исследование, \n
где одна структура выступает одним тестом
*/

void test (int number_of_test, struct param_solution_expected *test)
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
    printf("assert2\n");
    }
    printf("assert3\n");
}

//------------------------------------------------------------------------------------------------------

/*!
функция исследует заданные параметры, получает от solve ответы и сравнивает их с верными,\n
после чего возвращает ошибку при несходстве и верно пройденый тест при верно высчитаных ответах соответственно
*/

enum program_check run_expected (struct param_solution_expected *test)
{
    assert (test);

    (test->parametrs) = (test->parametrs_expected);

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

/*!
функция инициализирует массив структур, \n
задает параметры и верные ответы читая их из заданного файла и передает в тестирующую часть
*/

void test_from_file (void)
{
    struct param_solution_expected test_file[] = {};

    // char buff[100];
    // fgets (buff, 100, stdin); // TODO сделать ввод имени файла и очистку буфера
    // fflush(stdin);

    FILE *file;
    file = fopen ("test.txt", "r");

    if (file == 0)                                     //проверка на верно указанный файл и возврат верного указателя
    {
        printf ("error opening a file with the same name");
    }

    int number_of_test = 0;
    fscanf (file, "%d", &number_of_test);

    for (int i = 0; i < number_of_test; i++)
    {
        test_file[i].ntest = i;

        fscanf (file, "%lf %lf %lf %lf %lf %d ", &test_file[i].parametrs_expected.a, &test_file[i].parametrs_expected.b,
                &test_file[i].parametrs_expected.c, &test_file[i].parametrs_expected.x1, &test_file[i].parametrs_expected.x2,
                &test_file[i].parametrs_expected.nroots);
    }

    test (number_of_test, test_file);
    printf("assert4\n");
    // fclose(file);
    printf("assert5\n");
    printf("assert6\n");
}
