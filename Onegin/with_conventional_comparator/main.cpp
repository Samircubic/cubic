#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>

#include "main.h"

//----------------------------------------------------------------------

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf ("Invalid input, check the input format");
        return 0;
    }

    onegin_t *onegin_data = ctor_onegin (); //TODO dtor

    onegin_data->file_name_input = argv[INPUT_FILE_NAME];            // извлечение имени нужного нам файла(для чтения) в структуру данных
    onegin_data->file_name_output = argv[OUTPUT_FILE_NAME];          // извлечение имени нужного нам файла(для вывода) в структуру данных
    //TODO вместо названий указатели на файл
    reed_text (onegin_data);
    assert (onegin_data->text);

    creating_pointers (onegin_data);

    sort_strings_in_ascending_order (onegin_data);

    output_text_in_file (onegin_data);

    freedom_of_memory (onegin_data);

    return 0;
}

//----------------------------------------------------------------------

onegin_t* ctor_onegin ()
{
    onegin_t *onegin_data = (onegin_t*) calloc (creating_one_strust, sizeof (onegin_t));
    assert (onegin_data);

    return onegin_data;
}

//----------------------------------------------------------------------

void reed_text (onegin_t *onegin_data) //TODO rename
{
    assert (onegin_data);

    FILE *file_input = open_file_input (onegin_data);
    assert (file_input);

    measuring_file_len (onegin_data, file_input);

    read_and_check (onegin_data, file_input);

    fclose (file_input);
}

//----------------------------------------------------------------------

FILE* open_file_input (onegin_t *onegin_data)  //TODO передавай название файла, функция универсальная!!!!
{
    assert (onegin_data);
    assert (onegin_data->file_name_input);

    FILE *file_input = fopen (onegin_data->file_name_input, "rb");
    assert (file_input);

    return file_input;
}

//----------------------------------------------------------------------

void measuring_file_len (onegin_t *onegin_data, FILE *file)
{
    assert (onegin_data);
    assert (file);

    struct stat stat_onegin = {};
    int check_fstat = fstat (fileno (file), &stat_onegin); //TODO fseek and seek - read
    assert (check_fstat != -1);

    onegin_data->len = (int) stat_onegin.st_size;
}

//----------------------------------------------------------------------

void read_and_check (onegin_t *onegin_data, FILE *file)
{
    assert (onegin_data);
    assert (file);

    onegin_data->text = (char*) calloc ((unsigned int) (onegin_data->len + 1), sizeof (char));
    assert (onegin_data->text);

    int check_len = (int) fread (onegin_data->text, sizeof (char), (size_t) onegin_data->len, file);
    onegin_data->text[onegin_data->len] = '\0';

    if (check_len != onegin_data->len)
    {
        printf ("ERROR\n mismatch between file length and elements read\n");
    }
}

//----------------------------------------------------------------------

void creating_pointers (onegin_t *onegin_data)
{
    assert (onegin_data);

    measuring_the_number_lines (onegin_data);

    creation_pointers_onegin (onegin_data);
}

//----------------------------------------------------------------------

void measuring_the_number_lines (onegin_t *onegin_data)
{
    assert (onegin_data);
    assert (onegin_data->text);

    for (int i = 0; i < onegin_data->len; i++)
    {
        if (onegin_data->text[i] == '\n')
        {
            onegin_data->number_lines += 1;
        }
    }
}

//----------------------------------------------------------------------

void creation_pointers_onegin (onegin_t *onegin_data)
{
    assert (onegin_data);
    assert (onegin_data->text);

    onegin_data->pointers_to_lines = (char**) calloc ((unsigned int) onegin_data->number_lines, sizeof (char *));
    assert (onegin_data->pointers_to_lines);

    onegin_data->pointers_to_lines[0] = &onegin_data->text[0];    //TODO (?)

    int line_number = 1;
    for (int i = 0; i < onegin_data->len - 2; i++)
    {
        if (onegin_data->text[i] == '\r')
        {
            if (onegin_data->text[i + 2] != ' ' && onegin_data->text[i + 2] != '\r' && onegin_data->text[i + 2] != '\0')
            {
                onegin_data->pointers_to_lines[line_number] = &onegin_data->text[i + 2];
                line_number++;
            }
            else
            {
                onegin_data->number_lines--;
            }
        }
    }

    resetting_transfers (onegin_data);
}

//----------------------------------------------------------------------

void resetting_transfers (onegin_t *onegin_data)                                        \\проблема с последней пустой строкой решилась через \0
{
    for (int i = 0; i < onegin_data->len; i++)
    {
        if (onegin_data->text[i] == '\r' || onegin_data->text[i] == '\n')
        {
            onegin_data->text[i] = '\0';
        }
    }
}

//----------------------------------------------------------------------

void sort_strings_in_ascending_order (onegin_t *onegin_data)
{
    assert (onegin_data);

    for (int j = 0; j < onegin_data->number_lines; j++)
    {
        for (int i = 0; i < onegin_data->number_lines - j - 1; i++)
        {
            comparing_and_replacing_strings (onegin_data, i);
        }
    }
}

//----------------------------------------------------------------------

void comparing_and_replacing_strings (onegin_t *onegin_data, int comparable)
{
    assert (onegin_data);
    assert (onegin_data->pointers_to_lines);

    if (conventional_comparator (onegin_data->pointers_to_lines[comparable], onegin_data->pointers_to_lines[comparable + 1]) > 0 )
    {
        char* temporary = 0;
        temporary = onegin_data->pointers_to_lines[comparable];
        onegin_data->pointers_to_lines[comparable] = onegin_data->pointers_to_lines[comparable + 1];
        onegin_data->pointers_to_lines[comparable + 1] = temporary; //TODO swap
    }
}

//----------------------------------------------------------------------

int conventional_comparator (char *line_1, char *line_2)
{
    assert (line_1);
    assert (line_2);

    int i_1 = 0;
    int i_2 = 0;
    while (1)
    {
        if (line_1[i_1] == ' ' || line_1[i_1] == ',' ||  line_1[i_1] == '?' || line_1[i_1] == '!' || line_1[i_1] == '.') //TODO libfunc
        {
            i_1++;
        }
        else if (line_2[i_2] == ' ' || line_2[i_2] == ',' ||  line_2[i_2] == '?' || line_2[i_2] == '!' || line_2[i_2] == '.')
        {
            i_2++;
        }
        else
        {
            if (line_1[i_1] > line_2[i_2])
            {
                return 1;
            }
            else if (line_1[i_1] < line_2[i_2])
            {
                return -1;
            }
            else if (line_1[i_1] == '\0' && line_2[i_2] == '\0')
            {
                return 0;
            }

            i_1++;
            i_2++;
        }
    }

    return 0;
}

//----------------------------------------------------------------------

void output_text_in_file (onegin_t *onegin_data)
{
    assert (onegin_data);
    assert (onegin_data->pointers_to_lines);

    FILE *file_output = open_file_output (onegin_data);
    assert (file_output);

    for (int i = 0; i < onegin_data->number_lines; i++)
    {
        fprintf (file_output ,"%s\n", onegin_data->pointers_to_lines[i]);        //TODO сделать проверку коректности вывода
    }

    fclose(file_output);
}

//----------------------------------------------------------------------

FILE* open_file_output (onegin_t *onegin_data)
{
    assert (onegin_data);
    assert (onegin_data->file_name_output);

    FILE *file_output = NULL;
    file_output = fopen (onegin_data->file_name_output, "w");
    assert (file_output);
    return file_output;
}

//----------------------------------------------------------------------

void freedom_of_memory (onegin_t *onegin_data)
{
    assert (onegin_data);
    assert (onegin_data->text);
    assert (onegin_data->pointers_to_lines);

    for (int i = 0; i < onegin_data->len; i++)
    {
        onegin_data->text[i] = TOXIC_VALUE;
    }

    for (int i = 0; i < onegin_data->number_lines; i++)
    {
        onegin_data->pointers_to_lines[i] = TOXIC_POINTER;
    }

    free (onegin_data->text);
    free (onegin_data->pointers_to_lines);
    free (onegin_data);
}

//----------------------------------------------------------------------


// запуск через make
