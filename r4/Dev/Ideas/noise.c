#include <math.h>

static int randtab[513] =
{
   23, 125, 161, 52, 103, 117, 70, 37, 247, 101, 203, 169, 124, 126, 44, 123, 
   152, 238, 145, 45, 171, 114, 253, 10, 192, 136, 4, 157, 249, 30, 35, 72, 
   175, 63, 77, 90, 181, 16, 96, 111, 133, 104, 75, 162, 93, 56, 66, 240, 
   8, 50, 84, 229, 49, 210, 173, 239, 141, 1, 87, 18, 2, 198, 143, 57, 
   225, 160, 58, 217, 168, 206, 245, 204, 199, 6, 73, 60, 20, 230, 211, 233, 
   94, 200, 88, 9, 74, 155, 33, 15, 219, 130, 226, 202, 83, 236, 42, 172, 
   165, 218, 55, 222, 46, 107, 98, 154, 109, 67, 196, 178, 127, 158, 13, 243, 
   65, 79, 166, 248, 25, 224, 115, 80, 68, 51, 184, 128, 232, 208, 151, 122, 
   26, 212, 105, 43, 179, 213, 235, 148, 146, 89, 14, 195, 28, 78, 112, 76, 
   250, 47, 24, 251, 140, 108, 186, 190, 228, 170, 183, 139, 39, 188, 244, 246, 
   132, 48, 119, 144, 180, 138, 134, 193, 82, 182, 120, 121, 86, 220, 209, 3, 
   91, 241, 149, 85, 205, 150, 113, 216, 31, 100, 41, 164, 177, 214, 153, 231, 
   38, 71, 185, 174, 97, 201, 29, 95, 7, 92, 54, 254, 191, 118, 34, 221, 
   131, 11, 163, 99, 234, 81, 227, 147, 156, 176, 17, 142, 69, 12, 110, 62, 
   27, 255, 0, 194, 59, 116, 242, 252, 19, 21, 187, 53, 207, 129, 64, 135, 
   61, 40, 167, 237, 102, 223, 106, 159, 197, 189, 215, 137, 36, 32, 22, 5, 
};

static float lerp(float a, float b, float t)
{
   return a + (b-a) * t;
}

static float grad(int hash, float x, float y, float z)
{
   switch (hash & 15) {
      case 12:
      case  0: return  x +  y;
      case 13:
      case  1: return -x +  y;
      case  2: return  x + -y;
      case  3: return -x + -y;
      case  4: return  x +  z;
      case  5: return -x +  z;
      case  6: return  x + -z;
      case  7: return -x + -z;
      case 14:
      case  8: return  y +  z;
      case  9: return -y +  z;
      case 15:
      case 10: return  y + -z;
      case 11: return -y + -z;
   }
   return 0; // this is unreachable, you stupid git
}

static void initPerlinNoise(void)
{
   int i;
   for (i=0; i < 256; ++i)
      randtab[i+256] = randtab[i];
}

float noise3(float x, float y, float z, int wrap)
{
   float u,v,w;
   unsigned int raw_mask = (wrap-1);
   unsigned int mask = raw_mask > 255 ? 255 : raw_mask;
   int px = floor(x);
   int py = floor(y);
   int pz = floor(z);
   int x0 = px & mask, x1 = (px+1) & mask;
   int y0 = py & mask, y1 = (py+1) & mask;
   int z0 = pz & mask, z1 = (pz+1) & mask;
   int rx0,rx1, r00,r01,r10,r11;

   if (!init) { init=1; initPerlineNoise(); }

   x -= px, y -= py, z -= pz;

   #define ease(a)   (((a*6-15)*a + 10) * a * a * a)
   u = ease(x), v = ease(y), w = ease(z);

   rx0 = randtab[x0];
   rx1 = randtab[x1];

   r00 = randtab[rx0+y0];
   r01 = randtab[rx0+y1];
   r10 = randtab[rx1+y0];
   r11 = randtab[rx1+y1];

   return lerp(lerp(lerp(grad(randtab[r00+z0], x  , y  , z   ),
                         grad(randtab[r10+z0], x-1, y  , z   ), u),
                    lerp(grad(randtab[r01+z0], x  , y-1, z   ),
                         grad(randtab[r11+z0], x-1, y-1, z   ), u), v),
               lerp(lerp(grad(randtab[r00+z1], x  , y  , z-1 ),
                         grad(randtab[r10+z1], x-1, y  , z-1 ), u),
                    lerp(grad(randtab[r01+z1], x  , y-1, z-1 ),
                         grad(randtab[r11+z1], x-1, y-1, z-1 ), u), v), w);
}
