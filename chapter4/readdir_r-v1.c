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

    struct dirent d;   /* manpage states that readdir_r's entry
                          buffer must be "caller-allocated". That's you!
                          In other words, you have to declare an object
                          that is big enough to hold a dirent struct's 
                          worth of data. Just declaring the struct is
                          an easy way to do it. */
    struct dirent *result;


    for(;;) { /* for(;;) is a common infinite loop idiom */

	int ret = readdir_r(dstream, &d, &result);
        /* note that unlike readdir, readdir_r returns 0 for 
        *  success and non-zero for error. The error and end
        *  of directory states do NOT have the same return value */

	if (ret != 0) {
	    perror("readdir_r error");
	    exit(3);
	}
	if (!result) { /* readdir_r stores NULL in result upon end of 
                        * directory. NULL is false, so !NULL is true.
                        * Personally I prefer to write (result == NULL),
                        * but this is common and it's up to you. */
	    break;
	}

	printf("inode: %lld, name: %s\n", (long long) d.d_ino, d.d_name);
    }

    return 0;
}
