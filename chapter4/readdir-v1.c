#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char **argv)
{

    if (argc != 2) {
	printf("please specify directory name to open\n");
	exit(1);
    }

    DIR *dstream = opendir(argv[1]);
    if (dstream == NULL) {
	perror("opening directory failed");
	exit(2);
    }

    struct dirent *d;

    /* remember! readdir returns NULL when at end of 
     *      directory OR when an error occurs */

    while ((d = readdir(dstream))) {

	printf("inode: %lld, name: %s\n", (long long) d->d_ino, d->d_name);
    }



    return 0;
}
