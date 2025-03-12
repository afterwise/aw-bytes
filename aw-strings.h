
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
#include <string.h>
#include <sys/types.h>

#if defined(_strings_dllexport)
# if defined(_MSC_VER)
#  define _strings_api extern __declspec(dllexport)
# elif defined(__GNUC__)
#  define _strings_api __attribute__((visibility("default"))) extern
# endif
#elif defined(_strings_dllimport)
# if defined(_MSC_VER)
#  define _strings_api extern __declspec(dllimport)
# endif
#endif
#ifndef _strings_api
# define _strings_api extern
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

_strings_scanformat(2, 3)
_strings_api int _strscanf(const char *__restrict str, const char *__restrict format, ...);
_strings_api int _vstrscanf(const char *__restrict str, const char *__restrict format, va_list ap);

_strings_printformat(3, 4)
_strings_api int _strnprintf(char *__restrict str, size_t size, const char *__restrict format, ...);
_strings_api int _vstrnprintf(char *__restrict str, size_t size, const char *__restrict format, va_list ap);

#if !defined(_MSC_VER)
_strings_api char* _strdup(const char* str);
#endif
_strings_api bool _strcpy(char *dst, size_t dstsize, const char *src);
_strings_api bool _strcat(char* dst, size_t dstsize, const char* src);

_strings_api int _strcasecmp(const char *s1, const char *s2);
_strings_api int _strncasecmp(const char *s1, const char *s2, size_t n);

_strings_api const char *_strcasestr(const char *haystack, const char *needle);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_STRINGS_H */

