#if !defined HAVE_COLORMIX_H__
#define      HAVE_COLORMIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//<<
// operations on 32-bit integers where 3 color channels
// of 8 bit are expected to be in the least significant 24 bits.
// The order (e.g. 0x00RRGGBB vs. 0x00BBGGRR) does not matter.
//>>

static inline uint color01(uint c, ulong v)
// Return color with each channel scaled by v
// 0 <= v <= (1<<16)  corresponding to 0.0 ... 1.0
{
    // version 0:
//    uint t;
//    t  = (((c & 0xff) * v) >> 16) & 0x0000ff;
//    c >>= 8;
//    t |= (((c & 0xff) * v) >>  8) & 0x00ff00;
//    c >>= 8;
//    t |= (((c & 0xff) * v)      ) & 0xff0000;
//    return  t;

    // version 1:
    uint t;
    t = c & 0xff00ff00;  // must include alpha channel bits ...
    c ^= t;  // ... because they must be removed here
    t *= (uint)v;
    t >>= 24;  t <<= 8;
    v >>= 8;
    c *= (uint)v;
    c >>= 8;
    c &= 0xff00ff;
    return  c | t;

    // version 2:
//    uint t;
//    v >>= 8;
//    t  = (((0xff00ff & c) * v) >> 8 ) & 0xff00ff;
//    t |= (((0x00ff00 & c) * v) >> 8 ) & 0x00ff00;
//    return  t;
}
// -------------------------


static inline uint color_mix(uint c1, uint c2, ulong v)
// Return channel-wise average of colors:  (1.0-v)*c1 + v*c2
// 0 <= v <= (1<<16)  corresponding to 0.0 ... 1.0
// c1   ...    c2
{
    ulong w = (1UL<<16)-v;
    c1 = color01(c1, w);
    c2 = color01(c2, v);
    return  c1 + c2;  // no overflow in color channels
}
// -------------------------


static inline uint color_mix_50(uint c1, uint c2)
// Return channel-wise average of colors c1 and c2
// Shortcut for the special case (50% transparency)
//   of color_mix(c1, c2, "0.5")
// The least significant bits are ignored
// (in all functions color_mix_NN() )
{
    return  ((c1 & 0xfefefe) + (c2 & 0xfefefe)) >> 1;  // 50% c1, 50% c2
}
// -------------------------

static inline uint color_mix_25(uint c1, uint c2)
{
    return  color_mix_50(c2, color_mix_50(c1, c2));  // 25% c1, 75% c2
}
// -------------------------

static inline uint color_mix_75(uint c1, uint c2)
{
    return  color_mix_50(c1, color_mix_50(c1, c2));  // 75% c1, 25% c2
}
// -------------------------


static inline uint color_mix_25(uint c1, uint c2, uint c3)
{
    return  color_mix_25(c1, color_mix_50(c2, c3));  // 25% c1, 37.5% c2, 37.5% c3
}
// -------------------------

static inline uint color_mix_50(uint c1, uint c2, uint c3)
{
    return  color_mix_50(c1, color_mix_50(c2, c3) );  // 50% c1, 25% c2, 25% c3
}
// -------------------------

static inline uint color_mix_75(uint c1, uint c2, uint c3)
{
    return  color_mix_75(c1, color_mix_50(c2, c3) );  // 75% c1, 12.5% c2, 12.5% c3
}
// -------------------------



static inline uint color_sum_adjust(uint s)
// Set color channel to max (0xff) iff an overflow occurred
//  (that is, leftmost bit in channel is set)
{
    uint m = s & 0x808080;  // 1000 0000 // overflow bits
    s ^= m;
#if  1
    m >>= 7;    // 0000 0001
    m *= 0xff;  // 1111 1111  // optimized to (m<<8)-m by gcc
    return  (s << 1) | m;
#else
    m |= (m >> 1);  // 1100 0000
    m |= (m >> 2);  // 1111 0000
    m |= (m >> 4);  // 1111 1111
    return  (s << 1) | m;
#endif
}
// -------------------------


static inline uint color_sum(uint c1, uint c2)
// Return channel-wise saturated sum of colors c1 and c2.
// The least significant bits are ignored.
{
    uint s = color_mix_50(c1, c2);
    return  color_sum_adjust(s);
}
// -------------------------


static inline uint color_sum(uint c0, uint c1, uint c2)
// Return channel-wise saturated sum of colors c0, c1 and c2.
// The least significant bits are ignored.
{
    return  color_sum( color_sum(c1, c2), c0 );
}
// -------------------------


static inline uint color_mult(uint c1, uint c2)
// Return channel-wise product of colors c1 and c2.
// Corresponding to an object of color c1
//  illuminated by a light of color c2
{
    uint t = ((c1 & 0xff) * (c2 & 0xff)) >> 8;
    c1 >>= 8;  c2 >>= 8;
    t |= ((c1 & 0xff) * (c2 & 0xff)) & 0xff00;
    c1 &= 0xff00;  c2 >>= 8;
    t |= ((c1 * c2) & 0xff0000);
    return  t;
}
// -------------------------


#endif // !defined HAVE_COLORMIX_H__
