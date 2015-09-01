#include <stdio.h>


int main()
{
    /* declare a three element array */
    int a[3];

    /* initialize all three elements 
    *  rvalue is a char literal, gets
    *  converted to int by promotion */
    a[0] = 'x';
    a[1] = 'y';
    a[2] = 'z';

    /* print as ints, using array indexing */    
    printf("hello world %d %d\n", a[0], a[1]);
    /* print as ints, using pointers */
    printf("hello world %d %d\n", *a, *(a + 1));


    return 0;

}
