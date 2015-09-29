/* given the name of a file,
 * prints the file's size */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    struct stat mystat;
    /* what if testfile doesnt exist? */
    int ret = stat("testfile", &mystat);
    if (ret == -1) {
	perror("stat");
	exit(1);
    }

    printf("size is %lld\n", (long long) mystat.st_size);

    return 0;
}
