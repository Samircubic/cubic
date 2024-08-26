#ifndef SQUARE_SOLVER_H
#define SQUARE_SOLVER_H

#define red     "\033[31m"                      ///< изменения цвета на красный
#define blue    "\x1b[34m"                      ///< изменения цвета на синий
#define white   "\x1b[37m"                      ///< изменения цвета на белый
#define green   "\x1b[32m"                      ///< изменения цвета на зеленый

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


enum comparison         compare_double  (double x, double z);
enum program_check      run_expected    (struct param_solution_expected *test);
void     test_from_program    (void);

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
void    test_from_file                       (void);

const int    MAIN_PROGRAM   = 1;         //  основная программа
const int    FOR_NAN        = 1000;      //  NAN
const double EPSILONT       = 0.0000001; //  минимальная погрешность
const int FROM_PROGRAM      = 1;         // берет параметры из программы

#endif      //SQUARE_SOLVER_H
