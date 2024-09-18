#ifndef MAIN_H

const int ONE_INPUT_FILE = 1;
const int TWE_OUTPUT_FILE = 2;

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

*/
void    all_reed_text                           (onegin_t *data);

/*

*/
FILE* open_file_input (onegin_t *data);

/*

*/
void measuring_file_len (onegin_t *data, FILE *file);

/*

*/
void read_and_check (onegin_t *data, FILE *file);

/*

*/
void    creating_pointers                       (onegin_t *data);

/*

*/
void measuring_the_number_of_lines (onegin_t *data);

/*

*/
void memory_allocation_and_direct_creation_of_pointers (onegin_t *data);

/*

*/
void    output_text_in_file                             (onegin_t *data);

/*

*/
FILE* open_file_output (onegin_t *data);

/*

*/
void    sort_strings_in_ascending_order         (onegin_t *data);

/*

*/
void    comparing_and_replacing_strings         (onegin_t *data, int comparable);

/*

*/
int conventional_comparator (char *line_1, char *line_2);

#endif      //MAIN_H
