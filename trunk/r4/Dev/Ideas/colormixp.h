#if !defined HAVE_COLORMIXP_H__
#define      HAVE_COLORMIXP_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/colormix.h" // color_sum_adjust()
#include "fxttypes.h"

//<<
// Versions of some functionss from colormix.h that
// do not ignore the least significant bit
// (and are more expensive).
//
// The non-'perfect' versions should be ok for
//   the majority of applications.
//>>

static inline uint perfect_color_mix_50(uint c1, uint c2)
// Return channel-wise average of colors c1 and c2
{
#if  1
//    uint t = (c1 | c2) & 0x010101; // lowest channels bits in any arg
    uint t = (c1 & c2) & 0x010101; // lowest channels bits in both args
    return  color_mix_50(c1, c2) + t;

#else
    uint m = 0xff00ff;
    uint srb = (c1 & m) + (c2 & m) + 0x010001;
    srb >>= 1;
    srb &= m;

    m >>= 8;  // == 0xff00
    uint sg = (c1 & m) + (c2 & m) + 0x0100;
    sg >>= 1;
    sg &= m;

    return  srb | sg;
#endif
}
// -------------------------

static inline uint perfect_color_mix_75(uint c1, uint c2)
{
    return  perfect_color_mix_50(c1, perfect_color_mix_50(c1, c2));  // 75% c1
}
// -------------------------

static inline uint perfect_color_sum(uint c1, uint c2)
{
    uint srb = (c1 & 0xff00ff) + (c2 & 0xff00ff) + 0x010001;
    uint mrb = srb & 0x01000100;
    srb ^= mrb;
    uint sg = (c1 & 0xff00) + (c2 & 0xff00) + 0x0100;
    uint mg = (sg & 0x010000);
    sg ^= mg;
    uint m = (mrb | mg) >> 1;  // 1000 0000 // overflow bits
    m |= (m >> 1);  // 1100 0000
    m |= (m >> 2);  // 1111 0000
    m |= (m >> 4);  // 1111 1111
    return  srb | sg | m;
}
// -------------------------

static inline uint perfect_color_sum(uint c0, uint c1, uint c2)
{
    return  perfect_color_sum( perfect_color_sum(c1, c2), c0 );
}
// -------------------------


#endif // !defined HAVE_COLORMIXP_H__
