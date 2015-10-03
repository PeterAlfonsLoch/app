// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//
//#include "framework.h"

void swap(uint32_t * & p1,uint32_t * & p2)
{

   uint32_t * p = p1;
   p1 = p2;
   p2 = p;

}


void swap(vector4 * & p1,vector4 * & p2)
{

   vector4 * p = p1;
   p1 = p2;
   p2 = p;

}

inline void kernelPosition(int boxBlur,unsigned& std,int& dLeft,int& dRight)
{

   switch(boxBlur)
   {
   case 0:

      if(!(std % 2))
      {

         dLeft = std / 2 - 1;

         dRight = std - dLeft;

      }
      else
      {

         dLeft = std / 2;

         dRight = std - dLeft;

      }

      break;

   case 1:

      if(!(std % 2))
      {

         dLeft++;

         dRight--;

      }

      break;

   case 2:

      if(!(std % 2))
      {

         dRight++;

         std++;

}

      break;

   }

}



#ifdef __arm__

#include <arm_neon.h>

//namespace WebCore {


inline float32x4_t loadRGBA8AsFloat(uint32_t* source)
{

   uint32x2_t temporary1 ={0, 0};

   temporary1 = vset_lane_u32(*source,temporary1,0);

   uint16x4_t temporary2 = vget_low_u16(vmovl_u8(vreinterpret_u8_u32(temporary1)));

   return vcvtq_f32_u32(vmovl_u16(temporary2));

}

inline void storeFloatAsRGBA8(float32x4_t data,uint32_t* destination)
{

   uint16x4_t temporary1 = vmovn_u32(vcvtq_u32_f32(data));

   uint8x8_t temporary2 = vmovn_u16(vcombine_u16(temporary1,temporary1));

   *destination = vget_lane_u32(vreinterpret_u32_u8(temporary2),0);

}

//} // namespace WebCore

#endif // HAVE(ARM_NEON_INTRINSICS)

//#endif // NEONHelpers_h
namespace visual
{


   fastblur::fastblur(const ::aura::allocatorsp & allocer):
      dib_sp(allocer)
   {

      m_iRadius   = 0;
      m_size.cx   = 0;
      m_size.cy   = 0;

      vxmin       = NULL;
      vymin       = NULL;
      m_stack     = NULL;
      tsurface    = NULL;
      timage      = NULL;

   }


   bool fastblur::initialize(int32_t cx,int32_t cy,int32_t radius)
   {

      if(is_null())
         return false;

      if(m_p->m_size == size(cx,cy) && radius == m_iRadius)
         return true;

      if(cx + 100 > m_p->m_size.cx || cy + 100 > m_p->m_size.cy)
      {

         if(!m_p->create(cx + 100,cy + 100))
         {

            return false;

         }

#ifdef ANDROID

         if(m_dib.is_null())
         {

            m_dib.alloc(m_p->allocer());

         }

         if(!m_dib->create(cx + 100,cy + 100))
         {

            return false;

         }

#endif
#ifdef _WIN32
#if OSBIT == 32

         if(vxmin != NULL)
         {
            delete[] vxmin;
            vxmin = NULL;
         }
         if(vymin != NULL)
         {
            delete[] vymin;
            vymin = NULL;
         }
         if(m_stack != NULL)
         {
            delete[] m_stack;
            m_stack = NULL;
         }
         if(tsurface != NULL)
         {
            delete[] tsurface;
            tsurface = NULL;
         }
         if(timage != NULL)
         {
            delete[] timage;
            timage = NULL;
         }



         const int wh = (cx+ 100 + 16)*(cy + 100 + 16);
#undef new 
         timage = new vector4[wh];
         // temporary output space for first pass.
         tsurface = new vector4[wh];

         const int div2 = (radius * 2) + 1;
         m_stack = new vector4[div2];
#define new AURA_NEW
         // lookup table for clamping pixel offsets
         // as the kernel passes the right (or lower) edge
         // of the input data
         vxmin = new int[cx + 100 + 16];
         vymin = new int[cy + 100 + 16];
#endif
#endif

      }


      const int r1 = radius + 1;
      int wm = cx - 1;
      int c = cx + 16;
      for(index x = 0; x < c; x++)
      {
         vxmin[x] = MIN(x + r1,wm);
      }
      int hm = cy - 1;
      c = cy + 16;
      int s = cx;
      if(s % 16 > 0)
      {
         s = ((s / 16) * 16) + 16;
      }
      for(index y = 0; y < c; y++)
      {
         vymin[y] = MIN(y + r1,hm)*s;
      }


      m_p->m_iHeight = cy;

      //      int32_t h         = cy;
        //    int32_t scan      = m_p->scan;
      int32_t div       = radius + radius + 1;
      m_iRadius         = radius;
      m_uchaDiv.allocate(256 * div);
      byte * dv         = m_uchaDiv.get_data();

      m_size.cx         = cx;
      m_size.cy         = cy;

      for(int32_t i = 0; i < m_uchaDiv.get_count(); i++)
      {

         dv[i]= MIN(255,i / div);

      }

      m_p->map();

      int area = m_p->m_iScan * m_p->m_size.cy;

      m_ucha.allocate(area);

      //      area /= sizeof(COLORREF);

      //      m_uchaR.allocate(area);

      //      m_uchaG.allocate(area);

      //      m_uchaB.allocate(area);

      //      m_uchaA.allocate(area);

      //      int s = m_p->m_iScan / sizeof(COLORREF);

        //    int maxsh = MAX(s, m_size.cy);

          //  m_iaVmin.allocate(maxsh);

            //m_iaVmax.allocate(maxsh);

      return true;

   }


   bool fastblur::initialize(size sz,int32_t iRadius)
   {

      return initialize(sz.cx,sz.cy,iRadius);

   }



   bool fastblur::blur(int cx,int cy)
   {

      if(cx < 0 || cx > m_p->m_size.cx)
      {

         cx = m_p->m_size.cx;

      }

      if(cy < 0 || cy > m_p->m_size.cy)
      {

         cy = m_p->m_size.cy;

      }

      //synch_lock ml(&user_mutex());

      m_p->map();

      bool b = false;

      int bottomup;

#ifdef APPLEOS
      bottomup = 1;
#else
      bottomup = 0;
#endif


#if defined(_WIN32) && OSBIT == 32

#ifdef DO_BOX_BLUR

      uint32_t * pdata = (uint32_t *) m_p->get_data();

      byte * p;
      vector4 * t = timage;

      int w = m_size.cx;
      int h = m_size.cy;

      int s = m_p->m_iScan / 4;

      {

         DWORD dwA0 = get_tick_count();

         for(index y = 0; y < h; y++)
         {
            for(index x = 0; x < w; x++)
            {
               p = (byte *)&pdata[y * s + x];
               t[y * w + x] = vector4(p[0],p[1],p[2],p[3]);
            }
         }

         DWORD dwA1 = get_tick_count();
         DWORD dwA2 = dwA1 - dwA0;
         string str;

         str.Format("%d",dwA2);

      }



      {

         DWORD dw1 = get_tick_count();

         try
         {

            b = do_boxblur(
               timage,
               w,
               h,
               m_iRadius,
               (uint32_t *)m_ucha.get_data(),
               m_uchaDiv.get_data(),
               w * 4,
               w,h,bottomup);

         }
         catch(...)
         {

         }

         DWORD dw2 = get_tick_count();
         DWORD dw3 = dw2 - dw1;
         
         string str1;
         str1.Format("| Parameters: w=%d h=%d r=%d  \n",w,h,m_iRadius);
         string str2;
         str2.Format("| time for calculating box blur : %d\b",dw3);

         output_debug_string("/-----------------------------------------\n");
         output_debug_string("| \n");
         output_debug_string(str1);
         output_debug_string(str2);
         output_debug_string("| \n");

         ::aura::application * papp = m_p->m_pauraapp;
         APPTRACE("/--------------------------------");
         APPTRACE("| fastblur::blur");
         APPTRACE("| ");
         APPTRACE("| do_fastblur = %d ms",dw3);
      }

      {

         DWORD dwC0 = get_tick_count();

         for(index y = 0; y < h; y++)
         {
            for(index x = 0; x < w; x++)
            {
               p = (byte *)&pdata[y * s + x];
               t = &timage[y * w + x];
               p[0] = (byte)t->w;
               p[1] = (byte)t->x;
               p[2] = (byte)t->y;
               p[3] = (byte)t->z;
            }
         }

         DWORD dwC1 = get_tick_count();
         DWORD dwC2 = dwC1 - dwC0;
         string str;

         str.Format("%d",dwC2);
   }
#else
   uint32_t * pdata = (uint32_t *)m_p->get_data();

   byte * p;
   vector4 * t = timage;

   int w = m_size.cx;
   int h = m_size.cy;
   int wj = w; // w job
   int hj = h; // h job

   if(wj % 16 > 0)
   {
      wj = ((wj / 16) * 16) + 16;
   }

   int s = m_p->m_iScan / 4;

   {

      DWORD dwA0 = get_tick_count();

      for(index y = 0; y < hj; y++)
      {
         for(index x = 0; x < wj; x++)
         {
            p = (byte *)&pdata[y * s + x];
            t[y * wj + x] = vector4(p[0],p[1],p[2],p[3]);
         }
      }

      DWORD dwA1 = get_tick_count();
      DWORD dwA2 = dwA1 - dwA0;
      string str;

      str.Format("%d",dwA2);

   }


   DWORD dw1;
   DWORD dw2;
   DWORD dw3;
   {

      dw1 = get_tick_count();

      try
      {

         b = do_stackblur(
            timage,
            wj,
            hj,
            m_iRadius,
            (uint32_t *)m_ucha.get_data(),
            m_uchaDiv.get_data(),
            w * 4,
            w,h,bottomup);

      }
      catch(...)
      {

      }

      dw2 = get_tick_count();
      dw3 = dw2 - dw1;

      string str1;
      str1.Format("| Parameters: w=%d h=%d r=%d  \n", wj, hj, m_iRadius);
      string str2;
      str2.Format("| time for calculating stack blur : %d\b",dw3);
      
      output_debug_string("/-----------------------------------------\n");
      output_debug_string("| \n");
      output_debug_string(str1);
      output_debug_string(str2);
      output_debug_string("| \n");

      ::aura::application * papp = m_p->m_pauraapp;
      APPTRACE("/--------------------------------");
      APPTRACE("| fastblur::blur");
      APPTRACE("| ");
      APPTRACE("| do_fastblur = %d ms",dw3);
   }

   {

      DWORD dwC0 = get_tick_count();

      for(index y = 0; y < h; y++)
      {
         for(index x = 0; x < w; x++)
         {
            p = (byte *)&pdata[y * s + x];
            t = &timage[y * wj + x];
            p[0] = (byte)t->w;
            p[1] = (byte)t->x;
            p[2] = (byte)t->y;
            p[3] = (byte)t->z;
         }
      }

      DWORD dwC1 = get_tick_count();
      DWORD dwC2 = dwC1 - dwC0;
      string str;

      str.Format("%d",dwC2);
   }

#endif

#else


DWORD dw1 = get_tick_count();

#ifdef __arm__

#else

//      ::count cCount = MAX(2,m_iRadius / 8);

      ::count cCount = 2;

     for(index i = 0; i < cCount; i++)
#endif
      {
         try
         {

            b = do_fastblur(
               (uint32_t *)m_p->get_data(),
               m_size.cx,
               m_size.cy,
               m_iRadius,
               (uint32_t *)m_ucha.get_data(),
               m_uchaDiv.get_data(),
               m_p->m_iScan,
               cx,cy,bottomup);

         }
         catch(...)
         {

         }

      }

          DWORD dw2 = get_tick_count();
     DWORD dw3 = dw2 - dw1;
     string str1;
     str1.Format("| Parameters: w=%d h=%d r=%d  \n",m_size.cx,m_size.cy,m_iRadius);
     string str2;
     str2.Format("| time for calculating fast blur : %d\b",dw3);

     output_debug_string("/-----------------------------------------\n");
     output_debug_string("| \n");
     output_debug_string(str1);
     output_debug_string(str2);
     output_debug_string("| \n");

     ::aura::application * papp = m_p->m_pauraapp;
     APPTRACE("/--------------------------------");
     APPTRACE("| fastblur::blur");
     APPTRACE("| ");
     APPTRACE("| do_fastblur = %d ms",dw3);

#endif


      return b;

   }

#ifdef __arm__


   inline void boxBlurNEON(uint32_t* sourcePixel,uint32_t* destinationPixel,
      unsigned dx,int dxLeft,int dxRight,int stride,int strideLine,int effectWidth,int effectHeight)
   {

      float32x4_t deltaX = vdupq_n_f32(1.0 / dx);

      int pixelLine = strideLine / 4;

      int pixelStride = stride / 4;

      int strideRight = dxRight * pixelStride;

      int strideLeft = dxLeft * pixelStride;

      int dxW = effectWidth - dxRight;

      int x;

      int pixelOffset;

      if(dxLeft > dxW)
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            float32x4_t sum = vdupq_n_f32(0);

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + line + i * pixelStride);

               sum = vaddq_f32(sum,sourcePixelAsFloat);

            }

            // Blurring

            for(x = 0; x < effectWidth; x++)
            {

               pixelOffset = line + x * pixelStride;

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               if(x >= dxLeft)
               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_f32(sum,sourcePixelAsFloat);

               }

               if(x <= dxW)
               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_f32(sum,sourcePixelAsFloat);

               }

            }

         }

      }
      else
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            float32x4_t sum = vdupq_n_f32(0);

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + line + i * pixelStride);

               sum = vaddq_f32(sum,sourcePixelAsFloat);

            }

            // Blurring
            x = 0;

            pixelOffset = line;

            for(; x < dxLeft; x++)
            {

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_f32(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }

            for(; x <= dxW; x++)
            {

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_f32(sum,sourcePixelAsFloat);

               }

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset + strideRight);

                  sum = vaddq_f32(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }


            for(; x < effectWidth; x++)
            {

               float32x4_t result = vmulq_f32(sum,deltaX);

               storeFloatAsRGBA8(result,destinationPixel + pixelOffset);

               {

                  float32x4_t sourcePixelAsFloat = loadRGBA8AsFloat(sourcePixel + pixelOffset - strideLeft);

                  sum = vsubq_f32(sum,sourcePixelAsFloat);

               }

               pixelOffset += pixelStride;

            }

         }

      }

   }


   bool fastblur::do_fastblur(uint32_t * pdata,int32_t w,int32_t h,int32_t radius,uint32_t * prgba,byte * dv,int32_t stride,int cx,int cy,int bottomup)
   {

      //int stride = 4 * cx;
      int dxLeft = 0;
      int dxRight = 0;
      int dyLeft = 0;
      int dyRight = 0;
      uint32_t* src = pdata;
      uint32_t* dst = m_dib->m_pcolorref;
      unsigned int kernelSizeX = radius * 3 / 2 + 1;
      unsigned int kernelSizeY = radius * 3 / 2 + 1;

      for(int i = 0; i < 3; ++i)
      {

         if(kernelSizeX)
         {

            kernelPosition(i,kernelSizeX,dxLeft,dxRight);

            boxBlurNEON(src,dst,kernelSizeX,dxLeft,dxRight,4,stride,cx,cy);

            swap(src,dst);

         }

         if(kernelSizeY)
         {

            kernelPosition(i,kernelSizeY,dyLeft,dyRight);

            boxBlurNEON(src,dst,kernelSizeY,dyLeft,dyRight,stride,4,cy,cx);

            swap(src,dst);

         }

      }

      // The final result should be stored in srcPixelArray.
      if(dst != pdata)
      {

         memcpy(pdata,dst,m_p->m_iScan * m_p->m_size.cy);

      }

   }

#else

#if OSBIT == 32

   inline void boxBlurSSE(vector4* sourcePixel,vector4* destinationPixel,
      unsigned dx,int dxLeft,int dxRight,int stride,int strideLine,int effectWidth,int effectHeight)
   {

      vector4 deltaX = vector4(1.0 / dx,1.0 / dx,1.0 / dx,1.0 / dx);

      int pixelLine = strideLine / 4;

      int pixelStride = stride / 4;

      int strideRight = dxRight * pixelStride;

      int strideLeft = dxLeft * pixelStride;

      int dxW = effectWidth - dxRight;

      int x;

      int pixelOffset;

      if(dxLeft > dxW)
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            vector4 sum = vector4();

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               sum += sourcePixel[line + i*pixelStride];

            }

            // Blurring

            for(x = 0; x < effectWidth; x++)
            {

               pixelOffset = line + x * pixelStride;

               destinationPixel[pixelOffset] = sum * deltaX;

               if(x >= dxLeft)
               {

                  sum -= sourcePixel[pixelOffset - strideLeft];

               }

               if(x <= dxW)
               {

                  sum += sourcePixel[pixelOffset + strideRight];

               }

            }

         }

      }
      else
      {

         for(int y = 0; y < effectHeight; ++y)
         {

            int line = y * pixelLine;

            vector4 sum = vector4();

            // Fill the kernel
            int maxKernelSize = MIN(dxRight,effectWidth);

            for(int i = 0; i < maxKernelSize; ++i)
            {

               sum += sourcePixel[line + i*pixelStride];

            }

            // Blurring
            x = 0;

            pixelOffset = line;

            for(; x < dxLeft; x++)
            {

               destinationPixel[pixelOffset] = sum * deltaX;

               {

                  sum += sourcePixel[pixelOffset + strideRight];

               }

               pixelOffset += pixelStride;

            }

            for(; x <= dxW; x++)
            {

               destinationPixel[pixelOffset] = sum * deltaX;

               {

                  sum -= sourcePixel[pixelOffset - strideLeft];

               }

               {

                  sum += sourcePixel[pixelOffset + strideRight];

               }

               pixelOffset += pixelStride;

            }


            for(; x < effectWidth; x++)
            {

               destinationPixel[pixelOffset] = sum * deltaX;

               {

                  sum -= sourcePixel[pixelOffset - strideLeft];

               }

               pixelOffset += pixelStride;

            }

         }

      }

   }

   // https://gist.github.com/benjamin9999/3809142

   /*
   * "stackblur"
   * originally, Mario Klingemann, mario@quasimondo.com
   * this implementation, Benjamin Yates (benjamin@rqdq.com)
   * http://incubator.quasimondo.com/processing/stackblur.pde
   *
   * this blur routine seems to be quite popular.
   *
   * unfortunately, mario didn't comment anything.
   * but, it's easy to see it's just a flavor of a two-pass
   * sliding box kernel.
   *
   * this version is vectorized for float32 r/g/b/a using sse
   *
   * vector4() is just a class wrapping _mm_zzz_ps() family of SSE intrinsics
   * ( if you need one, start here:
   *  - http://fastcpp.blogspot.com/2011/12/simple-vector3-class-with-sse-support.html )
   *
   * radius is in (whole) pixels
   *
   */

   void fastblur::stackblur(vector4* pix,const int w,const int h,const int radius)
   {

      if(radius < 1) return;	// nothing to do

                              // some values for convenience
                              //const int w = image.width;
                              //const int h = image.height;
      const int wm = w - 1;
      const int hm = h - 1;
      const int wh = w*h;
      const int r1 = radius + 1;

      // number of divisions in the kernel
      // D(-r), D(-r+1), ... D(0), ... D(r-1), D(r)
      const int div = (radius * 2) + 1;

      // temporary output space for first pass.
      //vector4* tsurface = new vector4[wh];

      // lookup table for clamping pixel offsets
      // as the kernel passes the right (or lower) edge
      // of the input data
      //int* const vmin = new int[max(w,h)];

      // calculate divisor for pulling an output from the kernel
      //   the kernel is pyramid shaped.
      //   to understand this divisor, imagine a cross-section
      //   of the center of the pyramid.
      //   (or ask mario to document it better)
      //
      // I store the reciprocal in the vector to
      // mul_ps later instead of div_ps
      int divsumi = (div + 1) >> 1;
      divsumi *= divsumi;
      const vector4 divsum(1.0f / (float)divsumi);

      // kernel pixel data "stack"
      // which works more like a ring-buffer,
      // where the pointer is advanced each iteration, modulo #divisions
      vector4* stack = m_stack;
      int stackpointer;
      int stackstart;



      // input/output offsets.
      // they are discrete because the source can be non-square
      int yw = 0;	// current read offset in source
      int yi = 0; // current write offset in destination


                  // blur horizontally, output to temporary buffer
      for(int y=0; y<h; y++) {

         vector4 insum(0.f);
         vector4 outsum(0.f);
         vector4 sum(0.f);

         // preload the kernel(stack)
         // pixels before the left edge of the image are
         // samples of [0] (max()).  min() handles
         // images which are smaller than the kernel.
         for(int i=-radius; i <= radius; i++) {

            // calcualte address of source pixel
            const vector4& p = pix[yi + MIN(wm,MAX(i,0))];

            // put pixel in the stack
            vector4& sir = stack[i + radius];
            sir = p;

            // rbs is a weight from (1)...(radius+1)...(1)
            const int rbs = r1 - abs(i);

            // add pixel to accumulators
            sum += sir * rbs;
            if(i > 0) { insum  += sir; }
            else { outsum += sir; }
         }


         // now that the kernel is preloaded
         // stackpointer is the index of the center of the kernel
         stackpointer = radius;


         // now start outputing pixels
         for(int x=0; x<w; x++) {

            // output a pixel
            tsurface[yi] = sum * divsum;


            // calculate address of the next pixel
            // to add to the kernel
            //
            // on first pass, make a lut to handle access
            // past the right edge of the width image.
            // min() will cause the last pixel to repeat.
            //if(y == 0) vmin[x] = min(x + radius + 1,wm);
            //vector4& p = pix[yw + vmin[x]];
            vector4& p = pix[yw + vxmin[x]];


            // remove "past" pixels from the sum
            sum -= outsum;


            // remove "left" side of stack from outsum
            stackstart = stackpointer - radius + div;
            vector4& sir = stack[stackstart % div];
            outsum -= sir;

            // now this (same) stack entry is the "right" side
            // add new pixel to the stack, and update accumulators
            sir = p;
            insum += sir;
            sum += insum;


            // slide kernel one pixel ahead (right),
            // update accumulators again
            stackpointer = (stackpointer + 1) % div;
            const vector4& sirnext = stack[stackpointer];
            outsum += sirnext;
            insum -= sirnext;

            yi++;	// advance output offset to next pixel
         }
         yw += w;	// advance input offset to next line
      }//y loop



       // now blur vertically from the temporary
       // buffer, using the original image buffer
       // as the output
      for(int x=0; x<w; x++) {

         vector4 insum(0);
         vector4 outsum(0);
         vector4 sum(0);

         //preload the stack
         int yp = -radius * w;
         for(int i = -radius; i <= radius; i++) {

            vector4& sir = stack[i + radius];

            yi = MAX(0,yp) + x;
            const vector4& p = tsurface[yi];

            sir = p;

            const int rbs = r1 - abs(i);
            sum += sir * rbs;
            if(i > 0) { insum  += sir; }
            else { outsum += sir; }

            // only advance to the next row if there
            // are still more rows of image left.
            // otherwise, we keep sampling the same row
            // as if the bottom line was duplicated
            if(i < hm) yp += w;

         }//preload

         stackpointer = radius;

         // this loop is the same as the y-loop,
         // except the src/dest offsets are calcuated differently
         yi = x;	// set starting output offset by column
         for(int y=0; y<h; y++) {

            pix[yi] = sum * divsum;

            stackstart = stackpointer - radius + div;
            vector4& sir = stack[stackstart % div];
            sum -= outsum;
            outsum -= sir;

            //if(x == 0) vmin[y] = min(y + r1,hm)*w;
            //sir = tsurface[x + vmin[y]];
            sir = tsurface[x + vymin[y]];

            insum += sir;
            sum += insum;

            stackpointer = (stackpointer + 1) % div;
            const vector4& sirnext = stack[stackpointer];
            outsum += sirnext;
            insum -= sirnext;

            yi += w; // advance output offset to next line
         }
      }//x loop
   }


   bool fastblur::do_boxblur(vector4 * pimage,int32_t w,int32_t h,int32_t radius,uint32_t * prgba,byte * dv,int32_t stride,int cx,int cy,int bottomup)
   {

      int dxLeft = 0;
      int dxRight = 0;
      int dyLeft = 0;
      int dyRight = 0;
      vector4* src = pimage;
      vector4* dst = tsurface;
      unsigned int kernelSizeX = radius * 3 / 2 + 1;
      unsigned int kernelSizeY = radius * 3 / 2 + 1;

      for(int i = 0; i < 3; ++i)
      {

         if(kernelSizeX)
         {

            kernelPosition(i,kernelSizeX,dxLeft,dxRight);

            boxBlurSSE(src,dst,kernelSizeX,dxLeft,dxRight,4,stride,w,h);

            swap(src,dst);

         }

         if(kernelSizeY)
         {

            kernelPosition(i,kernelSizeY,dyLeft,dyRight);

            boxBlurSSE(src,dst,kernelSizeY,dyLeft,dyRight,stride,4,h,w);

            swap(src,dst);

         }

      }

      // The final result should be stored in srcPixelArray.
      if(dst != pimage)
      {

         memcpy(pimage,dst,m_p->m_iScan * m_p->m_size.cy);

      }


      return true;

   }

   bool fastblur::do_stackblur(vector4 * pimage,int32_t w,int32_t h,int32_t radius,uint32_t * prgba,byte * dv,int32_t stride,int cx,int cy,int bottomup)
   {

      stackblur(pimage,w,h,radius);

      return true;

   }


   #endif



   bool fastblur::do_fastblur(uint32_t * pdata,int32_t w,int32_t h,int32_t radius,uint32_t * prgba,byte * dv,int32_t stride,int cx,int cy,int bottomup)
   {

      if(radius <= 0)
      {

         return false;

      }

      int32_t rsum,gsum,bsum,asum;
      int32_t x;
      int32_t y;
      int32_t i;
      int32_t yp;
      int32_t yw;
      byte * p1;
      byte * p2;
      int32_t wm = w - 1;
      //      int32_t hm = h - 1;
      int32_t wr = MIN(w,cx) - 1 - radius;
      int32_t hr = MIN(h,cy) - 1 - radius;
      //   int32_t div        = radius + radius + 1;
      byte * p;

      yw = 0;

      h = MIN(h,cy);

      w = MIN(w,cx);

      if(bottomup)
      {

         pdata = (uint32_t *)(((byte *)pdata) + (stride * (cy - h)));

         prgba = (uint32_t *)(((byte *)prgba) + (stride * (cy - h)));

      }

      int dir;

      if(bottomup)
      {

         dir = -1;

      }
      else
      {

         dir = 1;

      }

      int32_t * pix = (int32_t *)pdata;
      byte * pb = (byte *)pdata;
      byte * pwork = (byte *)prgba;
      byte * pwk = (byte *)prgba;

      for(y = 0; y < h; y++)
      {

         pwork = &pwk[stride * y];

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         for(i = -radius; i <= radius; i++)
         {

            p = &pb[yw + (MIN(wm,MAX(i,0)) * 4)];
            rsum += p[0];
            gsum += p[1];
            bsum += p[2];
            asum += p[3];

         }

         p1 = &pb[yw + (radius + 1) * 4];
         p2 = &pb[yw];

         for(x = 0; x < radius; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];

            rsum += p1[0] - p2[0];
            gsum += p1[1] - p2[1];
            bsum += p1[2] - p2[2];
            asum += p1[3] - p2[3];

            pwork += 4;
            p1 += 4;

         }

         for(; x < wr; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += p1[0] - p2[0];
            gsum += p1[1] - p2[1];
            bsum += p1[2] - p2[2];
            asum += p1[3] - p2[3];

            p1 += 4;
            p2 += 4;
            pwork += 4;

         }

         p1 -= 4;

         for(; x < w; x++)
         {

            pwork[0] = dv[rsum];
            pwork[1] = dv[gsum];
            pwork[2] = dv[bsum];
            pwork[3] = dv[asum];


            rsum += p1[0] - p2[0];
            gsum += p1[1] - p2[1];
            bsum += p1[2] - p2[2];
            asum += p1[3] - p2[3];

            p2 += 4;
            pwork += 4;

         }

         yw += stride;

      }

      for(x = 0; x < w; x++)
      {

         asum = 0;
         rsum = 0;
         gsum = 0;
         bsum = 0;

         yp = -radius * stride;

         for(i = -radius; i <= radius; i++)
         {
            p = &pwk[MAX(0,yp) + x * 4];
            rsum += p[0];
            gsum += p[1];
            bsum += p[2];
            asum += p[3];
            yp += stride;
         }

         byte * r1 = &pwk[(x * 4) + (radius + 1) * stride];
         byte * r2 = &pwk[(x * 4)];

         p1 = (byte *)&pix[x];

         for(y = 0; y < radius; y++)
         {

            p1[0] = dv[rsum];
            p1[1] = dv[gsum];
            p1[2] = dv[bsum];
            p1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            p1 += stride;
            r1 += stride;

         }

         for(; y < hr; y++)
         {

            p1[0] = dv[rsum];
            p1[1] = dv[gsum];
            p1[2] = dv[bsum];
            p1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            p1 += stride;
            r1 += stride;
            r2 += stride;

         }

         p1 -= stride;
         r1 -= stride;

         for(; y < h; y++)
         {

            p1[0] = dv[rsum];
            p1[1] = dv[gsum];
            p1[2] = dv[bsum];
            p1[3] = dv[asum];

            rsum += r1[0] - r2[0];
            gsum += r1[1] - r2[1];
            bsum += r1[2] - r2[2];
            asum += r1[3] - r2[3];

            p1 += stride;
            r2 += stride;

         }

      }

      return true;

   }

#endif

   bool fastblur::do_fastblur(uint32_t * pix,int32_t w,int32_t h,int32_t radius,byte * r,byte * g,byte * b,byte * a,byte * dv,int32_t stride,int32_t * vmin,int32_t * vmax,int cx,int cy,int bottomup)
   {

      return false;

      /*

            if (radius <= 0)
            {

               return false;

            }

            int32_t asum, rsum, gsum, bsum, x, y, i, yp, yi, yw;
            int32_t s = stride / sizeof(COLORREF);
            int32_t wm = w - 1;
            int32_t hm = h - 1;
            int32_t div = radius + radius + 1;
            int32_t p;
            int32_t p1;
            int32_t p2;

            yw = yi = 0;

            for (x = 0; x < w; x++)
            {
               vmin[x] = MIN(x + radius + 1, wm);
               vmax[x] = MAX(x - radius, 0);
            }

            for (y = 0; y < h; y++)
            {
               asum = rsum = gsum = bsum = 0;
               yi = y * s;
               for (i = -radius; i <= radius; i++)
               {
                  p = pix[yi + MIN(wm, MAX(i, 0))];
                  asum += ((p & 0xff000000) >> 24);
                  rsum += ((p & 0xff0000) >> 16);
                  gsum += ((p & 0x00ff00) >> 8);
                  bsum += (p & 0x0000ff);
               }
               for (x = 0; x < w; x++)
               {
                  a[yi] = dv[asum];
                  r[yi] = dv[rsum];
                  g[yi] = dv[gsum];
                  b[yi] = dv[bsum];

                  p1 = pix[yw + vmin[x]];
                  p2 = pix[yw + vmax[x]];

                  asum += ((p1 >> 24) & 0xff) - ((p2 >> 24) & 0xff);
                  rsum += ((p1 & 0x00ff0000) - (p2 & 0x00ff0000)) >> 16;
                  gsum += ((p1 & 0x0000ff00) - (p2 & 0x0000ff00)) >> 8;
                  bsum += ((p1 & 0x000000ff) - (p2 & 0x000000ff));
                  yi++;
               }
               yw += s;
            }
            for (y = 0; y < h; y++)
            {
               vmin[y] = MIN(y + radius + 1, hm) * s;
               vmax[y] = MAX(y - radius, 0) * s;
            }

            for (x = 0; x < w; x++)
            {
               asum = rsum = gsum = bsum = 0;
               yp = -radius*s;
               for (i = -radius; i <= radius; i++)
               {
                  yi = MAX(0, yp) + x;
                  rsum += r[yi];
                  gsum += g[yi];
                  bsum += b[yi];
                  asum += a[yi];
                  yp += s;
               }
               yi = x;
               for (y = 0; y < h; y++)
               {
                  pix[yi] = (dv[asum] << 24) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];

                  p1 = x + vmin[y];
                  p2 = x + vmax[y];

                  rsum += r[p1] - r[p2];
                  gsum += g[p1] - g[p2];
                  bsum += b[p1] - b[p2];
                  asum += a[p1] - a[p2];

                  yi += s;

               }

            }

            return true;

      */

   }







} // namespace visual
