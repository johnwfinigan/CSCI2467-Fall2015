# Homework 1 - Due September 22 at 11:59 PM

Your mission is to explain in detail the control flow of the loop at lines 
32 through 48 of copyfile-final.c, which you can find at https://github.com/johnwfinigan/CSCI2467-Fall2015/blob/master/copyfile-examples/copyfile-final.c

Lines 32 through 48 correspond to the main while() loop containing read() and write().

To do this you should write out a list of the loop's iterations and values
of variables in each iteration. By default, assume that read() and write() do 
not return -1 or a partial read or write, but rather read or write the full 
amount requested. However, please see below: you must explain several scenarios 
where this is not the case.

Don't forget about "man 2 read" and "man 2 write", and also the Stevens Ch. 3 sections on read and write.

# Example:

Q - Assume sourcefile is 1024 bytes in size (Remember, assume defaults as above).

A - See the following:

* First iteration:
  * Line 32: we ask to read 1024 bytes from sourcefile into buf.
  * rret = 1024 - read returns full request successfully (default assumption).
  * buf[0] through buf[1023] now contain valid file data.
  * Line 33: rret != -1. If not taken.
  * Line 41: wcount = 0, so we start writing from buf[0]
  * rret = 1024, and wcount = 0, so we ask to write 1024 butes from address of buf[0]
  * write succeeds in writing full amount (default assumption). wret becomes 1024. 
  * Line 42: wret != -1. If not taken.
  * Line 46: wcount == 1024 and rcount == 1024, so do-while terminates.
* Second iteration:
  * read returns 0 due to EOF. While loop at line 32 breaks.

# Please solve:

Noting default assumptions as needed:

1. Assume sourcefile is 1040 bytes in size.
2. Assume sourcefile is 1024 bytes in size, and upon the first iteration of
the do-while, write() returns 400.
3. Assume sourcefile is 1024 bytes, and upon the first iteration of the while
starting at line 32, read() returns 400.
4. Assume sourcefile is 1040 bytes and a read error occurs in the first iteration.

# Please do not commit solutions to a public repo!
