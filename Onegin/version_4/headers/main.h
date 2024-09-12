#ifndef MAIN_H

const int number_strings = 14;
const int number_letters = 100;

//----------------------------------------------------------------------

void reed_text                              (char text[][number_letters], char* pointers_to_lines[number_strings]);
void check_buffer                           (void);
void output_text                            (char* text[number_strings]);
void sort_strings_in_ascending_order        (char* text[number_strings]);
void change_lines                           (char text[][number_letters], int line_number);
void comparing_and_replacing_strings        (char* pointers_to_lines[number_strings], int i);

#endif      //MAIN_H
