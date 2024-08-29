#ifndef SOLVE_H
#define SOLVE_H

typedef struct param_solution                           ///< структура несущая в себе параметры и решения квадратного уравнения
{
    double a, b, c;
    double x1, x2;
    int    nroots;
} equation_parameters_t;

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

/*!
на вход принимаются два числа double для сравнения, функция возвращает итог сравнения\n
\param[in] x первый сравниваемый параметр\n
\param[in] z второй сравниваемый параметр\n
\return возврат результата сравнения
*/

enum comparison compare_double      (double x, double z);

/*!
функция определяет квадратное/линейное уравнение и вызывает соответсвующую функцию для дальнейшего решения
*/

void            solve               (equation_parameters_t *data);

/*!
данная функция выполняет сортировку двух чисел типа double, в возрастающем порядке\n
\param[in] x первый аргумент сортировки\n
\param[in] z второй аргумент сортировки
*/

void            sorting_solutiong   (double *x, double *z);

/*!
проверка числа double на равенство нулю\n
\param[in] param проверяемый параметр
*/

void            check_zero          (double param);

/*!
вызов функции происходит в том случае если уравнение оказалось линейным\n
в переданный массив вставляются рассчитагнные значения
*/

void            program_liner       (equation_parameters_t *data);

/*!
вызов функции происходит в том случае если уравнение оказалось квадратным\n
в переданный массив вставляются рассчитанные значения
*/

void            program_squar       (equation_parameters_t *data);

/*!
функция используется для очистки буфера ввода
*/

void            check_buffer        (void);

#endif      //SOLVE_H
