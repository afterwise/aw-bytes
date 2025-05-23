
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

#ifndef AW_TYPES_H
#define AW_TYPES_H

#if !defined(_MSC_VER) || _MSC_VER >= 1600
# include <stdint.h>
#endif

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM64))
# include <intrin.h>
#elif defined(__i386__) || defined(__x86_64__)
# include <immintrin.h>
#endif

#if defined(_MSC_VER)
# define fmt_s64(...) "%" #__VA_ARGS__ "I64d"
# define fmt_u64(...) "%" #__VA_ARGS__ "I64u"
# define fmt_x64(...) "%" #__VA_ARGS__ "I64x"
# define imm_s64(x) (x##i64)
# define imm_u64(x) (x##ui64)
#elif defined(__WORDSIZE) && __WORDSIZE == 64 && defined(__linux__)
# define fmt_s64(...) "%" #__VA_ARGS__ "ld"
# define fmt_u64(...) "%" #__VA_ARGS__ "lu"
# define fmt_x64(...) "%" #__VA_ARGS__ "lx"
# define imm_s64(x) (x##l)
# define imm_u64(x) (x##ul)
#else
# define fmt_s64(...) "%" #__VA_ARGS__ "lld"
# define fmt_u64(...) "%" #__VA_ARGS__ "llu"
# define fmt_x64(...) "%" #__VA_ARGS__ "llx"
# define imm_s64(x) (x##ll)
# define imm_u64(x) (x##ull)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

#if defined(_MSC_VER)
typedef signed __int64 s64;
typedef unsigned __int64 u64;
#elif defined(__WORDSIZE) && __WORDSIZE == 64 && defined(__linux__)
typedef signed long s64;
typedef unsigned long u64;
#else
typedef signed long long s64;
typedef unsigned long long u64;
#endif

typedef float f32;
typedef double f64;

typedef s16 q16;
typedef s32 q32;
typedef s64 q64;

#if !defined(_have_simd_types)
# if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#  define _have_simd_types 1
typedef __m128i u32x4;
typedef __m128 f32x4;
# elif defined(__ARM_NEON)
#  define _have_simd_types 1
typedef unsigned int u32x4 __attribute__((vector_size(16)));
typedef float f32x4 __attribute__((vector_size(16)));
# elif defined(_M_ARM64)
#  define _have_simd_types 1
typedef uint32x4_t u32x4;
typedef float32x4_t f32x4;
# elif defined(__PPU__) || defined(__SPU) || defined(__ppc64__)
#  define _have_simd_types 1
typedef vector unsigned int u32x4;
typedef vector float f32x4;
# elif defined(_M_PPC)
#  define _have_simd_types 1
typedef __declspec(align(16)) unsigned int u32x4[4];
typedef __vector4 f32x4;
# endif
#endif /* !defined(_have_simd_types) */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_TYPES_H */

