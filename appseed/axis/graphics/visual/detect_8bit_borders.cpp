#include "framework.h"


#define pixel(x, y) (ba[(pointer->m_rect.height() - (y) - 1) * iScan + (x)])


bool detect_8bit_borders(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex)
{

   COLORREF cr;

   COLORREF crBack = 0;

   ::count cTransparent = 0;

   bool bTransparent;

   ::count c = 0;

   int64_t iR = 0;

   int64_t iG = 0;

   int64_t iB = 0;

   int iLight = 0;

   int iDark = 0;

   // Roughly detect colors on transparency borders...

   // ... first, at horizontal orientation...

   for (index y = 0; y < pointer->m_dib->m_size.cy; y++)
   {

      bTransparent = true;

      cr = 0;

      for (index x = 0; x < pointer->m_dib->m_size.cx; x++)
      {

         index iIndex = pixel(x, y);

         index iNextIndex = -1;

         if (x < pointer->m_dib->m_size.cx - 1)
         {

            iNextIndex = pixel(x + 1, y);

         }

         if (iIndex >= cra.get_count())
         {

            continue;

         }

         if (bTransparent)
         {

            if (iIndex == transparentIndex)
            {

               cTransparent++;

               continue;

            }
            else
            {

               cr = cra[iIndex];

               bTransparent = false;

            }

         }
         else
         {

            if (iNextIndex == transparentIndex)
            {

               cr = cra[iIndex];

               bTransparent = true;

            }
            else
            {

               cr = cra[iIndex];

               continue;

            }

         }

         iR += argb_get_r_value(cr);

         iG += argb_get_g_value(cr);

         iB += argb_get_b_value(cr);

         c++;

      }

   }

   // ... then, at vertical orientation...

   for (index x = 0; x < pointer->m_dib->m_size.cx; x++)
   {

      bTransparent = true;

      cr = 0;

      for (index y = 0; y < pointer->m_dib->m_size.cy; y++)
      {

         index iIndex = pixel(x, y);

         index iNextIndex = -1;

         if (y < pointer->m_dib->m_size.cy - 1)
         {

            iNextIndex = pixel(x, y + 1);

         }

         if (iIndex >= cra.get_count())
         {

            continue;

         }

         if (bTransparent)
         {

            if (iIndex == transparentIndex)
            {

               continue;

            }
            else
            {

               cr = cra[iIndex];

               bTransparent = false;

            }

         }
         else
         {

            if (iNextIndex == transparentIndex)
            {

               cr = cra[iIndex];

               bTransparent = true;

            }
            else
            {

               cr = cra[iIndex];

               continue;

            }

         }

         iR += argb_get_r_value(cr);

         iG += argb_get_g_value(cr);

         iB += argb_get_b_value(cr);

         c++;

      }

   }

   // and if detected transparency, roughly calculate if average border color is dark or light.

   if (cTransparent <= 0)
   {

      crBack = ARGB(255, 127, 127, 127);

      pdiba->m_bTransparent = false;

   }
   else
   {

      byte bAverage = (byte)((iR + iG + iB) / (3 * c));

      double bLite = 127 + 63;

      double bDark = 127 - 63;

      if (bAverage > bLite) // Light
      {

         crBack = ARGB(255, 255, 255, 255);

         pdiba->m_bTransparent = true;

      }
      else if (bAverage < bDark)
      {

         crBack = ARGB(255, 0, 0, 0);

         pdiba->m_bTransparent = true;

      }
      else
      {

         crBack = ARGB(255, 127, 127, 127);

         pdiba->m_bTransparent = false;

      }


   }

   pdiba->m_crTransparent = crBack;

   return true;

}





