#pragma once


namespace visual
{


   class CLASS_DECL_AXIS visual  :
      virtual public ::aura::departament
   {
   public:


      class imaging * m_pimaging;
      map < e_cursor, e_cursor, cursor *, cursor * > m_cursormap;
            class ::visual::api *                        m_pvisualapi;
            class font_central * m_pfontcentral;



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
      cursor * set_cursor_file(e_cursor ecursor,const ::file::path & psz, bool bFromCache);
      cursor * set_cursor_matter(e_cursor ecursor,const ::file::path & pszMatter);
      ::count set_cursor_set_from_matter(const ::file::path & pszMatter);
      ::count set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache);
      cursor * get_cursor(e_cursor ecursor);


      virtual int32_t exit_instance();


      static uint32_t c_cdecl thread_proc_parallel_initialize(void * pparamThis);


   };


} // namespace visual


