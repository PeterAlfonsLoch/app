#pragma once


namespace visual
{


   class CLASS_DECL_ca2 cursor :
      virtual public ::ca2::object
   {
   public:
      

      e_cursor             m_ecursor;
      ::visual::dib_sp     m_dib;
      ::ca2::dib_sp         m_dibWork;
      ::ca2::dib_sp         m_dibWork2;
      point                m_ptHotspot;


      cursor(sp(::ca2::application) papp);

      bool load_from_file(const char * psz);
      bool load_from_matter(const char * pszMatter);
      bool to(::ca2::graphics * pgraphics, int32_t x, int32_t y);
      bool to(::ca2::graphics * pgraphics, point pt);


   };


} // namespace visual


