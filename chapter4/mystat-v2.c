/* given the name of a file,
 * prints the file's size */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    if(argc != 2) {
        printf("wrong number of arguments");
        exit(2);
    }

    struct stat mystat;
    struct stat * statptr = &mystat;

    int ret = stat(argv[1], statptr);
    if (ret == -1) {
	perror("stat");
	exit(1);
    }

    printf("size is %lld\n", (long long) statptr->st_size);

    return 0;
}
