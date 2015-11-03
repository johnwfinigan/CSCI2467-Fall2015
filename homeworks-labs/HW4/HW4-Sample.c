#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


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


    for (;;) {

	int ret = readdir_r(dstream, &d, &result);

	if (ret != 0) {
	    perror("readdir_r error");
	    exit(3);
	}
	if (!result) {
	    break;
	}

	struct stat mystat;	/* must declare the struct itself, not just
				   a pointer to it, so the memory gets 
				   allocated for the whole struct */
    
	if ((stat(d.d_name, &mystat) == -1)) { /* but stat wants a pointer to
                                                  the struct, so use & */
	    perror("stat");
	    exit(4);
	}

	char *dir = "";		/* variable dir points to an empty string */

	if (S_ISDIR(mystat.st_mode))  /* if it's a directory, change dir */
            dir = "(Directory)";      /* to point to the string "(Directory)" */


        /* now we can print the mode in octal using %llo, the name, and
         *  the string dir which may either be "" or "(Directory)" */
	printf("mode: %llo, name: %s %s\n", (long long) mystat.st_mode,
	       d.d_name, dir);
    }
    return 0;
}
