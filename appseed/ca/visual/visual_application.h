#pragma once


namespace visual
{


   class CLASS_DECL_ca application  :
      virtual public ::userpresence::application
   {
   public:


      class imaging * m_pimaging;
      ::collection::map < e_cursor, e_cursor, cursor *, cursor * > m_cursormap;
      e_cursor m_ecursor;
      e_cursor m_ecursorDefault;


      application();
      virtual ~application();
      virtual class imaging & imaging();
      virtual bool initialize();
      virtual bool initialize1();
      class font_central & font_central();
      class font_central * m_pfontcentral;
      cursor * set_cursor_file(e_cursor ecursor, const char * psz);
      cursor * set_cursor_matter(e_cursor ecursor, const char * pszMatter);
      count set_cursor_set_from_matter(const char * pszMatter);
      count set_cursor_set_from_dir(const char * pszDir);
      void set_cursor(e_cursor ecursor);
      void set_default_cursor(e_cursor ecursor);
      cursor * get_cursor();
      cursor * get_default_cursor();
      cursor * get_cursor(e_cursor ecursor);


      virtual int32_t exit_instance();


   };


} // namespace visual


