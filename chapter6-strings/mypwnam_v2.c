/* getpwnam work-alike demo code. if you need this info in a real application,
 * use getpwnam */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

/* struct password definition:
 
           struct passwd {
               char   *pw_name;
               char   *pw_passwd;    
               uid_t   pw_uid;      
               gid_t   pw_gid;     
               char   *pw_gecos;  
               char   *pw_dir;   
               char   *pw_shell;
           };
*/

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
    /* we're going to fill in some fields in this struct passwd with 
     * the data we find in the password file, just to show how it's done.
     * in real life, you would use getpwnam() for this, not write it by hand */
    struct passwd mypasswd;

    while (fgets(pwstring, 4096, pw)) {

        /* WARNING - this code doesn't handle malformed input, that is
         * malformed lines in the passwd file. */

	/* calling strtok with pwstring causes strtok to find the 
         * first token in pwstring, that is, the characters between the 
         * beginning of the line and the first delimiter (:). it returns
         * a pointer to the first character of the first token, if 
         * it successfully finds a token. The first delimiter is 
         * REPLACED with a null terminator. */
	char *p = strtok(pwstring, ":");

	/* does the first token contain the same chars as the
        * command line argument the user provided */
        if (strcmp(argv[1], p) == 0) {

            /* if yes, make a copy of the first token and assign it to the 
             * passwd struct's pw_name member. we don't strictly need
             * to make a copy here, but in more complex code, it would
             * ensure that the string in question remains attached to the
             * pw_name member after the buffer (pwstring) is reused for the 
             * next line */

	    mypasswd.pw_name = strdup(p);
            /* strdup can fail, since it is allocating new memory and 
             * we might be out of free memory */
	    if (mypasswd.pw_name == NULL) {
		perror("strdup");
		exit(5);
	    }

            /* calling strtok with the first argument NULL means it will try
             * to find the next token in the same string it was previously 
             * working on, that is, pwstring, in this case */ 

	    /* find the second field, which is 'x' - we ignore it*/
	    p = strtok(NULL, ":");
            /* find the third field, which is uid */
	    p = strtok(NULL, ":");

            /* the field is a string - convert it to a number, and cast that
             * integer-type number to uid_t. TODO - handle strtoll errors */
	    mypasswd.pw_uid = (uid_t) strtoll(p, NULL, 10);

            /* print the struct members we set, just to show it worked */
	    printf("Username %s, UID %lld\n", mypasswd.pw_name,
		   (long long) mypasswd.pw_uid);
	}

    }


    return 0;
}
