#ifndef TEST_H
#define TEST_H

#define white   "\x1b[37m"                      ///< изменения цвета вывода на белый
#define green   "\x1b[32m"                      ///< изменения цвета вывода на зеленый

typedef struct param_solution                           ///< структура несущая в себе параметры и решения квадратного уравнения
{
    double a, b, c;
    double x1, x2;
    int    nroots;
} equation_parameters_t;

typedef struct param_solution_expected  ///<структура иcпользуемая в тестирование программы, хранит в себе номер теста, правильные параметры вывода и параметры которые расчитала функция solve
{
    int                   ntest;
    equation_parameters_t parametrs_expected;
    equation_parameters_t parametrs;
} testing_parameters_t;

enum comparison     ///< необходим для возврата итогов функции сранения двух чисел
{
    MORE,
    EQUALS,
    LESS
};

enum number_solutions       ///< обозначения колва корней в уравнение
{
    INF_ROOTS = 3,
    ZERO_ROOT = 0,
    ONE_ROOT = 1,
    TWO_ROOT = 2
};

enum program_check      ///< необходим для возврата верно\ошибка выполнения программы
{
    CRASH,
    OK
};

/*!
на вход принимаются два числа double для сравнения, функция возвращает итог сравнения\n
\param[in] x первый сравниваемый параметр\n
\param[in] z второй сравниваемый параметр\n
\return возврат результата сравнения
*/

enum comparison     compare_double      (double x, double z);

/*!
функция исследует заданные параметры, получает от solve ответы и сравнивает их с верными,\n
после чего возвращает ошибку при несходстве и верно пройденый тест при верно высчитаных ответах соответственно
*/

enum program_check  run_expected        (testing_parameters_t *test);

/*!
функция инициализирует массив структур с заданными данными и передает в тестирующую часть
*/

void                test_from_program   (void);

/*!
выводит ошибку тестирования в случае вызова\n
выходными данными служит параметры, рассчитанные ответы и верные ответы
*/

void                output_test         (testing_parameters_t *test);

/*!
данная функция выполняет сортировку двух чисел типа double, в возрастающем порядке\n
\param[in] x первый аргумент сортировки\n
\param[in] z второй аргумент сортировки
*/

void                sorting_solutiong   (double *x, double *z);

/*!
функция инициализирует массив структур, \n
задает параметры и верные ответы читая их из заданного файла и передает в тестирующую часть
*/


void                test_from_file      (void);

/*!
функция определяет квадратное/линейное уравнение и вызывает соответсвующую функцию для дальнейшего решения
*/

void                solve               (equation_parameters_t *data);

/*!
функция используется для очистки буфера ввода
*/

void            check_buffer        (void);


#endif      //TEST_H
