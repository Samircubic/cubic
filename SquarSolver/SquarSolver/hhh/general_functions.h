#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

enum comparison     ///< необходим для возврата итогов функции сранения двух чисел
{
    MORE,
    EQUALS,
    LESS
};

/*!
проверка числа double на равенство нулю\n
\param[in] param проверяемый параметр
*/

void            check_zero          (double param);

/*!
на вход принимаются два числа double для сравнения, функция возвращает итог сравнения\n
\param[in] x первый сравниваемый параметр\n
\param[in] z второй сравниваемый параметр\n
\return возврат результата сравнения
*/

enum comparison compare_double      (double x, double z);

/*!
данная функция выполняет сортировку двух чисел типа double, в возрастающем порядке\n
\param[in] x первый аргумент сортировки\n
\param[in] z второй аргумент сортировки
*/

void            sorting_solutiong   (double *x, double *z);

const double EPSILONT = 0.00001;   ///< минимальная погрешность

#endif      //GENERAL_FUNCTIONS_H
