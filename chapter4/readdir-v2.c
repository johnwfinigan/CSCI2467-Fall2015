#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char **argv)
{
    /* if argc < 2, no optional command line args: default to the current directory */
    char *d_to_open = ".";

    if (argc == 2) {
	/* argv[1] has type char *, and so does d_to_open */  
	d_to_open = argv[1];
    }
    if (argc > 2) {
	printf("please specify one directory name to open\n");
	exit(1);
    }

    DIR *dstream = opendir(d_to_open);
    if (dstream == NULL) {
	perror("opening directory failed");
	exit(2);
    }

    struct dirent *d;

    /* remember! readdir returns NULL when at end of 
     *      directory OR when an error occurs. The only way
     *      to tell the difference is to see if errno has been 
     *      changed after readdir returns NULL. Fortunately,
     *      we are allowed to set errno to a known value.
     *
     *      Must set errno directly before calling readdir,
     *      and check directly after, because errno is global.
     *      Any failing system call in your code could change
     *      errno between the set and the check, unless you 
     *      put nothing but readdir between the set and the check. */

    while (1) {

	errno = 0; 
	d = readdir(dstream);
	if (d == NULL) {
	    if (errno != 0) {
		perror("readdir error");
		exit(3);
	    }
	    else {
	    	break; /* errno was not changed. end of directory */
            }
	}

	printf("inode: %lld, name: %s\n", (long long) d->d_ino, d->d_name);
    }

    return 0;
}
