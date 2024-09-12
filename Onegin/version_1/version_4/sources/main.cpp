#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "../headers/main.h"

//----------------------------------------------------------------------

int main ()
{
    char text[number_strings][number_letters] = {};
    char* pointers_to_lines[number_strings] = {};

    reed_text (text, pointers_to_lines);

    sort_strings_in_ascending_order (pointers_to_lines);

    output_text (pointers_to_lines);

    return 0;
}

//----------------------------------------------------------------------

void reed_text (char text[][number_letters], char* pointers_to_lines[14])
{
    char *file_name = (char*) calloc (number_letters, sizeof (char));
    assert (file_name);

    printf ("enter the file name with parameters: ");
    scanf ("%s", file_name);

    FILE *file = NULL;
    file = fopen (file_name, "rb");
    assert (file);

    free (file_name);

    for (int i = 0; i < number_strings; i++)
    {
        fgets (text[i], number_letters, file);
        pointers_to_lines[i] = text[i];
    }

    fclose (file);
}

//----------------------------------------------------------------------

void output_text (char* pointers_to_lines[14])
{
    for (int i = 0; i < number_strings; i++)
    {
        printf ("%s", pointers_to_lines[i]);
    }
}

//----------------------------------------------------------------------

void sort_strings_in_ascending_order (char* pointers_to_lines[number_strings])
{
    for (int j = 0; j < number_strings; j++)
    {
        for (int i = 0; i < number_strings - j - 1; i++)
        {
            comparing_and_replacing_strings (pointers_to_lines, i);
        }
    }
}

//----------------------------------------------------------------------

void comparing_and_replacing_strings (char* pointers_to_lines[number_strings], int i)
{
    if (strcmp (pointers_to_lines[i], pointers_to_lines[i + 1]) > 0)
    {
        char* temporary = 0;
        temporary = pointers_to_lines[i];
        pointers_to_lines[i] = pointers_to_lines[i + 1];
        pointers_to_lines[i + 1] = temporary;
    }
}

//----------------------------------------------------------------------




// 0. код стайл, назван фун/перемен, assert
// 1. массив текста с определением длины
// 2. массив указателей
// 3. структура
// 4. компаратор
// 5. разбиение на файлы
// 6. make +++++++++++++++++++++++++++++++++++++
// 7. командная строка аргументы


