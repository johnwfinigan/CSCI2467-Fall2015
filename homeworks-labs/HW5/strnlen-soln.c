/*	$OpenBSD: strnlen.c,v 1.5 2014/06/10 04:17:37 deraadt Exp $	*/

/*
 * Copyright (c) 2010 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#include <string.h>


// begin JWF comments:
// strnlen returns an unsigned integer type, size_t
// and takes two arguments: str is a pointer to char (string)
// and is marked const, meaning that strnlen will not modify
// the addressee of this pointer.
// maxlen is an unsigned integer type, size_t
//
// strnlen takes as arguments a pointer to a string and
// a maximum length. it returns the lesser of maxlen or
// the length of the string, NOT counting the null terminator
size_t strnlen(const char *str, size_t maxlen)
{
  // cp is local to the scope of the function. it will be
  // allocated on the stack and discarded when the function
  // returns (automatic variable)
	const char *cp;

  // this for loop has no body. all of the action happens
  // inside the "iteration statement", which the standard
  // names thusly: (section 6.8.5.3, C11 draft standard, p151)
  // for ( clause-1 ; expression-2 ; expression-3 ) statement
  //
  // "statement" is empty. the semicolon terminates it.
  //
  // clause-1 initializes local variable cp to our local copy
  // of the pointer str. clause-1 is executed once, before
  // expression-2 is evaluated for the first time.
  //
  // expression-2, the "controlling expression", is evaluated
  // before each iteration (loop body execution). If it becomes
  // false, the loop breaks. It becomes false if *either* maxlen
  // becomes zero, *or* cp points to a null terminator.
  //
  // expression-3 is evaluated after each iteration. this is
  // important even here, with no body, since if expression-2
  // breaks the loop, expression-3 will not be executed afterward.
  // each time it is evaluated, cp is incremented by 1, and so
  // is made to point to the next char in the string
  //
  // also, maxlen is decremented by 1. this means that maxlen will
  // become zero at some point, unless the loop breaks first.
  // so an infinite loop is not possible.
  //
  // expression-3 is two expressions separated by a comma.
  // See C11 draft sec 6.5.17, p105 - both expressions are evaluated,
  // but the result of all but the rightmost is discarded.
  // discarding the result is irrelevant here since both expressions
  // work by side effect.

	for (cp = str; maxlen != 0 && *cp != '\0'; cp++, maxlen--)
		;

  // simply put, each iteration of the loop advances cp to the next
  // char in the string, and counts down maxlen by 1 each time.
  // if maxlen becomes 0 or cp points to a null terminator, it stops.
  // when it stops, cp points to *either* a char in the string,
  // before the end of the string (assuming maxlen became 0),
  // *or* it points to the null terminator.


  // cp and str are both pointers, so this is pointer subtraction of the
  // type where both operands are pointers, as in C11 draft standard,
  // 6.5.6, page 93, paragraph 9 - "the result is the difference of the
  // subscripts of the two array elements" (with cp and str taken to
  // both point to objects in the same array (here, string))
  //
  // since str and cp are char pointers, one array element is one byte,
  // that is one char, and so the result is how many chars are between
  // the beginning of the string (str), and cp.
  // this will either be the length of the string, or maxlen bytes.
  // result has type ptrdiff_t (standard), so its cast to the return
  // type of the function and returned.

	return (size_t)(cp - str);
}
