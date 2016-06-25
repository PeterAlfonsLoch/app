#include "framework.h"

#define unequal(a, b, n) ((a) > (b) - (n))

#define pixel(x, y) (ba[(pointer->m_rect.height() - (y) - 1) * iScan + (x)])

bool detect_8bit_borders(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool antialias_8bit(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool gif_draw_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool gif_load_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex)
{

   pointer->m_dib->map();

   COLORREF crBack = 0;

   if (uFrameIndex <= 0)
   {

      detect_8bit_borders(pdibCompose, pdiba, pointer, uFrameIndex, ba, iScan, cra, transparentIndex);
   
   }

   pointer->m_bTransparent = pdiba->m_bTransparent;

   if (pdiba->m_bTransparent)
   {

      gif_draw_frame(pdibCompose, pdiba, pointer, uFrameIndex, ba, iScan, cra, transparentIndex);
      
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

         ::rect r = pdiba->element_at(uFrameIndex - 1)->m_rect;

         r.offset(5, 5);

         pdibCompose->get_graphics()->FillSolidRect(r, crBack);

      }

      pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point pt = pointer->m_rect.top_left();

      ::size sz = pointer->m_rect.size();

      pdibCompose->get_graphics()->BitBlt(pt + point(5, 5), sz, pointer->m_dib->get_graphics());

      pointer->m_dib->from(pdibCompose);

      if (pointer->m_bTransparent)
      {

         crBack = pdiba->m_crTransparent;

         pdiba->m_iTransparentIndex = transparentIndex;

         pdiba->m_bTransparent = true;

      }
      else
      {

         crBack = pointer->m_crTransparent;

         size s = pointer->m_dib->m_size;

         int cx = s.cx;

         int cy = s.cy;

         if (pointer->m_rect.size() == pdiba->m_size)
         {

            if (pixel(0, 0) == pixel(cx - 1, 0)) // && pointer->m_rect.left == 0 && pointer->m_rect.top == 0 && pointer->m_rect.right == pdiba->m_size.cx)
            {

               transparentIndex = pixel(0, 0);

               pdiba->m_iTransparentIndex = transparentIndex;

            }
            else if (pixel(0, cy - 1) == pixel(cx - 1, cy - 1))// && pointer->m_rect.left == 0 && pointer->m_rect.bottom == pdiba->m_size.cy && pointer->m_rect.right == pdiba->m_size.cx)
            {

               transparentIndex = pixel(0, cy - 1);

               pdiba->m_iTransparentIndex = transparentIndex;

            }
            else
            {

               transparentIndex = pdiba->m_iTransparentIndex;

            }

         }
         else
         {

            transparentIndex = pdiba->m_iTransparentIndex;

         }

      }

      antialias_8bit(pdibCompose, pdiba, pointer, uFrameIndex, ba, iScan, cra, transparentIndex);

      pdibCompose->from(pointer->m_dib);


      pointer->m_dib->create(pdiba->m_size);

      pointer->m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      pointer->m_dib->get_graphics()->BitBlt(null_point(), pdiba->m_size, pdibCompose->get_graphics(), point(5, 5));








      //if (false)
      //{


      //   visual::fastblur f(pointer->m_dib->allocer());

      //   draw2d::dib_sp d(pointer->m_dib->allocer());

      //   d->create(pointer->m_dib->m_size);

      //   Sys(pointer->m_dib->get_app()).visual().imaging().channel_spread(f->get_graphics(),
      //    null_point(), f->m_size, pdibCompose->get_graphics(), null_point(), 3, 1);


      //   f.initialize(pointer->m_dib->m_size + size(10, 10), 1);

      //   f->channel_copy(::visual::rgba::channel_red, ::visual::rgba::channel_alpha, pdibCompose);

      //   f->channel_invert(::visual::rgba::channel_red);

      //   f.blur();
      //   f->channel_multiply(::visual::rgba::channel_red, 1.4);
      //   f.blur();
      //   
      //         f.blur();

      //   f->channel_invert(::visual::rgba::channel_red);

      //   draw2d::dib_sp d(pointer->m_dib->allocer());

      //   d->create(pdiba->m_size);

      //   d->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //   d->get_graphics()->BitBlt(null_point(), pdiba->m_size, f->get_graphics(), point(5, 5));

      //   pointer->m_dib->div_alpha();

      //   pointer->m_dib->channel_copy(::visual::rgba::channel_alpha, ::visual::rgba::channel_red, d);

      //   pointer->m_dib->mult_alpha();

      //}

   }
   else // !pdiba->m_bTransparent
   {

      gif_draw_frame(pdibCompose, pdiba, pointer, uFrameIndex, ba, iScan, cra, transparentIndex);


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

         ::rect r = pdiba->element_at(uFrameIndex - 1)->m_rect;

         pdibCompose->get_graphics()->FillSolidRect(r, crBack);

      }

      pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point pt = pointer->m_rect.top_left();

      ::size sz = pointer->m_rect.size();

      if (uFrameIndex <= 0)
      {

         pdibCompose->create(pdiba->m_size);

      }

      pdibCompose->get_graphics()->BitBlt(pt, sz, pointer->m_dib->get_graphics());

      pointer->m_dib->from(pdibCompose);

   }

   return true;

}




































bool gif_draw_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex)
{


   int w = pointer->m_dib->m_iScan / sizeof(COLORREF);

   for (index y = 0; y < pointer->m_rect.height(); y++)
   {

      for (index x = 0; x < pointer->m_rect.width(); x++)
      {

         index iIndex = pixel(x, y);

         if (iIndex >= cra.get_count())
         {

            pointer->m_dib->m_pcolorref[y*w + x] = 0;

            continue;

         }

         if (iIndex == transparentIndex)
         {

            pointer->m_dib->m_pcolorref[y*w + x] = 0;

            continue;

         }

         COLORREF cr = cra[iIndex];

         byte bA = argb_get_a_value(cr);

         pointer->m_dib->m_pcolorref[y*w + x] = cr;

      }

   }

   return true;

}