/*
   Copyright (c) 2014-2025 Malte Hildingsson, malte (at) afterwi.se

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 */

#ifndef _strings_nofeatures
# if defined(_WIN32)
#  define WIN32_LEAN_AND_MEAN 1
# elif defined(__linux__)
#  define _BSD_SOURCE 1
#  define _DEFAULT_SOURCE 1
#  define _POSIX_C_SOURCE 200809L
#  define _SVID_SOURCE 1
# elif defined(__APPLE__)
#  define _DARWIN_C_SOURCE 1
# endif
#endif /* _strings_nofeatures */

#include "aw-strings.h"

#include <stdio.h>
#if !defined(_WIN32)
# include <strings.h>
#endif

int _vstrscanf(const char *__restrict str, const char *__restrict format, va_list ap) {
#if !defined(_WIN32)
	return vsscanf(str, format, ap);
#else
	return vsscanf_s(str, format, ap);
#endif
}

int _strscanf(const char *__restrict str, const char *__restrict format, ...) {
	va_list ap;
	va_start(ap, format);
	int err = _vstrscanf(str, format, ap);
	va_end(ap);
	return err;
}

int _vstrnprintf(char *__restrict str, size_t size, const char *__restrict format, va_list ap) {
#if !defined(_WIN32)
	return vsnprintf(str, size, format, ap);
#else
	return vsnprintf_s(str, size, _TRUNCATE, format, ap);
#endif
}

int _strnprintf(char *__restrict str, size_t size, const char *__restrict format, ...) {
	va_list ap;
	va_start(ap, format);
	int err = _vstrnprintf(str, size, format, ap);
	va_end(ap);
	return err;
}

#if !defined(_WIN32)
char* _strdup(const char* str) {
	return strdup(str);
}
#endif

bool _strcpy(char *dst, size_t dstsize, const char *src) {
	if (dst == NULL || dstsize == 0 || src == NULL)
		return false;
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || \
		defined(__DragonFly__) || defined(__ORBIS__) || defined(__PROSPERO__)
	return strlcpy(dst, src, dstsize) < dstsize;
#elif !defined(_WIN32)
	size_t n = strlen(src);
	bool trunc = false;
	if (n > dstsize - 1)
	{
		n = dstsize - 1;
		trunc = true;
	}
	memcpy(dst, src, n);
	dst[n] = 0;
	return !trunc;
#else
	return strncpy_s(dst, dstsize, src, _TRUNCATE) == 0;
#endif
}

bool _strncpy(char *dst, size_t dstsize, const char *src, size_t n) {
	if (dst == NULL || dstsize == 0 || src == NULL)
		return false;
	bool trunc = false;
	if (n > dstsize - 1)
	{
		n = dstsize - 1;
		trunc = true;
	}
	strncpy(dst, src, n);
	dst[n] = 0;
	return !trunc;
}

bool _strcat(char* dst, size_t dstsize, const char* src) {
	if (dst == NULL || dstsize == 0 || src == NULL)
		return false;
#if !defined(_WIN32)
	return strncat(dst, src, dstsize - strlen(dst) - 1) != NULL;
#else
	return strncat_s(dst, dstsize, src, _TRUNCATE) == 0;
#endif
}

int _strcasecmp(const char *s1, const char *s2) {
#if !defined(_WIN32)
	return strcasecmp(s1, s2);
#else
	return _stricmp(s1, s2);
#endif
}

int _strncasecmp(const char *s1, const char *s2, size_t n) {
#if !defined(_WIN32)
	return strncasecmp(s1, s2, n);
#else
	return _strnicmp(s1, s2, n);
#endif
}

const char *_strcasestr(const char *haystack, const char *needle) {
#if !defined(_WIN32) && !defined(__ORBIS__) && !defined(__PROSPERO__)
	return strcasestr(haystack, needle);
#else
	strings_ssize_t h = (strings_ssize_t) (haystack ? strlen(haystack) : 0);
	strings_ssize_t n = (strings_ssize_t) (needle ? strlen(needle) : 0);
	for (; h >= n; --h, ++haystack)
		if (_strncasecmp(haystack, needle, n) == 0)
			return haystack;
	return NULL;
#endif
}

