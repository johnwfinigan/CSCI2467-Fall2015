#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>


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

    /* used for cases when group name or user name is
     *  unknown - the missing name  will be filled with the uid/gid
     *  converted to string instead */
    struct passwd dummy_passwd;
    struct group dummy_group;
    char uidstring[32] = { 0 };
    char gidstring[32] = { 0 };
    dummy_passwd.pw_name = uidstring;
    dummy_group.gr_name = gidstring;


    for (;;) {

	int ret = readdir_r(dstream, &d, &result);

	if (ret != 0) {
	    perror("readdir_r error");
	    exit(3);
	}
	if (!result) {
	    break;
	}

	/* from here on, do nothing (skip entry) if d_name is . or .. */
	if ((strcmp(d.d_name, ".") != 0) && (strcmp(d.d_name, "..") != 0)) {

	    struct stat mystat;	/* must declare the struct itself, not just
				   a pointer to it, so the memory gets 
				   allocated for the whole struct */

	    if ((stat(d.d_name, &mystat) == -1)) {	/* but stat wants a pointer to
							   the struct, so use & */
		perror("stat");
		exit(4);
	    }

	    char *dir = "";	/* variable dir points to an empty string */

	    if (S_ISDIR(mystat.st_mode))	/* if it's a directory, change dir */
		dir = "(Directory)";	/* to point to the string "(Directory)" */

	    /* yours doesnt need to be this complex! This just handles
	     *  the error that the user/group name is not found */
	    errno = 0;
	    struct passwd *pw = getpwuid(mystat.st_uid);
	    if (pw == NULL) {
		if (errno != 0) {
		    perror("getpwuid");
		    exit(5);
		} else {
		    /* user name is unknown - put unknown uid as string into
		     * dummy struct */
		    snprintf(dummy_passwd.pw_name, 32, "%llu",
			     (unsigned long long)mystat.st_uid);
		    /* but watch out for truncation - although 2^64 is only 
		     * 20 digits or so*/
		    pw = &dummy_passwd;
		}
	    }

	    errno = 0;
	    struct group *gr = getgrgid(mystat.st_gid);
	    if (gr == NULL) {
		if (errno != 0) {
		    perror("getgrgid");
		    exit(5);
		} else {
		    /* group name is unknown - put unknown gid as string into
		     * dummy struct */
		    snprintf(dummy_group.gr_name, 32, "%llu",
			     (unsigned long long)mystat.st_gid);
		    /* but watch out for truncation - although 2^64 is only 
		     * 20 digits or so*/
		    gr = &dummy_group;
		}
            }

		/* now we can print the mode in octal using %llo, the name, and
		 *  the string dir which may either be "" or "(Directory)" */
		printf("user: %s, group: %s, mode: %llo, name: %s %s\n",
		       pw->pw_name, gr->gr_name,
		       (long long) mystat.st_mode, d.d_name, dir);
	    }
	
    }
    return 0;
}
