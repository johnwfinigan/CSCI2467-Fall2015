/* modified copy program to always skip first 100
 * bytes of source file. so, not a copy program 
 * anymore. */

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
	off_t currpos = lseek(sourcefile, 0, SEEK_CUR);
	if (currpos == -1) {
	    perror("lseek");
	    exit(8);
	}
	printf("current position in source file during loop: %lld\n",
	       (long long) currpos);

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
