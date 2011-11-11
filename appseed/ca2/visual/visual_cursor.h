#pragma once


namespace visual
{


   class CLASS_DECL_ca cursor :
      virtual public ::radix::object
   {
   public:
      

      e_cursor             m_ecursor;
      ::visual::dib_sp     m_dib;
      ::ca::dib_sp         m_dibWork;
      ::ca::dib_sp         m_dibWork2;
      point                m_ptHotspot;


      cursor(::ca::application * papp);

      bool load_from_file(const char * psz);
      bool load_from_matter(const char * pszMatter);
      bool to(::ca::graphics * pgraphics, int x, int y);
      bool to(::ca::graphics * pgraphics, point pt);


   };


} // namespace visual


