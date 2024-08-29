#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#define red     "\033[31m"                      ///< изменения цвета вывода на красный
#define blue    "\x1b[34m"                      ///< изменения цвета вывода на синий
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

enum number_solutions       ///< обозначения колва корней в уравнение
{
    INF_ROOTS = 3,
    ZERO_ROOT = 0,
    ONE_ROOT = 1,
    TWO_ROOT = 2
};

/*!
функция инициализирует массив структур с заданными данными и передает в тестирующую часть
*/

void    test_from_program               (void);

/*!
вывод пользователю результатов вычислений\n
с несколькими режимами зависящими от верности выполнения программы и количества корней
*/

void    output                          (equation_parameters_t *data);

/*!
выводит ошибку тестирования в случае вызова\n
выходными данными служит параемтры, рассчитанные ответы и верные ответы
*/

void    output_test                     (testing_parameters_t *test);

/*!
функция отвечает за корекктный ввод пользователем параметров для уравнения\n
check_input () дожидается от пользователя корекктного ввода использую цикл
*/

void    input_params                    (equation_parameters_t *data);

/*!
дожидается от пользователя корекктного ввода использую цикл
*/

void    check_input                     (double *v);

/*!
данная функция добивается от пользователя корекктного выбора режима программы\n
функция check_buffer () используется для очистки буфера ввода\n
\param[in] input возвращает число определяющее режим программы
*/

void    input_program                   (int *input);

/*!
функция используется для очистки буфера ввода
*/

void    check_buffer                    (void);

#endif      //INPUT_OUTPUT_H
