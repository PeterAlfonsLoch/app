#pragma once


namespace visual
{
      
      template < typename PRED >
      bool visual::emboss_pred(
         ::draw2d::graphics * pgraphics,
         LPCRECT lpcrect,
         PRED pred,
         ::visual::fastblur & dib2,
         COLORREF crGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate,
         double dAlpha)
      {


         int iR = MAX(MAX(iSpreadRadius, iBlurRadius), iBlur) + 1;

         ::rect rectEmboss = *lpcrect;

         rectEmboss.left -= iR;
         rectEmboss.top -= iR;
         rectEmboss.right += iR * 3;
         rectEmboss.bottom += iR * 3;

         if (bUpdate || dib2.is_null() || dib2->area() <= 0)
         {

            int iEffectiveSpreadRadius = iSpreadRadius;

            int iEffectiveBlurRadius = iBlurRadius;

            if (dib2.is_null())
            {

               dib2.alloc(allocer());

            }

            class size size = rectEmboss.size();

            dib2.initialize(size, iEffectiveBlurRadius);

            dib2->Fill(0, 0, 0, 0);

            class rect rectCache;

            rectCache.left = iR + (iR >= 2 ? 1 : 0);
            rectCache.top = iR + 1;
            rectCache.right = rectCache.left + ::width(lpcrect);
            rectCache.bottom = rectCache.top + ::height(lpcrect);

            ::draw2d::dib_sp dib(allocer());

            dib->create(size.cx, size.cy);
            dib->Fill(0, 0, 0, 0);

            ::draw2d::brush_sp brushText(allocer());

            brushText->create_solid(ARGB(255, 255, 255, 255));
            dib->get_graphics()->SelectObject(brushText);

            dib->get_graphics()->OffsetViewportOrg(rectCache.left - lpcrect->left, rectCache.top - lpcrect->top);

            pred(dib->get_graphics());

            dib->get_graphics()->OffsetViewportOrg(-rectCache.left + lpcrect->left, -rectCache.top + lpcrect->top);

            System.visual().imaging().channel_spread_set_color(dib2->get_graphics(), null_point(), size, dib->get_graphics(), null_point(), ::visual::rgba::channel_alpha, iEffectiveSpreadRadius, ARGB(255, 255, 255, 255));

            for (index i = 0; i < iBlur; i++)
            {

               dib2.blur();

            }

            dib2->set_rgb(crGlow);

            dib2->mult_alpha();

         }

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->alpha_blend(rectEmboss, dib2->get_graphics(), dAlpha);

         //::draw2d::brush_sp brushText(allocer());
         //brushText->create_solid(crText);
         //pgraphics->SelectObject(brushText);
         //pgraphics->SelectObject(pfont);
         //pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

         return true;

      }


}
