# Homework 4 - Due November 9 at 11:55 PM

Modify the code at [HW4/HW4-Sample.c](https://github.com/johnwfinigan/CSCI2467-Fall2015/blob/master/homeworks-labs/HW4/HW4-Sample.c) 
to print out the name and mode of each file, just as before. The mode must be printed **in octal**.

**Plus, modify it to print out the associated owner and owning group for
each file. Print the names, NOT the uid and gid**

If the file is a directory, print the word (Directory) after the name.

Submit one .c file on Moodle.

# Hints

     man 2 stat
     man 3 readdir
     man 3 getpwuid
     man 3 getgrgid

**READ Stevens 6.1 through 6.5 to get background on getpwuid and getgrgid.**


# Sample output

Please try to make yours use this sample format. Your output, of course, 
will be different

Your output does not have to be sorted in any particular order.

      user: myuser, group: mygroup, mode: 100664, name: HW4-Sample.c 
      user: myuser, group: mygroup, mode: 100775, name: a.out 
      user: myuser, group: mygroup, mode: 100664, name: Homework4-due-November-9-1155pm.md 
      user: myuser, group: mygroup, mode: 40775, name: testdir (Directory)

##Extra credit (10 points)

Use character or string processing knowlege to skip and not print the 
entries for dot and dot-dot. Important! If you're going for extra credit
say so in a comment in the first line of your source!

