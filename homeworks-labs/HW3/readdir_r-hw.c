#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

/* see chapter4/readdir_r-v1.c for extra comments */

int main(int argc, char **argv)
{

    /* Always list the current directory */
    char *d_to_open = ".";

    DIR *dstream = opendir(d_to_open);
    if (dstream == NULL) {
	perror("opening directory failed");
	exit(2);
    }

    struct dirent d;
    struct dirent *result;


    for(;;) {

	int ret = readdir_r(dstream, &d, &result);

	if (ret != 0) {
	    perror("readdir_r error");
	    exit(3);
	}
	if (!result) {
	    break;
	}

	printf("inode: %lld, name: %s\n", (long long) d.d_ino, d.d_name);
    }

    return 0;
}
