#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{

    if (argc != 2) {
	printf("need to supply one username as argument\n");
	exit(1);
    }

    FILE *pw = fopen("/etc/passwd", "r");
    if (pw == NULL) {
	perror("fopen /etc/passwd");
	exit(2);
    }
    char *pwstring = malloc(4096);
    if (pwstring == NULL) {
	perror("malloc buffer");
	exit(3);
    }

    while (fgets(pwstring, 4096, pw)) {

        char * pwstring_copy = strdup(pwstring);
        if (pwstring_copy == NULL) {
            perror("strdup");
            exit(4);
        }
        /* we made a copy because strtok changes
         * its input */
	char *p = strtok(pwstring_copy, ":");

	if (strcmp(argv[1], p) == 0) {
	    printf("%s", pwstring);
	}
        
        free(pwstring_copy);
        pwstring_copy = NULL;
    }



    return 0;
}
