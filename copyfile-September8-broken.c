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
    ssize_t wret = 0;
    char buf[1024];
    int iterations = 0;

    /* broken! change 1024 below to 1025 or 8192
     * to create a buffer overflow in read */
    while ((rret = read(sourcefile, buf, 1024))) {
	if (rret == -1) {
	    perror("read error");
	    exit(3);
	}

	/* keep in mind that write is not required
	 * to write the full amount - BUG */

	/* broken! we write the whole buffer every time 
	 * change 1024 to rret to fix */
	wret = write(destfile, buf, 1024);
	if (wret == -1) {
	    perror("write error");
	    exit(4);
	}

	printf("loop iteration %d\n", iterations);
	iterations++;
    }
    /* explicit close isn't useful if you dont check its return... */
    close(sourcefile);
    close(destfile);

    exit(0);
    /* zero return implies success. check it with "echo $?" */
}
