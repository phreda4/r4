// JPEG Decoder for GameBoy Advance modes 3/5
// Original Visual Basic version by Dmitry Brant.
//   http://www.dmitrybrant.com
// AA & N IDCT C code from IJG
//   http://www.ijg.org
// GBA GCC/GAS version by Jeff Frohwein.
//   http://www.devrs.com/gba/
//
//  This version uses a AA & N fast IDCT so only requires
// a 64 byte scale data table.
//
// v1.0318 - Original release
//
//******************************************************
// Draw a JPEG photo in GBA graphics modes 3/5 in ARM asm
// Entry: x = photo upper left X coordinate
//        y = photo upper left Y coordinate
//    photo = photo data base addr in ROM
//     addr = screen base addr in RAM
// (void) gfxJpeg (u8 x, u8 y, u8 *photo, u8 *addr);
//******************************************************
// INSTRUCTIONS:
//
// To use a JPEG photo with this software you need to
// first compact the JPEG to remove comments & to optimize
// the huffman tables to save ROM space. Use the following
// to do this (Get djpeg.exe & cjpeg.exe from devrs.com/gba in apps/misc):
//
//    djpeg -targa input.jpg > tmp.tga
//    cjpeg -optimize tmp.tga > file.jpg
//
// Next you need to convert this "file.jpg" to a .s or a .h
// file so that you can include it in your project.
// It's a little easier to use a .h file but your
// code will probably take longer to compile.
// Use whatever format you prefer. (Get b2x.exe from
// devrs.com/gba in the apps/misc section. Get v1.5 or later.):
//
//  To generate a .h (gcc compiler) file:
//  -------------------------------------
//    b2x -c -t u8 -n MyPhotoLabel <file.jpg > output.h
//
//    Now include this in your C file and try it like this:
//
//       typedef  unsigned char  u8;
//       #include "output.h"
//       #define _VRAM (u8 *)0x6000000
//       (void) gfxJpeg(0,0,&MyPhotoLabel[0], _VRAM);
//
//  To generate a .s (gas compiler) file:
//  -------------------------------------
//    b2x -a -d -n MyPhotoLabel <file.jpg > output.s
//
//    Using a text editor add the following line
//    to the top of output.s:
//
//      .global MyPhotoLabel
//
//    Add the following lines to your C file:
//
//       typedef  unsigned char  u8;
//       extern u8 MyPhotoLabel[];
//       #define _VRAM (u8 *)0x6000000
//       (void) gfxJpeg(0,0,&MyPhotoLabel[0], _VRAM);
//
//    Modify your makefile and/or gasdepend file to
//    make sure that output.s gets compiled & linked
//    into your project. For en example of doing this,
//    check out gfxLib on devrs.com/gba
//

// values for Zig-zag reordering

const u8 JPGZig1 [64] = {
   0,0,1,2,1,0,0,1,2,3,4,3,2,1,0,0,1,2,3,4,5,6,5,4,3,2,1,0,0,1,2,3,
   4,5,6,7,7,6,5,4,3,2,1,2,3,4,5,6,7,7,6,5,4,3,4,5,6,7,7,6,5,6,7,7
   };

const u8 JPGZig2 [64] = {
   0,1,0,0,1,2,3,2,1,0,0,1,2,3,4,5,4,3,2,1,0,0,1,2,3,4,5,6,7,6,5,4,
   3,2,1,0,1,2,3,4,5,6,7,7,6,5,4,3,2,3,4,5,6,7,7,6,5,4,5,6,7,7,6,7
   };

//  AA & N IDCT scaling table

const u16 JPGaanscales[64] = {
   /* precomputed values scaled up by 14 bits */
   16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
   22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
   21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
   19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
   16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
   12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
    8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
    4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247
   };

#define FIX_1_082392200  277     /* FIX(1.082392200) */
#define FIX_1_414213562  362     /* FIX(1.414213562) */
#define FIX_1_847759065  473     /* FIX(1.847759065) */
#define FIX_2_613125930  669     /* FIX(2.613125930) */

struct JpegType {                      // some type definitions (for coherence)
   u16 Rows;                           // image height
   u16 Cols;                           // image width
   u16 SamplesY;                       // sampling ratios
   u16 SamplesCbCr;
   u16 QuantTableY;                    // quantization table numbers
   u16 QuantTableCbCr;
   u16 HuffDCTableY;                   // huffman table numbers
   u16 HuffDCTableCbCr;
   u16 HuffACTableY;
   u16 HuffACTableCbCr;
   u16 NumComp;                        // number of components
   };

struct JPGHuffmanEntry {                   // a type for huffman tables
   u16 Index;
   s16 Code;
   u16 Length;
   }__attribute__ ((packed));

// Global variables

u32 JPGfindex;
u16 JPGDCTables;
u16 JPGACTables;
u16 JPGQTables;
u8 JPGcurByte;
u8 JPGcurBits;
u8 JPGeoi;
struct JPGHuffmanEntry JPGHuffmanDC0[256];
struct JPGHuffmanEntry JPGHuffmanDC1[256];
struct JPGHuffmanEntry JPGHuffmanAC0[256];
struct JPGHuffmanEntry JPGHuffmanAC1[256];
u16 JPGQuantTable0[64];    // 2 quantization tables (Y, CbCr)
u16 JPGQuantTable1[64];    // 2 quantization tables (Y, CbCr)
struct JpegType JPGImage;
s16 JPGCbVector[64];              // 1 vector for Cb attribute
s16 JPGCrVector[64];              // 1 vector for Cr attribute
u16 JPGXOrigin; u16 JPGYOrigin;
u32 JPGdata;

//External code in ARM assembly

extern u32 JPGGetByte (void);
extern u32 JPGGetWord (void);
extern u32 JPGNextBit (void);
extern void JPGClear128Bytes (u32 *);
extern s32 JPGReceiveBits (u16 cat);
extern s32 JPGDecode(struct JPGHuffmanEntry inArray[256]);
extern void JPGGetBlockBits (u16,u32 *);
extern void JPGDraw8x8 (u32 *, u32,u32, u32);

void jpeg_idct_ifast (s16 inarray[64], s16 outarray[64], u16 QuantTable[64])
  {
  // The following variables only need 16bits precision
  // but the resulting code is smaller if you use s32.
  s32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  s32 tmp10, tmp11, tmp12, tmp13;
  s32 z5, z10, z11, z12, z13;
  u32 ctr;
  u32 ctr8;
  s32 warray[64];

  /* Pass 1: process columns from input, store into work array. */

  for (ctr = 0; ctr < 8; ctr++)
    {
    /* Due to quantization, we will usually find that many of the input
     * coefficients are zero, especially the AC terms.  We can exploit this
     * by short-circuiting the IDCT calculation for any column in which all
     * the AC terms are zero.  In that case each output is equal to the
     * DC coefficient (with scale factor as needed).
     * With typical images and quantization tables, half or more of the
     * column DCT calculations can be simplified this way.
     */

    if (inarray[8+ctr] == 0 && inarray[16+ctr] == 0 &&
        inarray[24+ctr] == 0 && inarray[32+ctr] == 0 &&
        inarray[40+ctr] == 0 && inarray[48+ctr] == 0 &&
        inarray[56+ctr] == 0)
      {
      /* AC terms all zero */
      s16 dcval = inarray[ctr] * QuantTable[ctr];

      warray[ctr] = dcval;
      warray[8+ctr] = dcval;
      warray[16+ctr] = dcval;
      warray[24+ctr] = dcval;
      warray[32+ctr] = dcval;
      warray[40+ctr] = dcval;
      warray[48+ctr] = dcval;
      warray[56+ctr] = dcval;

      continue;
      }

    /* Even part */

    tmp0 = inarray[ctr] * QuantTable[ctr];
    tmp1 = inarray[16+ctr] * QuantTable[16+ctr];
    tmp2 = inarray[32+ctr] * QuantTable[32+ctr];
    tmp3 = inarray[48+ctr] * QuantTable[48+ctr];

    tmp10 = tmp0 + tmp2;	/* phase 3 */
    tmp11 = tmp0 - tmp2;

    tmp13 = tmp1 + tmp3;	/* phases 5-3 */
    tmp12 = (((tmp1 - tmp3) * FIX_1_414213562) >> 8) - tmp13; /* 2*c4 */

    tmp0 = tmp10 + tmp13;	/* phase 2 */
    tmp3 = tmp10 - tmp13;
    tmp1 = tmp11 + tmp12;
    tmp2 = tmp11 - tmp12;

    /* Odd part */

    tmp4 = inarray[8+ctr] * QuantTable[8+ctr];
    tmp5 = inarray[24+ctr] * QuantTable[24+ctr];
    tmp6 = inarray[40+ctr] * QuantTable[40+ctr];
    tmp7 = inarray[56+ctr] * QuantTable[56+ctr];

    z13 = tmp6 + tmp5;		/* phase 6 */
    z10 = tmp6 - tmp5;
    z11 = tmp4 + tmp7;
    z12 = tmp4 - tmp7;

    tmp7 = z11 + z13;		/* phase 5 */
    tmp11 = ((z11 - z13) * FIX_1_414213562) >> 8; /* 2*c4 */

    z5 = ((z10 + z12) * FIX_1_847759065) >> 8; /* 2*c2 */
    tmp10 = ((z12 * FIX_1_082392200) >> 8) - z5; /* 2*(c2-c6) */
    tmp12 = ((z10 * - FIX_2_613125930) >> 8) + z5; /* -2*(c2+c6) */

    tmp6 = tmp12 - tmp7;	/* phase 2 */
    tmp5 = tmp11 - tmp6;
    tmp4 = tmp10 + tmp5;

    warray[ctr] = (tmp0 + tmp7);
    warray[56+ctr] = (tmp0 - tmp7);
    warray[8+ctr] = (tmp1 + tmp6);
    warray[48+ctr] = (tmp1 - tmp6);
    warray[16+ctr] = (tmp2 + tmp5);
    warray[40+ctr] = (tmp2 - tmp5);
    warray[32+ctr] = (tmp3 + tmp4);
    warray[24+ctr] = (tmp3 - tmp4);
    }

  /* Pass 2: process rows from work array, store into output array. */
  /* Note that we must descale the results by a factor of 8 == 2**3, */
  /* and also undo the PASS1_BITS scaling. */

  for (ctr = 0; ctr < 8; ctr++)
    {
    ctr8 = ctr << 3;
    /* Rows of zeroes can be exploited in the same way as we did with columns.
     * However, the column calculation has created many nonzero AC terms, so
     * the simplification applies less often (typically 5% to 10% of the time).
     * On machines with very fast multiplication, it's possible that the
     * test takes more time than it's worth.  In that case this section
     * may be commented out.
     */

    if (warray[ctr8+1] == 0 && warray[ctr8+2] == 0 && warray[ctr8+3] == 0 && warray[ctr8+4] == 0 &&
        warray[ctr8+5] == 0 && warray[ctr8+6] == 0 && warray[ctr8+7] == 0)
      {
      /* AC terms all zero */
      s16 dcval = (warray[ctr8] >> 5)+128;
//      if (dcval<0) dcval = 0;
//      if (dcval>255) dcval = 255;

      outarray[ctr8] = dcval;
      outarray[ctr8+1] = dcval;
      outarray[ctr8+2] = dcval;
      outarray[ctr8+3] = dcval;
      outarray[ctr8+4] = dcval;
      outarray[ctr8+5] = dcval;
      outarray[ctr8+6] = dcval;
      outarray[ctr8+7] = dcval;
      continue;
      }

    /* Even part */

    tmp10 = warray[ctr8] + warray[ctr8+4];
    tmp11 = warray[ctr8] - warray[ctr8+4];

    tmp13 = warray[ctr8+2] + warray[ctr8+6];
    tmp12 = (((warray[ctr8+2] - warray[ctr8+6]) * FIX_1_414213562) >> 8) - tmp13;

    tmp0 = tmp10 + tmp13;
    tmp3 = tmp10 - tmp13;
    tmp1 = tmp11 + tmp12;
    tmp2 = tmp11 - tmp12;

    /* Odd part */

    z13 = warray[ctr8+5] + warray[ctr8+3];
    z10 = warray[ctr8+5] - warray[ctr8+3];
    z11 = warray[ctr8+1] + warray[ctr8+7];
    z12 = warray[ctr8+1] - warray[ctr8+7];

    tmp7 = z11 + z13;		/* phase 5 */
    tmp11 = ((z11 - z13) * FIX_1_414213562) >> 8; /* 2*c4 */

    z5 = ((z10 + z12) * FIX_1_847759065) >> 8; /* 2*c2 */
    tmp10 = ((z12 * FIX_1_082392200) >> 8) - z5; /* 2*(c2-c6) */
    tmp12 = ((z10 * - FIX_2_613125930) >> 8) + z5; /* -2*(c2+c6) */

    tmp6 = tmp12 - tmp7;	/* phase 2 */
    tmp5 = tmp11 - tmp6;
    tmp4 = tmp10 + tmp5;

    /* Final output stage: scale down by a factor of 8 and range-limit */

    outarray[ctr8+0] = ((tmp0 + tmp7) >> 5)+128;
    outarray[ctr8+7] = ((tmp0 - tmp7) >> 5)+128;
    outarray[ctr8+1] = ((tmp1 + tmp6) >> 5)+128;
    outarray[ctr8+6] = ((tmp1 - tmp6) >> 5)+128;
    outarray[ctr8+2] = ((tmp2 + tmp5) >> 5)+128;
    outarray[ctr8+5] = ((tmp2 - tmp5) >> 5)+128;
    outarray[ctr8+4] = ((tmp3 + tmp4) >> 5)+128;
    outarray[ctr8+3] = ((tmp3 - tmp4) >> 5)+128;
    }
  }

void JPGGetBlock (s16 vector[64], u16 HuffDCNum, u16 HuffACNum, u16 QuantNum, s16 *dcCoef)
   {
   s16 array2[64];
   s16 temp0;

   JPGeoi = 0;

   // Clear array2
   JPGClear128Bytes ((u32 *)&array2[0]);

   if (HuffDCNum)
      temp0 = JPGDecode(JPGHuffmanDC1);   // Get the DC coefficient
   else
      temp0 = JPGDecode(JPGHuffmanDC0);   // Get the DC coefficient
   *dcCoef += JPGReceiveBits(temp0);
   array2[0] = *dcCoef;

   JPGGetBlockBits(HuffACNum,(u32 *)&array2[0]);

   if (QuantNum)
      jpeg_idct_ifast (array2, vector, JPGQuantTable1);
   else
      jpeg_idct_ifast (array2, vector, JPGQuantTable0);

   }

u16 JPGGetHuffTables (void)
   {
   u16 HuffAmount[17]; //1-16
   u32 l0;
   u16 c0;
   u16 temp0;
   s16 temp1;
   u16 total;
   u16 i;
   u16 t0;
   s32 CurNum;
   u16 CurIndex;
   u16 j;

   l0 = JPGGetWord();
   c0 = 2;
   do
      {
      temp0 = JPGGetByte();
      c0++;
      t0 = (temp0 & 16) >> 4;
      temp0 &= 15;
      switch (t0)
         {
         case 0:        // DC Table
            total = 0;
            for (i=1; i<16+1; i++)
               {
               temp1 = JPGGetByte();
               c0++;
               total += temp1;
               HuffAmount[i] = temp1;
               }
            for (i=0; i<total; i++)
               {
               if (temp0)
                  JPGHuffmanDC1[i].Code = JPGGetByte();
               else
                  JPGHuffmanDC0[i].Code = JPGGetByte();
               c0++;
               }
            CurNum = 0;
            CurIndex = -1;
            for (i=1; i<16+1; i++)
               {
               for (j=1; j<HuffAmount[i]+1; j++)
                  {
                  CurIndex++;
                  if (temp0)
                     {
                     JPGHuffmanDC1[CurIndex].Index = CurNum;
                     JPGHuffmanDC1[CurIndex].Length = i;
                     }
                  else
                     {
                     JPGHuffmanDC0[CurIndex].Index = CurNum;
                     JPGHuffmanDC0[CurIndex].Length = i;
                     }
                  CurNum++;
                  }
               CurNum *= 2;
               }
            JPGDCTables++;
            break;
         case 1:
            total = 0;
            for (i=1; i<16+1; i++)
               {
               temp1 = JPGGetByte();
               c0++;
               total += temp1;
               HuffAmount[i] = temp1;
               }
            for (i=0; i<total; i++)
               {
               if (temp0)
                  JPGHuffmanAC1[i].Code = JPGGetByte();
               else
                  JPGHuffmanAC0[i].Code = JPGGetByte();
               c0++;
               }

            CurNum = 0;
            CurIndex = -1;
            for (i=1; i<16+1; i++)
               {
               for (j=1; j<HuffAmount[i]+1; j++)
                  {
                  CurIndex++;
                  if (temp0)
                     {
                     JPGHuffmanAC1[CurIndex].Index = CurNum;
                     JPGHuffmanAC1[CurIndex].Length = i;
                     }
                  else
                     {
                     JPGHuffmanAC0[CurIndex].Index = CurNum;
                     JPGHuffmanAC0[CurIndex].Length = i;
                     }
                  CurNum++;
                  }
               CurNum *= 2;
               }
            JPGACTables++;
            break;
         }
      }
   while (c0 < l0);

   return(1);
   }

u16 JPGGetImageAttr (void)
   {
   u32 temp4;
   u16 temp0;
   u16 temp1;
   u16 i;
   u16 id;

   temp4 = JPGGetWord();          //Length of segment
   temp0 = JPGGetByte();          // Data precision
   if (temp0 != 8)
      return(0);                  // we do not support 12 or 16-bit samples
   JPGImage.Rows = JPGGetWord();  // Image Height
   JPGImage.Cols = JPGGetWord();  // Image Width
   temp0 = JPGGetByte();          // Number of components
   for (i=1; i<temp0+1; i++)
      {
      id = JPGGetByte();
      switch (id)
         {
         case 1:
            temp1 = JPGGetByte();
            JPGImage.SamplesY = (temp1 & 15) * (temp1 >> 4);
            JPGImage.QuantTableY = JPGGetByte();
            break;
         case 2:
         case 3:
            temp1 = JPGGetByte();
            JPGImage.SamplesCbCr = (temp1 & 15) * (temp1 >> 4);
            JPGImage.QuantTableCbCr = JPGGetByte();
            break;
         }
      }
   return(1);
   }

u8 JPGGetQuantTables(void)
   {
   u32 l0 = JPGGetWord();
   u16 c0 = 2;
   u16 temp0;
   u16 xp;
   u16 yp;
   u16 i;
   u16 ZigIndex;

   do
      {
      temp0 = JPGGetByte();
      c0++;
      if (temp0 & 0xf0)
         return(0);        //we don't support 16-bit tables

      temp0 &= 15;
      ZigIndex = 0;
      xp = 0;
      yp = 0;
      for (i=0; i<64; i++)
         {
         xp = JPGZig1[ZigIndex];
         yp = JPGZig2[ZigIndex];
         ZigIndex++;
         /* For AA&N IDCT method, multipliers are equal to quantization
          * coefficients scaled by scalefactor[row]*scalefactor[col], where
          *   scalefactor[0] = 1
          *   scalefactor[k] = cos(k*PI/16) * sqrt(2)    for k=1..7
          */
         if (temp0)
            JPGQuantTable1[(xp<<3)+yp] = (JPGGetByte() * JPGaanscales[(xp<<3) + yp]) >> 12;
         else
            JPGQuantTable0[(xp<<3)+yp] = (JPGGetByte() * JPGaanscales[(xp<<3) + yp]) >> 12;

         c0++;
         }
      JPGQTables++;
      }
   while (c0 < l0);

   return(1);
   }

u16 JPGGetSOS (void)
   {
   u32 temp4;
   u16 temp0;
   u16 temp1;
   u16 temp2;
   u16 i;

   temp4 = JPGGetWord();
   temp0 = JPGGetByte();

   if ((temp0 != 1) && (temp0 != 3))
      return(0);
   JPGImage.NumComp = temp0;
   for (i=1; i<temp0+1; i++)
      {
      temp1 = JPGGetByte();
      switch (temp1)
         {
         case 1:
            temp2 = JPGGetByte();
            JPGImage.HuffACTableY = temp2 & 15;
            JPGImage.HuffDCTableY = temp2 >> 4;
            break;
         case 2:
            temp2 = JPGGetByte();
            JPGImage.HuffACTableCbCr = temp2 & 15;
            JPGImage.HuffDCTableCbCr = temp2 >> 4;
            break;
         case 3:
            temp2 = JPGGetByte();
            JPGImage.HuffACTableCbCr = temp2 & 15;
            JPGImage.HuffDCTableCbCr = temp2 >> 4;
            break;
         default:
            return(0);
         }
      }
   JPGfindex += 3;
   return(1);
   }

u32 gfxJpeg (u8 x0, u8 y0, u8 *data, u8 *vram)
   {
   u8 exit = 1;
   s16 y;
   u16 Restart = 0;
   u16 XPos; u16 YPos;
   s16 dcY; s16 dcCb; s16 dcCr;
   u16 mcu;
   s16 YVector1[64];              // 4 vectors for Y attribute
   s16 YVector2[64];              // (not all may be needed)
   s16 YVector3[64];
   s16 YVector4[64];

   u16 i,j;
   u16 xj;
   u16 yi;
   s16 r; s16 g; s16 b;
   u16 xindex; u16 yindex;

   JPGfindex = (u32)data;

   JPGQTables = 0;     // Initialize some checkpoint variables
   JPGACTables = 0;
   JPGDCTables = 0;

   //findex = 0;

   if (JPGGetByte() == 0xff)
      {
      if (JPGGetByte() == 0xd8)
         exit = 0;
      }

   // Exit if not a JPEG file
   if (exit)
      return(0);

   while (!exit)
      {
      if (JPGGetByte() == 0xff)
         {
         switch (JPGGetByte())
            {
            case 0x00: //not important
               break;
            case 0xc0: //SOF0
               JPGGetImageAttr();
               break;
            case 0xc1: //SOF1
               JPGGetImageAttr();
               break;
            case 0xc4: //DHT
               if ((JPGACTables < 2) || (JPGDCTables < 2))
                  JPGGetHuffTables();
               break;
            case 0xc9: //SOF9
               break;
            case 0xd9: //EOI
               exit = 1;
               break;
            case 0xda: //SOS
               JPGGetSOS();
               if ( ((JPGDCTables == 2) &&
                     (JPGACTables == 2) &&
                     (JPGQTables == 2)) ||
                     (JPGImage.NumComp == 1) )
                  {
                  JPGeoi = 0;
                  exit = 1;        // Go on to secondary control loop
                  }
               break;
            case 0xdb: //DQT
               if (JPGQTables < 2)
                  JPGGetQuantTables();
               break;
            case 0xdd: //DRI
               Restart = JPGGetWord();
               break;
            case 0xe0: //APP0
               (void) JPGGetWord();        // Length of segment
               JPGfindex += 5;
               (void) JPGGetByte();        // Major revision
               (void) JPGGetByte();        // Minor revision
               (void) JPGGetByte();        // Density definition
               (void) JPGGetByte();        // X density
               (void) JPGGetByte();        // Y density
               (void) JPGGetByte();        // Thumbnail width
               (void) JPGGetByte();        // Thumbnail height
               break;
            case 0xfe: //COM
               break;
            }
         }
      }

   XPos = 0;
   YPos = 0;                            // Initialize active variables
   dcY = 0; dcCb = 0; dcCr = 0;
   xindex = 0; yindex = 0; mcu = 0;
   r = 0; g = 0; b = 0;

   JPGXOrigin = x0;
   JPGYOrigin = y0;
   JPGcurBits = 128;             // Start with the seventh bit
   JPGcurByte = JPGGetByte();    // Of the first byte

   switch (JPGImage.NumComp)     // How many components does the image have?
     {
     case 3:                     // 3 components (Y-Cb-Cr)
       {
       switch (JPGImage.SamplesY)// What's the sampling ratio of Y to CbCr?
         {
         case 4:                 // 4 pixels to 1

           do                    // Process 16x16 blocks of pixels
             {
             JPGGetBlock (YVector1, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (YVector2, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (YVector3, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (YVector4, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (JPGCbVector, JPGImage.HuffDCTableCbCr, JPGImage.HuffACTableCbCr, JPGImage.QuantTableCbCr, &dcCb);
             JPGGetBlock (JPGCrVector, JPGImage.HuffDCTableCbCr, JPGImage.HuffACTableCbCr, JPGImage.QuantTableCbCr, &dcCr);
             // YCbCr vectors have been obtained

             JPGDraw8x8 ((u32 *)&YVector1[0], 0,0, (u32)vram);
             JPGDraw8x8 ((u32 *)&YVector2[0], 0,8, (u32)vram);
             JPGDraw8x8 ((u32 *)&YVector3[0], 8,0, (u32)vram);
             JPGDraw8x8 ((u32 *)&YVector4[0], 8,8, (u32)vram);
             xindex += 16;
             JPGXOrigin += 16;
             if (xindex >= JPGImage.Cols)
                {
                xindex = 0; yindex += 16; mcu = 1;
                JPGXOrigin = x0; JPGYOrigin += 16;
                }
             if ((mcu == 1) && (Restart != 0))    //Execute the restart interval
                {
                (void) JPGGetByte();
                (void) JPGGetByte();
                JPGcurByte = JPGGetByte();
                JPGcurBits = 128;
                dcY = 0; dcCb = 0; dcCr = 0; mcu = 0;  //Reset the DC value
                }
             }
//           while ((findex < flen) && (yindex < Image.Rows));
           while (yindex < JPGImage.Rows);
           break;
         case 2:           // 2 pixels to 1
           do
             {
             JPGGetBlock (YVector1, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (YVector2, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (JPGCbVector, JPGImage.HuffDCTableCbCr, JPGImage.HuffACTableCbCr, JPGImage.QuantTableCbCr, &dcCb);
             JPGGetBlock (JPGCrVector, JPGImage.HuffDCTableCbCr, JPGImage.HuffACTableCbCr, JPGImage.QuantTableCbCr, &dcCr);
             // YCbCr vectors have been obtained

             JPGDraw8x8 ((u32 *)&YVector1[0], 0,0, (u32)vram);
             JPGDraw8x8 ((u32 *)&YVector2[0], 0,8, (u32)vram);
             xindex += 16;
             if (xindex >= JPGImage.Cols)
               {
               xindex = 0; yindex += 8; mcu = 1;
               JPGXOrigin = x0; JPGYOrigin += 16;
               }
             if ((mcu == 1) && (Restart != 0))  // execute the restart interval
               {
               (void) JPGGetByte();
               (void) JPGGetByte();
               JPGcurByte = JPGGetByte();
               JPGcurBits = 128;
               dcY = 0; dcCb = 0; dcCr = 0; mcu = 0;
               }
             }
//           while ((findex < flen) && (yindex < Image.Rows));
           while (yindex < JPGImage.Rows);
           break;
         case 1:        // 1 pixel to 1
           do
             {
             JPGGetBlock (YVector1, JPGImage.HuffDCTableY,    JPGImage.HuffACTableY,    JPGImage.QuantTableY,    &dcY);
             JPGGetBlock (JPGCbVector, JPGImage.HuffDCTableCbCr, JPGImage.HuffACTableCbCr, JPGImage.QuantTableCbCr, &dcCb);
             JPGGetBlock (JPGCrVector, JPGImage.HuffDCTableCbCr, JPGImage.HuffACTableCbCr, JPGImage.QuantTableCbCr, &dcCr);
             // YCbCr vectors have been obtained

             JPGDraw8x8 ((u32 *)&YVector1[0], 0,0, (u32)vram);

             xindex += 8;
             if (xindex >= JPGImage.Cols)
               {
               xindex = 0; yindex += 8; mcu = 1;
               JPGXOrigin = x0; JPGYOrigin += 16;
               }
             if ((mcu == 1) && (Restart != 0))  // execute the restart interval
               {
               (void) JPGGetByte();
               (void) JPGGetByte();
               JPGcurByte = JPGGetByte();
               JPGcurBits = 128;
               dcY = 0; dcCb = 0; dcCr = 0; mcu = 0;
               }
             }
//           while ((findex < flen) && (yindex < Image.Rows));
           while (yindex < JPGImage.Rows);
           break;
         }  // Ratio
       }
     case 1:
       do
         {
         JPGGetBlock (YVector1, JPGImage.HuffDCTableY, JPGImage.HuffACTableY, JPGImage.QuantTableY, &dcY);
         // Y vector has been obtained

         for (i=0; i<8; i++)           // Draw 8x8 pixels
           for (j=0; j<8; j++)
             {
             y = YVector1[i*8+j];
             xj = xindex + j;
             yi = yindex + i;
             gfxPixel (xj + x0, yi + y0, RGB(y, y, y), (u32)vram);
             }

// Get setup to draw next block
         xindex += 8;
         if (xindex >= JPGImage.Cols)
           {
           xindex = 0; yindex += 8; mcu = 1;
           }

         if ((mcu == 1) && (Restart != 0))   // execute the restart interval
           {
           (void) JPGGetByte();
           (void) JPGGetByte();
           JPGcurByte = JPGGetByte();
           JPGcurBits = 128;
           dcY = 0; mcu = 0;
           }
         }
//       while ((findex <flen) && (yindex < Image.Rows));
       while (yindex < JPGImage.Rows);
       break;
     }

   return(1);
   }

