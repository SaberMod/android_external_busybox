/* vi: set sw=4 ts=4: */
/*
 * Utility routines.
 *
 * Copyright (C) 1999,2000,2001 by Erik Andersen <andersee@debian.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libbb.h"


#ifndef DMALLOC
extern void *xmalloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL && size != 0)
		error_msg_and_die(memory_exhausted);
	return ptr;
}

extern void *xrealloc(void *ptr, size_t size)
{
	ptr = realloc(ptr, size);
	if (ptr == NULL && size != 0)
		error_msg_and_die(memory_exhausted);
	return ptr;
}

extern void *xcalloc(size_t nmemb, size_t size)
{
	void *ptr = calloc(nmemb, size);
	if (ptr == NULL && nmemb != 0 && size != 0)
		error_msg_and_die(memory_exhausted);
	return ptr;
}

extern char * xstrdup (const char *s) {
	char *t;

	if (s == NULL)
		return NULL;

	t = strdup (s);

	if (t == NULL)
		error_msg_and_die(memory_exhausted);

	return t;
}
#endif

extern char * xstrndup (const char *s, int n) {
	char *t;

	if (s == NULL)
		error_msg_and_die("xstrndup bug");

	t = xmalloc(++n);
	
	return safe_strncpy(t,s,n);
}

FILE *xfopen(const char *path, const char *mode)
{
	FILE *fp;
	if ((fp = fopen(path, mode)) == NULL)
		perror_msg_and_die("%s", path);
	return fp;
}

extern int xopen(const char *pathname, int flags)
{
	int ret;
	
	ret = open(pathname, flags);
	if (ret == -1) {
		perror_msg_and_die("%s", pathname);
	}
	return ret;
}

extern ssize_t xread(int fd, void *buf, size_t count)
{
	ssize_t size;

	size = read(fd, buf, count);
	if (size == -1) {
		perror_msg_and_die("Read error");
	}
	return(size);
}

extern void xread_all(int fd, void *buf, size_t count)
{
	ssize_t size;

	size = xread(fd, buf, count);
	if (size != count) {
		error_msg_and_die("Short read");
	}
	return;
}

extern ssize_t xread_all_eof(int fd, void *buf, size_t count)
{
	ssize_t size;

	size = xread(fd, buf, count);
	if ((size != 0) && (size != count)) {
		error_msg_and_die("Short read");
	}
	return(size);
}

extern unsigned char xread_char(int fd)
{
	char tmp;
	
	xread_all(fd, &tmp, 1);

	return(tmp);	
}

/* Stupid gcc always includes its own builtin strlen()... */
#undef strlen
size_t xstrlen(const char *string)
{
	    return(strlen(string));
}

/* END CODE */
/*
Local Variables:
c-file-style: "linux"
c-basic-offset: 4
tab-width: 4
End:
*/
