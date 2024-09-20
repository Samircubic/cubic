#ifndef MAIN_H
#define MAIN_H                                              //проверка на активацию

const int INPUT_FILE_NAME = 1;
const int OUTPUT_FILE_NAME = 2;

const char TOXIC_VALUE = 9;
char* TOXIC_POINTER = 0;

const int creating_one_strust = 1;

typedef struct onegin
{
    char *text;
    char **pointers_to_lines;
    int   number_lines;
    int   len;
    char *file_name_input;
    char *file_name_output;
} onegin_t;

//----------------------------------------------------------------------

/*
функция производит все операции связанные с вводом данных
открытие, считывание длинны, создание стека памяти для текста и передает сам текст из файла в массив
*/
void        reed_text                       (onegin_t *data);

/*

*/
onegin_t*   ctor_onegin                     ();

/*

*/
FILE*       open_file_input                 (onegin_t *data);

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
void resetting_transfers (onegin_t *onegin_data);

/*

*/
void        output_text_in_file             (onegin_t *data);

/*

*/
FILE*       open_file_output                (onegin_t *data);

/*

*/
void        sort_strings_in_ascending_order (onegin_t *data);

/*

*/
void        comparing_and_replacing_strings (onegin_t *data, int comparable);

/*

*/
int         conventional_comparator         (char *line_1, char *line_2);

/*

*/
void        freedom_of_memory               (onegin_t *data);

#endif      //MAIN_H
