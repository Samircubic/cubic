#include <stdio.h>
#include <math.h>
#include <malloc.h>

//----------------------------------------------------------------------

void reed_text              (char text[][100]);
void check_buffer           (void);
void output_text            (char text[][100]);
void sorting_strings        (char text[][100]);
void change_lines (char text[][100], int line_number);

//----------------------------------------------------------------------

int main ()
{
    char text[14][100] = {};

    reed_text (text);

    sorting_strings (text);

    output_text (text);
}

//----------------------------------------------------------------------

void reed_text (char text[][100])
{
    char *file_name = (char*) calloc (100, sizeof (char));

    printf ("enter the file name with parameters: ");
    scanf ("%s", file_name);

    FILE *file = NULL;
    file = fopen (file_name, "rb");

    free (file_name);

    for (int i = 0; i < 14; i++)
    {
        fgets (text[i], 100, file);
    }

    fclose (file);
}

//----------------------------------------------------------------------

void output_text (char text[][100])
{
    for (int i = 0; i < 14; i++)
    {
        printf ("%s", text[i]);
    }
}

//----------------------------------------------------------------------

void sorting_strings (char text[][100])
{
    int len = 13;
    for (int u = 0; u < 14; u++)
    {
        for (int i = 0; i < len; i++)
        {
            for (int o = 0; o < 100; o++)
            {
                if (text[i + 1][o] == '\0')
                {
                    break;
                }
                if (text[i][o] > text[i + 1][o])
                {
                    change_lines (text, i);
                    break;
                }
            }
        }
        len--;
    }
}

//----------------------------------------------------------------------

void change_lines (char text[][100], int line_number)
{
    for (int p = 0; p < 100; p++)
    {
        char c = 0;
        c = text[line_number][p];
        text[line_number][p] = text[line_number + 1][p];
        text[line_number + 1][p] = c;
    }
}
