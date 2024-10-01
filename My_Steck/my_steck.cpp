#include <stdio.h>
#include <malloc.h>
#include <assert.h>

const int initial_length = 100;
const int initial_one_steck = 1; //TODO CAPS rename, ?
const int delta_realloc = 10; //
const int step_dismissal = 2; //TODO rename

typedef double stack_elem_t;

typedef struct stack
{
    stack_elem_t* data;
    int size;
    int capacity;
} stack_t;

//----------------------------------------------------------------------

stack_t*    init        (); //TODO CTOR_STACK
int         dump        (stack_t *stk);
int         push        (stack_t *stk, double elem);
int         dectroy     (stack_t *stk); //TODO rename DTOR_STACK
int         pop         (stack_t *stk, double *elem);
int         steck_error (stack_t *stk); //TODO rename

//----------------------------------------------------------------------

int main ()
{
    stack_t *stk = init (); //TODO read about static - func and ...
    assert (stk);

    dump (stk); //TODO ifdef DUMP(stk)

    for (int i = 0; i < 100; i++)
    {
        push (stk, 1);
    }

    // steck_error (stk);

    dump (stk);

    for (int i = 0; i < 200; i++)
    {
        push (stk, 2);
    }

    dump (stk);

    for (int i = 0; i < 300; i++)
    {
        double number = 0;
        pop (stk, &number);
        printf ("%lf\n", number);
    }

    // double number = 0;
    // pop (stk, &number);
    // printf ("%lf\n", number);

    dump (stk);

    dectroy (stk);
    return 0;
}

//----------------------------------------------------------------------

int push (stack_t *stk, double elem)
{
    assert (stk);
    assert (stk->data);
    assert (stk->capacity);

    if (stk->size + 1 == stk->capacity)
    {
        int *new_capacity = (int*) calloc (1, sizeof (int*));   //TODO func realloc
        *new_capacity = stk->capacity * step_dismissal; //TODO

        stk->data = (stack_elem_t*) realloc (new_capacity, sizeof (stack_elem_t)); //FIXME
        stk->capacity = *new_capacity;
    }

    stk->data[stk->size] = elem;
    stk->size++;

    return 0;
}

//----------------------------------------------------------------------

int pop (stack_t *stk, double *elem)
{
    assert (stk);
    assert (stk->data);
    assert (stk->capacity);

    if (stk->size - delta_realloc < stk->capacity / step_dismissal)
    {
        int *new_capacity = (int*) calloc (1, sizeof (int*));
        *new_capacity = stk->capacity / step_dismissal;

        stk->data = (stack_elem_t*) realloc (new_capacity, sizeof (stack_elem_t));
        stk->capacity = *new_capacity;
    }

    *elem = stk->data[stk->size - 1];
    stk->size--;

    return 0;
}

//----------------------------------------------------------------------

stack_t* init ()
{
    stack_t *stk = (stack_t*) calloc (initial_one_steck, sizeof (stack_t)); //TODO 2 func- ctor, get_point_stack
    assert (stk);

    stk->data = (stack_elem_t*) calloc (initial_length, sizeof (stack_elem_t)); //TODO assert
    stk->size = 0;
    stk->capacity = initial_length;

    return stk;
}

//----------------------------------------------------------------------

int dectroy (stack_t *stk)
{
    assert (stk);
    assert (stk->data); //TODO NAN

    stk->size = 0;
    stk->capacity = 0; //TODO poison

    free (stk->data); //TODO NULL
    free (stk);

    return 0;
}

//----------------------------------------------------------------------

int dump (stack_t *stk) //TODO COLOR
{
    assert (stk);
    assert (stk->capacity);
    assert (stk->data);

    printf ("текущий элемент = %g\n", (stk->size == 0)? stk->data[stk->size]:stk->data[stk->size - 1]);
    printf ("номер текущего элемента = %d\n", stk->size);
    printf ("длинна стека на данный момент = %d\n", stk->capacity);

    return 0;
}

//----------------------------------------------------------------------

// int steck_error (stack_t *stk)
// {
//
// }

//----------------------------------------------------------------------



//----------------------------------------------------------------------


// 1) добавить заполнение ядовитыми значениями
// 2)
