# Homework 2 - Due September 29, 11:59 PM

Solve question 3.6 in Stevens' *Advanced Programming in the Unix Environment*,
3rd edition, chapter 3. Reproduced here for your convenience:

If you open a file for read-write with the append flag, can you still `read` from anywhere
in the file using `lseek`? Can you use `lseek` to replace existing data in the file?
Write a program to verify this.

#Hints

**Hint based on student question: All sentences in the question assume that the file is 
opened with O_APPEND** 

    man 2 read
    man 2 write
    man 2 lseek
    man 2 open

#What to turn in

Submit one .c source code file. Put your answers to the questions in a C comment
block at the top of the file.

# Please do not commit solutions to a public repo!
