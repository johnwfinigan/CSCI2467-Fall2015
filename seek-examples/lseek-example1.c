/* Demonstrates some uses of lseek.
 * modified copy program to always skip first 100
 * bytes of source file. modified to add extra
 * data to the end of the destination file.  */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{

    if (argc != 3) {
	printf("wrong number of arguments\n");
	exit(5);
    }

    int sourcefile = open(argv[1], O_RDONLY);
    if (sourcefile == -1) {
	perror("open source file failed");
	exit(1);
    }

    /* what happens if we omit O_CREAT? what about modes? */
    int destfile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
    if (destfile == -1) {
	perror("open dest file failed");
	exit(2);
    }

    ssize_t rret = 0;
    char buf[1024];

    /* seek past first 100 bytes of the source file.
     * they are skipped in the copy. */
    off_t pos = lseek(sourcefile, 100, SEEK_SET);
    if (pos == -1) {
	perror("lseek");
	exit(8);
    }
    printf("position in source file before copying begins: %lld\n",
	   (long long) pos);

    while ((rret = read(sourcefile, buf, 1024))) {
	if (rret == -1) {
	    perror("read error");
	    exit(3);
	}

	/* seeking 0 bytes away from the current position
	 * just causes lseek to return the current position */
	pos = lseek(sourcefile, 0, SEEK_CUR);
	if (pos == -1) {
	    perror("lseek");
	    exit(9);
	}
	printf("current position in source file during loop: %lld\n",
	       (long long) pos);

	ssize_t wret = 0;
	ssize_t wcount = 0;
	do {
	    wret = write(destfile, &buf[wcount], rret - wcount);
	    if (wret == -1) {
		perror("write error");
		exit(4);
	    }
	    wcount += wret;
	} while (wcount < rret);
    }

    /* move the current postion in the dest file to the end of the 
     * destfile */
    pos = lseek(destfile, 0, SEEK_END);
    if (pos == -1) {
	perror("lseek");
	exit(10);
    }
    printf("current position in dest file (end of dest file): %lld\n",
	   (long long) pos);

    /* write some extra data to end of dest file. manually calcuated length.
     * not partial-write safe. */
    int ret = write(destfile, "Some extra data\n", 16);
    if (ret == -1) {
	perror("error writing extra data to dest");
	exit(11);
    }
    /* get position in dest file after write */
    pos = lseek(destfile, 0, SEEK_CUR);
    if (pos == -1) {
	perror("lseek");
	exit(9);
    }
    printf
	("current position in dest file after writing extra data: %lld\n",
	 (long long) pos);

    /* explicit close isn't useful if you dont check its return... */
    int scret = close(sourcefile);
    if (scret == -1) {
	perror("closing source");
	exit(6);
    }
    int dcret = close(destfile);
    if (dcret == -1) {
	perror("closing copy");
	exit(7);
    }

    exit(0);
    /* zero return implies success. check it with "echo $?" */
}
