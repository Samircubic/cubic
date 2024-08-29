#ifndef MAIN_H
#define MAIN_H

#define red     "\033[31m"                      ///< изменения цвета вывода на красный
#define white   "\x1b[37m"                      ///< изменения цвета вывода на белый

typedef struct param_solution                           ///< структура несущая в себе параметры и решения квадратного уравнения
{
    double a, b, c;
    double x1, x2;
    int    nroots;
} equation_parameters_t;

/*!
функция инициализирует массив структур с заданными данными и передает в тестирующую часть
*/

void    test_from_program               (void);

/*!
функция определяет квадратное/линейное уравнение и вызывает соответсвующую функцию для дальнейшего решения
*/

void    solve                           (equation_parameters_t *data);

/*!
вывод пользователю результатов вычислений\n
с несколькими режимами зависящими от верности выполнения программы и количества корней
*/

void    output                          (equation_parameters_t *data);

/*!
функция отвечает за корекктный ввод пользователем параметров для уравнения\n
check_input () дожидается от пользователя корекктного ввода использую цикл
*/

void    input_params                    (equation_parameters_t *data);

/*!
запускает цикл решения квадратных уравнений с теми параметрами которые введет пользователь\n
в конце каждого цикла пользователь выбирает решать дальше уравнения или приостановить программу\n
input_params (&data) ввод параметров с проверкой\n
solve (&data) автоматически решает уравнения при заданных параметрах\n
output (&data) вывод ответов
*/

void    re_entry                        (void);

/*!
данная функция добивается от пользователя корекктного выбора режима программы\n
функция check_buffer () используется для очистки буфера ввода\n
\param[in] input возвращает число определяющее режим программы
*/

void    input_program                   (int *input);

/*!
функция инициализирует массив структур, \n
задает параметры и верные ответы читая их из заданного файла и передает в тестирующую часть
*/

void    test_from_file                  (void);

const int MAIN_PROGRAM = 1;     ///< определение программы с ручным вводом параметров
const int FROM_PROGRAM = 1;     ///< определение программы с автоматическим вводом параметров из массива в программе

#endif      //MAIN_H
