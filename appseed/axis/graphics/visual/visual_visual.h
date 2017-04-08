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
      class font_department *                            m_pfontdepartment;



      visual(::aura::application * papp);
      virtual ~visual();


      virtual void construct(::aura::application * papp);

      virtual bool process_initialize();
      
      virtual bool initialize();
      virtual bool initialize1();

      virtual bool finalize();


      virtual class api & api();
      virtual class imaging & imaging();
            


      class font_department & fonts();
      cursor * set_system_default_cursor(e_cursor ecursor);
      cursor * set_cursor_file(e_cursor ecursor,const ::file::path & psz, bool bFromCache = true);
      ::count set_cursor_set_from_matter(const ::file::path & pszMatter);
      ::count set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache = true);
      ::count set_cursor_set_system_default();
      cursor * get_cursor(e_cursor ecursor);


      virtual int32_t exit_application();


      //static uint32_t c_cdecl thread_proc_parallel_initialize(void * pparamThis);





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
         bool bUpdate,
         double dAlpha = 1.0);


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
         bool bUpdate,
         double dAlpha = 1.0);
      


   };


} // namespace visual


