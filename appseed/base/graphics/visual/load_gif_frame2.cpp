#include "framework.h"

bool gif_load_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex)
{


   bool bTransparent;

   COLORREF cr;

   COLORREF crBack = 0;

 
   int w = pointer->m_dib->m_iScan / sizeof(COLORREF);

   for (index y = 0; y < pointer->m_rect.height(); y++)
   {

      for (index x = 0; x < pointer->m_rect.width(); x++)
      {

         index iIndex = ba[x + y * iScan];
         index iPixel = (pointer->m_rect.height() - y - 1) * w + x;

         if (iIndex >= cra.get_count())
         {

            pointer->m_dib->m_pcolorref[iPixel] = 0;

            continue;

         }

         if (iIndex == transparentIndex)
         {

            pointer->m_dib->m_pcolorref[iPixel] = 0;

            continue;

         }

         cr = cra[iIndex];

         pointer->m_dib->m_pcolorref[iPixel] = cr;

      }

   }


   {

      if (uFrameIndex > 0 && pdiba->element_at(uFrameIndex - 1)->m_edisposal == ::visual::dib_sp::pointer::disposal_background)
      {

         pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         COLORREF crBack = pdiba->m_crBack;

         byte bAlpha = argb_get_a_value(crBack);

         if (bAlpha == 0)
         {

            crBack = 0;

         }
         else
         {

            output_debug_string("non zero alpha");

         }

         RECT r = pdiba->element_at(uFrameIndex - 1)->m_rect;

         pdibCompose->get_graphics()->FillSolidRect(r, crBack);

      }
      pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point pt = pointer->m_rect.top_left();

      ::size sz = pointer->m_rect.size();

      pdibCompose->get_graphics()->BitBlt(pt, sz, pointer->m_dib->get_graphics());

      pointer->m_dib->from(pdibCompose);

   }

   return true;

}