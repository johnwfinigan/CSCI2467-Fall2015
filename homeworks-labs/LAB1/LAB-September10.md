Get a terminal. If you're on Windows, open Cygwin or your preferred ssh terminal app.

Log into Cook using ssh, clone this repo, and cd into it:

(Dont type the $, the $ stands for your shell's prompt.)

$ ssh myUNOusername@cook.cs.uno.edu

(if you already have a copy of the repo, you can "git pull" and use it instead. Otherwise:)

$ git clone https://github.com/johnwfinigan/CSCI2467-Fall2015.git Lab-Sept10

$ cd Lab-Sept10/homeworks-labs/LAB1

Compile the program.

$ gcc -Wall -g -o copyfile ../../copyfile-examples/copyfile-September8.c

Now, start it in the debugger:

$ gdb ./copyfile

Set the program's arguments inside gdb. This will be eqivalent to calling it like
"./copyfile test-sourcefile copyof-test-sourcefile" on the shell. 

(don't type (gdb), (gdb) represents gdb's prompt)

(gdb) set args test-sourcefile copyof-test-sourcefile

List some of the program's source code, and find the line that says "if (argc != 3)"

(gdb) l

For me, the if statement is at line 10. Set a breakpoint there, or wherever the "if" is for you:

(gdb) b 10

Then run the program:

(gdb) r

Gdb will stop at the breakpoint you set. Let's look at what argv points to. Try these:

(gdb) p argv

(gdb) p *argv

(gdb) p argv[0]

(gdb) p *(argv+1)

(gdb) p argv[1]

argv is a pointer to a pointer to char. If we print argv itself, we just get the memory addrress
it contains. That is, the memory address of the char pointer that
argv points to, or, more specifically, the 
address of the 8 bytes in which argv's pointee's contents are stored.

But, if we use the * to tell gdb to go look at argv's pointee, or use the array index brackets
to access the pointees, we see the strings that the pointees point to.

Next, find the line of code that says "if (rret == -1)". For me, this is line 35. Set a breakpoint there

(gdb) l 35

(gdb) b 35

Set one more breakpoint right before the "exit(0)" at the end of the source, and then type "c" to continue execution.

(gdb) b 64

(gdb) c

Now, you can see the value of rret change as the loop iterates. Alternate pressing "c" and "p rret" until the loop breaks.

(gdb) c

(gdb) p rret

Why is rret different in the last iteration? 

Next, the program is just about to exit. Try printing scret and dcret. What do they represent?

Type q to exit.

