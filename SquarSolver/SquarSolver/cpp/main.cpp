#include <stdio.h>
#include <string.h>                 //TODO typedef
#include <assert.h>
#include <math.h>

#include "../square_solver.h"

//typedef void handles_structure (struct); TODO

//-------------------------------------------------------------------------------

int main (void)
{
    int mode_selection = 0;

    printf ("What kind of check do you want to perform?\n"
            red "1 " white "- independent decision, " red "Any number " white "- automatic program check\n");

    input_program (&mode_selection);

    if (mode_selection == MAIN_PROGRAM)
    {
        re_entry ();
    }

    else
    {
        printf ("From where the parameters of the equation will be inserted?\n"
                red "1 " white "- from program, " red "Any number " white "- from file\n");

        input_program (&mode_selection);

        if (mode_selection == FROM_PROGRAM)
        {
            test_from_program ();
        }
        else                                     // из файла
        {
            test_from_file ();
        }
    }
}

//--------------------------------------------------------------------------------------

void re_entry (void)  ///<вызов основной программы
{
    while (1)
    {
        param_solution data = {NAN, NAN, NAN, NAN, NAN, 0};

        input_params (&data);

        solve (&data);

        output (&data);

        printf ("Want to solve another equation\n");

        char buff[100] = "";

        fgets (buff, 100, stdin); // TODO
        fflush(stdin);

        if ((strcmp (buff, "no\n")) == 0 || (strcmp (buff, "No\n")) == 0 || (strcmp (buff, "NO\n")) == 0)
        {
            break;
        }
    }
}
