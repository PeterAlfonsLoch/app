#pragma once


namespace visual
{


   class CLASS_DECL_BASE cursor :
      virtual public object
   {
   public:


      e_cursor                m_ecursor;
      ::draw2d::dib_sp        m_dib;
      ::draw2d::dib_sp        m_dibWork;
      ::draw2d::dib_sp        m_dibWork2;
      point                   m_ptHotspot;


      cursor(sp(base_application) papp);

      bool load_from_file(const char * psz);
      bool load_from_matter(const char * pszMatter);
      bool to(::draw2d::graphics * pgraphics, int32_t x, int32_t y);
      bool to(::draw2d::graphics * pgraphics, point pt);


   };


} // namespace visual


