#include <stdio.h>


int main()
{

    char a[] = { 'x', 'y', 'z', '\0' };

    /* what if we drop the null terminator?
       char a[] = { 'x', 'y', 'z' };
     */

    char *b = "xyz";


    printf("%s %s\n", a, b + 1);



    return 0;

}
