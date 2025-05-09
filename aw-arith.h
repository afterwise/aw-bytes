
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

#ifndef AW_ARITH_H
#define AW_ARITH_H

#include "aw-types.h"
#include <math.h>

#if !defined(_MSC_VER) || _MSC_VER >= 1800
# include <stdbool.h>
#else
# include <stddef.h>
#endif

#if defined(__GNUC__)
# define _arith_alwaysinline inline __attribute__((always_inline))
# define _arith_likely(x) __builtin_expect(!!(x), 1)
# define _arith_unlikely(x) __builtin_expect(!!(x), 0)
#elif defined(_MSC_VER)
# define _arith_alwaysinline __forceinline
# define _arith_likely(x) (x)
# define _arith_unlikely(x) (x)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PI (3.1415926535897932384626433832795f)
#define TWO_PI (6.283185307179586476925286766559f)
#define HALF_PI (1.5707963267948966192313216916398f)
#define QUARTER_PI (0.785398163397448309615660845819876f)
#define ONE_OVER_PI (0.31830988618379067153776752674503f)
#define TWO_OVER_PI (0.636619772367581343075535053490057f)
#define ROOT_TWO (1.4142135623730950488016887242097f)
#define ROOT_HALF (0.70710678118654752440084436210485f)
#define DEG_TO_RAD (0.01745329f)
#define RAD_TO_DEG (57.29578f)
#define MAX_POS_FLOAT (3.402823466e+38f)
#define MIN_NEG_FLOAT (-3.402823466e+38f)
#define LOG_2 (0.69314718056f)
#define LOG_10 (2.30258509299f)

_arith_alwaysinline u32 lsr31(u32 a) { return a >> 31; }
_arith_alwaysinline u64 lsr63(u64 a) { return a >> 63; }
_arith_alwaysinline s32 asr31(s32 a) { return a >> 31; }
_arith_alwaysinline s64 asr63(s64 a) { return a >> 63; }

_arith_alwaysinline s32 abs_s32(s32 a) { return (a ^ asr31(a)) - asr31(a); }
_arith_alwaysinline s64 abs_s64(s64 a) { return (a ^ asr63(a)) - asr63(a); }

#if defined(__PPU__)
_arith_alwaysinline f32 abs_f32(f32 a) { return __fabsf(a); }
#elif defined(_M_PPC)
_arith_alwaysinline f32 abs_f32(f32 a) { return __fabsf(a); }
#elif defined(__allegrex__)
_arith_alwaysinline f32 abs_f32(f32 a) { f32 r; __asm__("abs.s %0, %1" : "=r"(r) : "r"(a)); return r; }
#else
_arith_alwaysinline f32 abs_f32(f32 a) { return fabsf(a); }
#endif

#if defined(__PPU__)
_arith_alwaysinline f32 sel_f32(f32 x, f32 a, f32 b) { return __fsels(x, a, b); }
#elif defined(_M_PPC)
_arith_alwaysinline f32 sel_f32(f32 x, f32 a, f32 b) { return __fsel(x, a, b); }
#else
_arith_alwaysinline f32 sel_f32(f32 x, f32 a, f32 b) { return x >= 0.f ? a : b; }
#endif

_arith_alwaysinline s32 sel_s32(s32 x, s32 a, s32 b) { return a + ((b - a) & asr31(x)); }
_arith_alwaysinline u32 sel_u32(u32 x, u32 a, u32 b) { return a + ((b - a) & asr31(x)); }
_arith_alwaysinline s64 sel_s64(s64 x, s64 a, s64 b) { return a + ((b - a) & asr63(x)); }
_arith_alwaysinline u64 sel_u64(u64 x, u64 a, u64 b) { return a + ((b - a) & asr63(x)); }

_arith_alwaysinline s32 selgtz_s32(s32 x, s32 a, s32 b) { return b + ((a - b) & -asr31(x)); }
_arith_alwaysinline u32 selgtz_u32(u32 x, u32 a, u32 b) { return b + ((a - b) & -asr31(x)); }
_arith_alwaysinline s64 selgtz_s64(s64 x, s64 a, s64 b) { return b + ((a - b) & -asr63(x)); }
_arith_alwaysinline u64 selgtz_u64(u64 x, u64 a, u64 b) { return b + ((a - b) & -asr63(x)); }

_arith_alwaysinline s32 selltz_s32(s32 x, s32 a, s32 b) { return b + ((a - b) & asr31(x)); }
_arith_alwaysinline u32 selltz_u32(u32 x, u32 a, u32 b) { return b + ((a - b) & asr31(x)); }
_arith_alwaysinline s64 selltz_s64(s64 x, s64 a, s64 b) { return b + ((a - b) & asr63(x)); }
_arith_alwaysinline u64 selltz_u64(u64 x, u64 a, u64 b) { return b + ((a - b) & asr63(x)); }

#if defined(__allegrex__)
_arith_alwaysinline s32 selz_s32(s32 x, s32 a, s32 b) {
	__asm__("movz %0, %1, %2" : "=&r"(b) : "r"(a), "r"(x));
	return b;
}
_arith_alwaysinline u32 selz_u32(u32 x, u32 a, u32 b) {
	__asm__("movz %0, %1, %2" : "=&r"(b) : "r"(a), "r"(x));
	return b;
}
#else
_arith_alwaysinline s32 selz_s32(s32 x, s32 a, s32 b) { return a + ((b - a) & asr31(-(s32) x | x)); }
_arith_alwaysinline u32 selz_u32(u32 x, u32 a, u32 b) { return a + ((b - a) & asr31(-(s32) x | x)); }
#endif
_arith_alwaysinline s64 selz_s64(s64 x, s64 a, s64 b) { return a + ((b - a) & asr63(-(s64) x | x)); }
_arith_alwaysinline u64 selz_u64(u64 x, u64 a, u64 b) { return a + ((b - a) & asr63(-(s64) x | x)); }

_arith_alwaysinline s32 incwrap_s32(s32 x, s32 mx) { return sel_s32(mx - (x + 1), x + 1, 0); }
_arith_alwaysinline u32 incwrap_u32(u32 x, u32 mx) { return sel_s32(mx - (x + 1), x + 1, 0); }
_arith_alwaysinline s64 incwrap_s64(s64 x, s64 mx) { return sel_s64(mx - (x + 1), x + 1, 0); }
_arith_alwaysinline u64 incwrap_u64(u64 x, u64 mx) { return sel_s64(mx - (x + 1), x + 1, 0); }

_arith_alwaysinline s32 decwrap_s32(s32 x, s32 mx) { return sel_s32(x - 1, x - 1, mx); }
_arith_alwaysinline u32 decwrap_u32(u32 x, u32 mx) { return sel_s32(x - 1, x - 1, mx); }
_arith_alwaysinline s64 decwrap_s64(s64 x, s64 mx) { return sel_s64(x - 1, x - 1, mx); }
_arith_alwaysinline u64 decwrap_u64(u64 x, u64 mx) { return sel_s64(x - 1, x - 1, mx); }

_arith_alwaysinline s32 min_s32(s32 a, s32 b) { return a < b ? a : b; }
_arith_alwaysinline s64 min_s64(s64 a, s64 b) { return a < b ? a : b; }
_arith_alwaysinline u32 min_u32(u32 a, u32 b) { return b + ((a - b) & asr31(a - b)); }
_arith_alwaysinline u64 min_u64(u64 a, u64 b) { return b + ((a - b) & asr63(a - b)); }
_arith_alwaysinline f32 min_f32(f32 a, f32 b) { return sel_f32(a - b, b, a); }

_arith_alwaysinline s32 max_s32(s32 a, s32 b) { return a < b ? b : a; }
_arith_alwaysinline s64 max_s64(s64 a, s64 b) { return a < b ? b : a; }
_arith_alwaysinline u32 max_u32(u32 a, u32 b) { return a + ((b - a) & asr31(a - b)); }
_arith_alwaysinline u64 max_u64(u64 a, u64 b) { return a + ((b - a) & asr63(a - b)); }
_arith_alwaysinline f32 max_f32(f32 a, f32 b) { return sel_f32(a - b, a, b); }

_arith_alwaysinline s32 clamp_s32(s32 a, s32 mn, s32 mx) { return min_s32(max_s32(a, mn), mx); }
_arith_alwaysinline u32 clamp_u32(u32 a, u32 mn, u32 mx) { return min_u32(max_u32(a, mn), mx); }
_arith_alwaysinline f32 clamp_f32(f32 a, f32 mn, f32 mx) { return min_f32(max_f32(a, mn), mx); }
_arith_alwaysinline f32 saturate_f32(f32 a)  { return clamp_f32(a, 0.f, 1.f); }

_arith_alwaysinline s32 sgn_s32(s32 a) { return asr31(a) | lsr31(-a); }
_arith_alwaysinline f32 sgn_f32(f32 a) { return sel_f32(a, sel_f32(-abs_f32(a), 0.f, 1.f), -1.f); }

_arith_alwaysinline s32 isgn_s32(s32 a, s32 b) { return abs_s32(a) * sgn_s32(b); }
_arith_alwaysinline f32 isgn_f32(f32 a, f32 b) { return abs_f32(a) * sgn_f32(b); }

_arith_alwaysinline s32 sgnflip_s32(s32 a) { return a ^ (-(s32) lsr31(a) | (1 << 31)); }
_arith_alwaysinline s32 invsgnflip_s32(s32 a) { return a ^ ((lsr31(a) - 1) | (1 << 31)); }

_arith_alwaysinline u32 clz_u32(u32 a) {
        u32 r;

	if (_arith_unlikely(a == 0))
		return 32;

# if defined(__i386__) || defined(__x86_64__)
        __asm__ ("bsr %0, %1" : "=r" (r) : "r" (a));
	r = 31 - r;
# elif defined(_M_IX86) || defined(_M_X64)
        __asm bsr eax, a;
        __asm mov r, eax;
	r = 31 - r;
# elif defined(__PPU__)
        r = __cntlzw(a);
# elif defined(__SPU__)
        r = si_to_uint(si_clz(si_from_uint(a)));
# elif defined(__arm__)
        __asm__ ("clz %0, %1" : "=r" (r) : "r" (a) : "cc");
# else
# warning no clz
# endif

        return r;
}

_arith_alwaysinline u32 ctz_u32(u32 a) {
	if (_arith_unlikely(a == 0))
		return 32;

	return 31 - clz_u32(a & -(s32) a);
}

_arith_alwaysinline u32 floorpow2_u32(u32 a) {
	if (_arith_unlikely(a == 0))
		return 0;

	return 1 << (31 - clz_u32(a));
}

_arith_alwaysinline u32 ceilpow2_u32(u32 a) {
	--a;
	a |= a >> 1;
	a |= a >> 2;
	a |= a >> 4;
	a |= a >> 8;
	a |= a >> 16;
	return ++a;
}

_arith_alwaysinline bool ispow2_u32(u32 a) { return !(a & (a - 1)); }

_arith_alwaysinline u8 bitswap_u8(u8 v) {
        return (u8) (((v * 0x0802 & 0x22110) | (v * 0x8020 & 0x88440)) * 0x10101 >> 16);
}

_arith_alwaysinline f32 sqr_f32(f32 a) { return a * a; }
_arith_alwaysinline f32 smoothstep_f32(f32 a) { return (3 - 2 * a) * sqr_f32(a); }
_arith_alwaysinline f32 lerp_f32(f32 t, f32 a, f32 b) { return a + t * (b - a); }
_arith_alwaysinline f32 unlerp_f32(f32 t, f32 a, f32 b) { return t + a / (b - a); }

_arith_alwaysinline s32 log2_f32(f32 a) {
	union { f32 f; u32 u; } t;
	t.f = a;
	return (s32) ((t.u >> 23) & 0xff) - 127;
}

_arith_alwaysinline s32 trunc_f32(f32 a) {
#if defined(__i386__) || defined(__x86_64__)
	s32 t;

	asm ("fisttpl %0" : "=g" (t) : "t" (a));
	return t;
#elif defined(_M_IX86) || defined(_M_X64)
	s32 t;

	__asm fisttp dword ptr[t];
	return t;
#else
	return (s32) a;
#endif
}

_arith_alwaysinline s64 trunc_f64(f64 a) {
#if defined(__i386__) || defined(__x86_64__)
	s64 t;

	asm ("fisttpq %0" : "=g" (t) : "t" (a));
	return t;
#elif defined(_M_IX86) || defined(_M_X64)
	s64 t;

	__asm fisttp dword ptr[t];
	return t;
#else
	return (s64) a;
#endif
}

_arith_alwaysinline s32 round_f32(f32 a) {
#if defined(__i386__) || defined(__x86_64__)
	s32 t;

	asm("fistpl %0" : "=g" (t) : "t" (a));
	return t;
#elif defined(_M_IX86) || defined(_M_X64)
	s32 t;

	__asm fistp dword ptr[t];
	return t;
#else
	return lroundf(a);
#endif
}

_arith_alwaysinline s64 round_f64(f64 a) {
#if defined(__i386__) || defined(__x86_64__)
	s64 t;

	asm("fistpq %0" : "=g" (t) : "t" (a));

	return t;
#elif defined(_M_IX86) || defined(_M_X64)
	s64 t;

	__asm fistp dword ptr[t];
	return t;
#else
	return llroundf(a);
#endif
}

_arith_alwaysinline s32 ceil_f32(f32 a) {
	return -(round_f32(-0.5f - (a + a)) >> 1);
}

_arith_alwaysinline s64 ceil_f64(f64 a) {
	return -(round_f64(-0.5f - (a + a)) >> 1);
}

_arith_alwaysinline s32 floor_f32(f32 a) {
	return round_f32(-0.5f + (a + a)) >> 1;
}

_arith_alwaysinline s64 floor_f64(f64 a) {
	return round_f64(-0.5f + (a + a)) >> 1;
}

/* q16 */
_arith_alwaysinline q16 s16_to_q16(s16 s, s16 frac) { return s << frac; }
_arith_alwaysinline s16 q16_to_s16(q16 q, s16 frac) { return q >> frac; }
_arith_alwaysinline q16 f32_to_q16(f32 f, s16 frac) {
	return (trunc_f32(floor_f32(f)) << frac) | round_f32((f - floor_f32(f)) * (1 << frac));
}
_arith_alwaysinline f32 q16_to_f32(q16 x, s16 frac) {
	return (x >> frac) + (x & ((1 << frac) - 1)) / (f32) (1 << frac);
}
_arith_alwaysinline q16 add_q16(q16 x, q16 y) { return x + y; }
_arith_alwaysinline q16 sub_q16(q16 x, q16 y) { return x - y; }
_arith_alwaysinline q16 mul_q16(q16 x, q16 y, s16 frac) { return (x * y) >> frac; }
_arith_alwaysinline q16 div_q16(q16 x, q16 y, s16 frac) { return (x << frac) / y; }
_arith_alwaysinline q16 neg_q16(q16 x) { return -x; }
_arith_alwaysinline q16 abs_q16(q16 x) { return abs_s32(x); }

/* q32 */
_arith_alwaysinline q32 s32_to_q32(s32 s, s32 frac) { return s << frac; }
_arith_alwaysinline s32 q32_to_s32(q32 q, s32 frac) { return q >> frac; }
_arith_alwaysinline q32 f32_to_q32(f32 f, s32 frac) {
	return (trunc_f32(floor_f32(f)) << frac) | round_f32((f - floor_f32(f)) * (1 << frac));
}
_arith_alwaysinline f32 q32_to_f32(q32 x, s32 frac) {
	return (x >> frac) + (x & ((1 << frac) - 1)) / (f32) (1 << frac);
}
_arith_alwaysinline q32 add_q32(q32 x, q32 y) { return x + y; }
_arith_alwaysinline q32 sub_q32(q32 x, q32 y) { return x - y; }
_arith_alwaysinline q32 mul_q32(q32 x, q32 y, s32 frac) { return (x * y) >> frac; }
_arith_alwaysinline q32 div_q32(q32 x, q32 y, s32 frac) { return (x << frac) / y; }
_arith_alwaysinline q32 neg_q32(q32 x) { return -x; }
_arith_alwaysinline q32 abs_q32(q32 x) { return abs_s32(x); }

/* q64 */
_arith_alwaysinline q64 s64_to_q64(s64 s, s64 frac) { return s << frac; }
_arith_alwaysinline s64 q64_to_s64(q64 q, s64 frac) { return q >> frac; }
_arith_alwaysinline q64 f64_to_q64(f64 f, s64 frac) {
	return (trunc_f64(floor_f64(f)) << frac) | round_f64((f - floor_f64(f)) * (imm_s64(1) << frac));
}
_arith_alwaysinline f64 q64_to_f64(q64 x, s64 frac) {
	return (x >> frac) + (x & ((imm_s64(1) << frac) - 1)) / (f64) (imm_s64(1) << frac);
}
_arith_alwaysinline q64 add_q64(q64 x, q64 y) { return x + y; }
_arith_alwaysinline q64 sub_q64(q64 x, q64 y) { return x - y; }
_arith_alwaysinline q64 mul_q64(q64 x, q64 y, s64 frac) { return (x * y) >> frac; }
_arith_alwaysinline q64 div_q64(q64 x, q64 y, s64 frac) { return (x << frac) / y; }
_arith_alwaysinline q64 neg_q64(q64 x) { return -x; }
_arith_alwaysinline q64 abs_q64(q64 x) { return abs_s64(x); }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_ARITH_H */

