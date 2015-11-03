#include <stdio.h>
#include <stdlib.h>



int main() {

    FILE * pw = fopen("/etc/passwd", "r");
    if (pw == NULL) {
        perror("fopen /etc/passwd");
        exit(1);
    }
    char * pwstring = malloc(4096);
    if (pwstring == NULL) {
        perror("malloc buffer");
        exit(1);
    }

    while(fgets(pwstring, 4096, pw)) {
        printf("%s", pwstring);

    }



    return 0;
}
