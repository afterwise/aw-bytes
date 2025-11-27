
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

#ifndef AW_ENDIAN_H
#define AW_ENDIAN_H

#include "aw-types.h"

#if defined(__GNUC__)
# define _endian_alwaysinline __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
# define _endian_alwaysinline __forceinline
#endif

#ifdef __cplusplus
extern "C" {
#endif

_endian_alwaysinline
static u16 _byteswap16(u16 v) {
        return
                (v << 0x08 & 0xff00u) |
                (v >> 0x08 & 0x00ffu);
}

_endian_alwaysinline
static u32 _byteswap32(u32 v) {
        return
                (v << 0x18 & 0xff000000ul) |
                (v << 0x08 & 0x00ff0000ul) |
                (v >> 0x08 & 0x0000ff00ul) |
                (v >> 0x18 & 0x000000fful);
}

_endian_alwaysinline
static u64 _byteswap64(u64 v) {
        return
                (v << 0x38 & 0xff00000000000000ull) |
                (v << 0x28 & 0x00ff000000000000ull) |
                (v << 0x18 & 0x0000ff0000000000ull) |
                (v << 0x08 & 0x000000ff00000000ull) |
                (v >> 0x08 & 0x00000000ff000000ull) |
                (v >> 0x18 & 0x0000000000ff0000ull) |
                (v >> 0x28 & 0x000000000000ff00ull) |
                (v >> 0x38 & 0x00000000000000ffull);
}

#if defined(__BIG_ENDIAN__) || \
	defined(__ARMEB__) || defined(__THUMBEB__) || \
	defined(_M_PPC) || defined(__ppc64__) || \
	defined(__PPU__) || defined(__SPU)
_endian_alwaysinline static u16 _btoh16(u16 v) { return v; }
_endian_alwaysinline static u32 _btoh32(u32 v) { return v; }
_endian_alwaysinline static u64 _btoh64(u64 v) { return v; }

_endian_alwaysinline static u16 _ltoh16(u16 v) { return _byteswap16(v); }
_endian_alwaysinline static u32 _ltoh32(u32 v) { return _byteswap32(v); }
_endian_alwaysinline static u64 _ltoh64(u64 v) { return _byteswap64(v); }

_endian_alwaysinline static u16 _htob16(u16 v) { return v; }
_endian_alwaysinline static u32 _htob32(u32 v) { return v; }
_endian_alwaysinline static u64 _htob64(u64 v) { return v; }

_endian_alwaysinline static u16 _htol16(u16 v) { return _byteswap16(v); }
_endian_alwaysinline static u32 _htol32(u32 v) { return _byteswap32(v); }
_endian_alwaysinline static u64 _htol64(u64 v) { return _byteswap64(v); }
#else
_endian_alwaysinline static u16 _btoh16(u16 v) { return _byteswap16(v); }
_endian_alwaysinline static u32 _btoh32(u32 v) { return _byteswap32(v); }
_endian_alwaysinline static u64 _btoh64(u64 v) { return _byteswap64(v); }

_endian_alwaysinline static u16 _ltoh16(u16 v) { return v; }
_endian_alwaysinline static u32 _ltoh32(u32 v) { return v; }
_endian_alwaysinline static u64 _ltoh64(u64 v) { return v; }

_endian_alwaysinline static u16 _htob16(u16 v) { return _byteswap16(v); }
_endian_alwaysinline static u32 _htob32(u32 v) { return _byteswap32(v); }
_endian_alwaysinline static u64 _htob64(u64 v) { return _byteswap64(v); }

_endian_alwaysinline static u16 _htol16(u16 v) { return v; }
_endian_alwaysinline static u32 _htol32(u32 v) { return v; }
_endian_alwaysinline static u64 _htol64(u64 v) { return v; }
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AW_ENDIAN_H */

