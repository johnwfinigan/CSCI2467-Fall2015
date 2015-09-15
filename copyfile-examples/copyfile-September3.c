#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{

    int sourcefile = open("string.c", O_RDONLY);
    if (sourcefile == -1) {
	perror("open source file failed");
	return 1;
    }

    /* what happens if we omit O_CREAT? what about modes? */
    int destfile = open("copyofstring.c", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (destfile == -1) {
	perror("open dest file failed");
	return 2;
    }

    /* first version will only copy first 100 bytes of source */
    ssize_t rret = 0;
    ssize_t wret = 0;
    char buf[100];

    rret = read(sourcefile, buf, 100);
    if (rret == -1) {
	perror("read error");
	return 3;
    }

    wret = write(destfile, buf, rret);
    if (wret == -1) {
	perror("write error");
	return 4;
    }

    /* explicit close isn't useful if you dont check its return... */
    close(sourcefile);
    close(destfile);

    return 0;
    /* zero return implies success. check it with "echo $?" */
}
