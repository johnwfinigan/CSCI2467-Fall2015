#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char **argv)
{

    char *d_to_open = ".";

    if (argc == 2) {
	d_to_open = argv[1];
    }
    if (argc > 2) {
	printf("please specify directory name to open\n");
	exit(1);
    }

    DIR *dstream = opendir(d_to_open);
    if (dstream == NULL) {
	perror("opening directory failed");
	exit(2);
    }

    struct dirent *d;

    /* remember! readdir returns NULL when at end of 
     *      directory OR when an error occurs */

    while (1) {

	errno = 0;
	d = readdir(dstream);
	if (d == NULL) {
	    if (errno != 0) {
		perror("readdir error");
		exit(3);
	    }
	    break;
	}

	printf("inode: %lld, name: %s\n", (long long) d->d_ino, d->d_name);
    }

    return 0;
}
