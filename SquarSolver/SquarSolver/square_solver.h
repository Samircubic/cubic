#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

#define red     "\033[31m"                      ///< изменения цвета вывода на красный
#define blue    "\x1b[34m"                      ///< изменения цвета вывода на синий
#define white   "\x1b[37m"                      ///< изменения цвета вывода на белый
#define green   "\x1b[32m"                      ///< изменения цвета вывода на зеленый

struct param_solution                           ///< структура несущая в себе параметры и решения квадратного уравнения
{
    double a, b, c;
    double x1, x2;
    int    nroots;
};

/*!
структура импользуемая в тестирование программы, хранит в себе номер теста, правильные параметры вывода
и параметры которые расчитала функция solve
*/

struct param_solution_expected
{
    int                   ntest;
    struct param_solution parametrs_expected;
    struct param_solution parametrs;
};

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

enum comparison         compare_double  (double x, double z);
enum program_check      run_expected    (struct param_solution_expected *test);
void    test_from_program               (void);
void    solve                           (struct param_solution *data);
void    output                          (struct param_solution *data);
void    output_test                     (struct param_solution_expected *test);
void    input_params                    (param_solution *data);
void    check_input                     (double *v);
void    sorting_solutiong               (double *x, double *z);
void    re_entry                        (void);
void    check_zero                      (double param);
void    program_liner                   (struct param_solution *data);
void    program_squar                   (struct param_solution *data);
void    input_program                   (int *input);
void    check_buffer                    (void);
void    test_from_file    (void);

const int       MAIN_PROGRAM   = 1;         ///< основная программа
const double    EPSILONT       = 0.00001; ///< минимальная погрешность
const int       FROM_PROGRAM   = 1;         ///< определяет режим исполнения теста, где заданые параметры берутся из программы

#endif      //SQUARE_SOLVER_H
