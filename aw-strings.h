
/*
   Copyright (c) 2014-2024 Malte Hildingsson, malte (at) afterwi.se

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

#ifndef AW_STRINGS_H
#define AW_STRINGS_H

#include <stdarg.h>
#if !defined(_MSC_VER) || _MSC_VER >= 1800
# include <stdbool.h>
#endif
#include <stddef.h>
#if !defined(_MSC_VER) || _MSC_VER >= 1600
# include <stdint.h>
#endif
#include <stdio.h>
#include <string.h>
#if !defined(_MSC_VER)
# include <strings.h>
#endif

#if defined(__GNUC__)
# define _strings_alwaysinline inline __attribute__((always_inline))
# define _strings_unused __attribute__((unused))
#elif defined(_MSC_VER)
# define _strings_alwaysinline __forceinline
# define _strings_unused
#endif

#if defined(__GNUC__)
# define _strings_scanformat(a,b) __attribute__((format(__scanf__, a, b)))
# define _strings_printformat(a,b) __attribute__((format(__printf__, a, b)))
#else
# define _strings_scanformat(a,b)
# define _strings_printformat(a,b)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
typedef signed __int64 strings_ssize_t;
#else
typedef ssize_t strings_ssize_t;
#endif

_strings_alwaysinline
static int _vstrscanf(const char *__restrict str, const char *__restrict format, va_list ap) {
#if defined(__GNUC__)
	return vsscanf(str, format, ap);
#elif defined(_MSC_VER)
	return vsscanf_s(str, format, ap);
#endif
}

_strings_scanformat(2, 3)
_strings_unused
static inline int _strscanf(const char *__restrict str, const char *__restrict format, ...) {
	va_list ap;
	va_start(ap, format);
	int err = _vstrscanf(str, format, ap);
	va_end(ap);
	return err;
}

_strings_alwaysinline
static int _vstrnprintf(char *__restrict str, size_t size, const char *__restrict format, va_list ap) {
#if defined(__GNUC__)
	return vsnprintf(str, size, format, ap);
#elif defined(_MSC_VER)
	return vsnprintf_s(str, size, _TRUNCATE, format, ap);
#endif
}

_strings_printformat(3, 4)
_strings_unused
static inline int _strnprintf(char *__restrict str, size_t size, const char *__restrict format, ...) {
	va_list ap;
	va_start(ap, format);
	int err = _vstrnprintf(str, size, format, ap);
	va_end(ap);
	return err;
}

_strings_alwaysinline
_strings_unused
static bool _strcpy(char *dst, size_t dstsize, const char *src) {
	if (dst == nullptr || dstsize == 0 || src == nullptr)
		return false;
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || \
		defined(__DragonFly__) || defined(__ORBIS__) || defined(__PROSPERO__)
	return strlcpy(dst, src, dstsize) < dstsize;
#elif defined(__GNUC__)
	strncpy(dst, src, dstsize);
	if (dst[dstsize - 1] == 0)
		return true;
	dst[dstsize - 1] = 0;
	return false;
#elif defined(_MSC_VER)
	return strcpy_s(dst, dstsize, src) == 0;
#endif
}

_strings_alwaysinline
static int _strcasecmp(const char *s1, const char *s2) {
#if defined(__GNUC__)
	return strcasecmp(s1, s2);
#elif defined(_MSC_VER)
	return _stricmp(s1, s2);
#endif
}

_strings_alwaysinline
static int _strncasecmp(const char *s1, const char *s2, size_t n) {
#if defined(__GNUC__)
	return strncasecmp(s1, s2, n);
#elif defined(_MSC_VER)
	return _strnicmp(s1, s2, n);
#endif
}

_strings_alwaysinline
static const char *_strcasestr(const char *haystack, const char *needle) {
#if defined(__GNUC__) && !(defined(__ORBIS__) || defined(__PROSPERO__))
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

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_STRINGS_H */

