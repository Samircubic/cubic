#ifndef MAIN_H
#define MAIN_H                      //проверка на активацию

const int INPUT_FILE_NAME = 1;      //номер имени файла для ввода в argv
const int OUTPUT_FILE_NAME = 2;     //номер имени файла для вывода в argv

const char TOXIC_VALUE = 9;         //ядовитая переменная
char* TOXIC_POINTER = 0;            //ядовитый указатель

const int creating_one_strust = 1;  //создание одной структуры в одном элементе массива

typedef struct pointers_start_end
{
    char *pointers_to_lines_start;
    char *pointers_to_lines_end;
} pointers_start_end_t;

typedef struct onegin
{
    char *text;
    pointers_start_end_t *pointers_to_lines;
    int   number_lines;
    int   len;
    FILE *file_input;
    FILE *file_output;
} onegin_t;

//----------------------------------------------------------------------

/*
функция производит все операции связанные с вводом данных
открытие, считывание длинны, создание стека памяти для текста и передает сам текст из файла в массив
*/
void        reed_text                       (onegin_t *data, char *file_name_input);

/*

*/
onegin_t*   ctor_onegin                     ();

/*

*/
FILE*       open_file_input                 (onegin_t *data, char *file_name_input);

/*

*/
void        measuring_file_len              (onegin_t *data, FILE *file);

/*

*/
void        read_and_check                  (onegin_t *data, FILE *file);

/*

*/
void        creating_pointers               (onegin_t *data);

/*

*/
void        measuring_the_number_lines      (onegin_t *data);

/*

*/
void        creation_pointers_onegin        (onegin_t *data);

/*

*/
void        resetting_transfers             (onegin_t *onegin_data);

/*

*/
void        output_text_in_file             (onegin_t *data, char *file_name_output);

/*

*/
FILE*       open_file_output                (onegin_t *data, char *file_name_output);

/*

*/
void        sort_strings_in_ascending_order (onegin_t *data);

/*

*/
void        comparing_and_replacing_strings (onegin_t *data, int comparable);

/*

*/
void        swap_pointers                   (onegin_t *onegin_data, int comparable);

/*

*/
int         conventional_comparator         (char *line_1, char *line_2);

/*

*/
void        freedom_of_memory               (onegin_t *data);

#endif      //MAIN_H
