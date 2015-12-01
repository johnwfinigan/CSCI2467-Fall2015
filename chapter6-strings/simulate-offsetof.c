#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

    //offsetof operator tells you how many bytes away
    //from the starting address of a struct a member is.

    size_t offs = offsetof(struct stat, st_size);
    printf("st_size is %zu bytes from the beginning of our stat stuct\n",
	   offs);


    //We can simulate offsetof
    //Source - C a Reference Manual 4th ed
    //Authors Harbison, Steele ISBN 0133262243

    ptrdiff_t diff;
    struct stat s;
    //note: we need to know what member is first!
    //that is, which is at offset 0 in the struct
    //for stat, that is st_dev (see man 2 stat)
    diff = (void *)&s.st_size - (void *)&s.st_dev;
    printf("by another method, offset is %tu\n", diff);

    return 0;

}
