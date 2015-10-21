# Homework 3 - Due October 28 at 11:55 PM

Modify the code at [HW3/readdir_r-hw.c](https://github.com/johnwfinigan/CSCI2467-Fall2015/blob/master/homeworks-labs/HW3/readdir_r-hw.c) 
to print out the name and mode of each file. The mode must be printed **in octal**.

If the file is a directory, print the word (Directory) after the name.

Submit one .c file on Moodle.

# Hints

     man 2 stat

# Sample output

Please try to stick to this format:

      mode: 40775, name: . (Directory)
      mode: 40775, name: .. (Directory)
      mode: 100664, name: readdir_r-v1.c 
      mode: 100664, name: Homework3-due-October28-1155pm.md

Your output does not have to be sorted in any particular order.
