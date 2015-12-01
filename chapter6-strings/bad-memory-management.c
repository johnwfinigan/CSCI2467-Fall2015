#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *doit()
{
    int i = 2;			//stack allocated
    return &i;			//BUG! i goes out of scope
}


int main()
{
    //Compiler warnings will not catch all of these runtime errors.
    //The program will crash unexpectedly, or appear to work,
    //until it doesn't.
    //May return bogus values or enable a security exploit.



    int *f = doit();
    int j = 3;
    //*f is a stack allocated object that is now out of scope.
    printf("%d %d\n", *f, j);

    //heap allocate 20 byte buffer
    char * buf = malloc(20);
    //set the first 19 bytes to the ascii byte 'a'
    memset(buf, 'a', 19);
    //add a null terminator to make it a string
    buf[19] = '\0';

    //free the buffer
    free(buf);

    //use it anyway!  BUG!!!!
    printf("%s\n", buf);

    //free it twice (Dangerous BUG!)
    //free does not clear the address stored
    //in the pointer buf, so free will be passed
    //a valid address to an invalid object
    free(buf); 

    //How to mitigate both free errors:
    //set buf to NULL directly after freeing it.
    //free(NULL) is defined to do nothing.
    //the use-after-free will crash the program still,
    //but at least in a predictable manner.
    //like so:
    //
    //free(buf);
    //buf = NULL;

    return 0;
}
