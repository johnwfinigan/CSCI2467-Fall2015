#Test 2 study guide

The rule is, anything you needed to solve either Homework 3 or Homework 4 is fair game, as is anything we 
learned for Test 1. Test 1 material may only be present incidentally; I will not ask whole questions
on Test 1 material.

[HW3 Solution](https://github.com/johnwfinigan/CSCI2467-Fall2015/blob/master/homeworks-labs/HW4/HW4-Sample.c)
[HW4 Solution](https://github.com/johnwfinigan/CSCI2467-Fall2015/blob/master/homeworks-labs/HW4/HW4-Solution.c)

Here's a non-exhausive list:

* [Essential C](http://cslibrary.stanford.edu/101/EssentialC.pdf) Sections 1 and 2 and 3
    * All of section 3 is now included
    * For structs, know your `.` and your `->`
* From the texbook (Stevens' Advanced Programming the UNIX Environment)
  * Chapter 4
    * 4.1 through 4.3 (stat and file types)
    * 4.5 (file permissions)
    * 4.22 (reading directories)
  * Chapter 6
    * 6.1 through 6.5 (Password file, shadow passwords, group file, supplementary group IDs)

Manpages to read:
          man 2 stat
          man opendir
          man 3 readdir
          man 3 getpwuid
          man 3 getgrgid

Be able to differentiate a:
   * File from a file name from an inode
   * Directory from a directory entry
   * "regular" file from a directory or a special file - see Stevens 4.3 

**Do not** try to memorize manpages, since they will be provided to you on paper during the test.

**Do** try to be familiar with the manpages, knowing the principles of the various flags we talked about,
meanings of return values, etc.

**Do** understand what a string looks like in memory (array of bytes followed by a null terminator).

**Do** understand the difference between a pointer and a value.

