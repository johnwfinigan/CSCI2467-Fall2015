#Homework 5

Due date: December 2, 7:00 pm (to be returned in class on the 3rd)

May be turned in late with no penalty, as long as it's turned in prior to the final.

Reproduced below in its entirety is the OpenBSD 5.8 String processing function strnlen().

Turn in one .c file to Moodle containing this code and sufficient comments to explain every line in detail. In particular, you MUST explain all three clauses of the for loop in detail, and also explain the for loop's empty body.


##HINT

Section 4 in Essential C talks about functions (went over in class 11/25)

Be sure to read the formal definition of the for loop in section 6.8.5.3 of the [C11 standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) (page 151 as marked on bottom of PDF page)


```
/*  $OpenBSD: strnlen.c,v 1.5 2014/06/10 04:17:37 deraadt Exp $ */

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

size_t
strnlen(const char *str, size_t maxlen)
{
    const char *cp;

    for (cp = str; maxlen != 0 && *cp != '\0'; cp++, maxlen--)
        ;

    return (size_t)(cp - str);
}
```
