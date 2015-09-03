#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{

    /* Work in progress version fromn 9/1 lecture. doesn't do much yet */
    
    int sourcefile = open("string.c", O_RDONLY);
    if (sourcefile == -1) {
	perror("open source file failed");
	return 1;
    }

    /* what happens if we omit O_CREAT? what about modes? */
    int destfile = open("copyofstring.c", O_WRONLY | O_CREAT | O_TRUNC);
    if (destfile == -1) {
	perror("open dest file failed");
	return 2;
    }

    





    /* explicit close isn't useful if you dont check its return... */
    close(sourcefile);
    close(destfile);

    return 0;
    /* zero return implies success. check it with "echo $?" */
}
