#pragma once


namespace visual
{


   class CLASS_DECL_AXIS visual  :
      virtual public ::aura::department
   {
   public:


      class imaging *                                    m_pimaging;
      map < e_cursor, e_cursor, cursor *, cursor * >     m_cursormap;
      class ::visual::api *                              m_pvisualapi;
      class font_central *                               m_pfontcentral;



      visual(::aura::application * papp);
      virtual ~visual();


      virtual void construct(::aura::application * papp);

      virtual bool process_initialize();
      
      virtual bool initialize();
      virtual bool initialize1();

      virtual bool finalize();


      virtual class api & api();
      virtual class imaging & imaging();
            


      class font_central & font_central();
      cursor * set_cursor_file(e_cursor ecursor,const ::file::path & psz, bool bFromCache = true);
      ::count set_cursor_set_from_matter(const ::file::path & pszMatter);
      ::count set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache = true);
      cursor * get_cursor(e_cursor ecursor);


      virtual int32_t exit_instance();


      static uint32_t c_cdecl thread_proc_parallel_initialize(void * pparamThis);

      virtual bool embossed_text_out(
         ::draw2d::graphics * pgraphics, 
         LPCRECT lpcrect, 
         string strText, 
         ::visual::fastblur & dib2,
         ::draw2d::font * pfont, 
         int iDrawTextFlags,
         COLORREF crText,
         COLORREF crGlow, 
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur, 
         bool bUpdate);


      template < typename PRED >
      bool emboss_pred(
         ::draw2d::graphics * pgraphics,
         LPCRECT lpcrect,
         PRED pred,
         ::visual::fastblur & dib2,
         COLORREF crGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate)
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
         pgraphics->BitBlt(rectEmboss, dib2->get_graphics());

         //::draw2d::brush_sp brushText(allocer());
         //brushText->create_solid(crText);
         //pgraphics->SelectObject(brushText);
         //pgraphics->SelectObject(pfont);
         //pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

         return true;

      }


   };


} // namespace visual


