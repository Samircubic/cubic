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

    onegin_t data = {0, 0, 0, 0, 0, 0};

    data.file_name_input = argv[ONE_INPUT_FILE];            // извлечение имени нужного нам файла(для чтения) в структуру данных
    data.file_name_output = argv[TWE_OUTPUT_FILE];          // извлечение имени нужного нам файла(для вывода) в структуру данных

    all_reed_text (&data);
    assert (data.text);

    creating_pointers (&data);

    sort_strings_in_ascending_order (&data);

    output_text_in_file (&data);

    return 0;
}

//----------------------------------------------------------------------

void all_reed_text (onegin_t *data)
{
    assert (data);

    FILE *file_input = open_file_input (data);
    assert (file_input);

    measuring_file_len (data, file_input);

    read_and_check (data, file_input);

    fclose (file_input);
}

//----------------------------------------------------------------------

FILE* open_file_input (onegin_t *data)
{
    assert (data);

    FILE *file_input = NULL;
    file_input = fopen (data->file_name_input, "rb");
    assert (file_input);
    return file_input;
}

//----------------------------------------------------------------------

void measuring_file_len (onegin_t *data, FILE *file)
{
    assert (data);
    assert (file);

    struct stat st = {};
    int check_fstat = fstat (fileno (file), &st);
    assert (check_fstat != -1);
    data->len = (int) st.st_size;
}

//----------------------------------------------------------------------

void read_and_check (onegin_t *data, FILE *file)
{
    assert (data);
    assert (file);

    data->text = (char*) calloc (data->len + 1, sizeof (char));

    int check_len = (int) fread (data->text, sizeof (char), data->len, file);
    data->text[data->len] = '\0';

    if (check_len != data->len)
    {
        printf ("ERROR\n mismatch between file length and elements read\n");
    }
}

//----------------------------------------------------------------------

void creating_pointers (onegin_t *data)
{
    assert (data);

    measuring_the_number_of_lines (data);

    memory_allocation_and_direct_creation_of_pointers (data);
}

//----------------------------------------------------------------------

void measuring_the_number_of_lines (onegin_t *data)
{
    assert (data);

    for (int i = 0; i < data->len; i++)
    {
        if (data->text[i] == '\r')
        {
            data->number_lines += 1;
        }
    }
}

//----------------------------------------------------------------------

void memory_allocation_and_direct_creation_of_pointers (onegin_t *data)
{
    assert (data);

    data->pointers_to_lines = (char**) calloc (data->number_lines, sizeof (long int));

    data->pointers_to_lines[0] = &data->text[0];

    int line_number = 1;
    for (int i = 0; i < data->len - 2; i++)
    {
        if (data->text[i] == '\r')
        {
            data->text[i] = '\0';
            data->text[i + 1] = '\0';
            if (data->text[i + 2] != ' ' && data->text[i + 2] != '\r' && data->text[i + 2] != '\0')
            {
                data->pointers_to_lines[line_number] = &data->text[i + 2];
                line_number++;
            }
            else
            {
                data->number_lines--;
            }
        }
    }
}

//----------------------------------------------------------------------

void sort_strings_in_ascending_order (onegin_t *data)
{
    assert (data);

    for (int j = 0; j < data->number_lines; j++)
    {
        for (int i = 0; i < data->number_lines - j - 1; i++)
        {
            comparing_and_replacing_strings (data, i);
        }
    }
}

//----------------------------------------------------------------------

void comparing_and_replacing_strings (onegin_t *data, int comparable)
{
    assert (data);

    if (strcmp (data->pointers_to_lines[comparable], data->pointers_to_lines[comparable + 1]) > 0 )
    {
        char* temporary = 0;
        temporary = data->pointers_to_lines[comparable];
        data->pointers_to_lines[comparable] = data->pointers_to_lines[comparable + 1];
        data->pointers_to_lines[comparable + 1] = temporary;
    }
}

//----------------------------------------------------------------------

int conventional_comparator (char *line_1, char *line_2)
{
    assert (line_1);
    assert (line_2);

    return 0;
}

//----------------------------------------------------------------------

void output_text_in_file (onegin_t *data)
{
    assert (data);

    FILE *file_output = open_file_output (data);
    assert (file_output);

    for (int i = 0; i < data->number_lines; i++)
    {
        printf ("%s\n", data->pointers_to_lines[i]);
    }

    fclose(file_output);
}

//----------------------------------------------------------------------

FILE* open_file_output (onegin_t *data)
{
    assert (data);

    FILE *file_output = NULL;
    file_output = fopen (data->file_name_output, "w");
    assert (file_output);
    return file_output;
}

//----------------------------------------------------------------------

