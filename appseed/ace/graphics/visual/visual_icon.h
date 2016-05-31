#pragma once


namespace visual
{


   class CLASS_DECL_AURA icon :
      virtual public ::object
   {
   public:


      void *      m_picon;
      bool        m_bAutoDelete;
      string      m_strAppTrayIcon;
      size        m_size;
      map < size, size, ::draw2d::dib_sp, ::draw2d::dib_sp> m_dibmap;

      icon(::aura::application * papp);
      icon(void * picon);
#ifdef WINDOWS
      icon(HICON hicon);
#endif
      virtual ~icon();


      operator void *();
#ifdef WINDOWS
      operator HICON();
#endif

      bool load_app_tray_icon(string strPath);

      ::size get_size();

      virtual void on_update_icon();

      ::draw2d::dib * get_dib(int cx, int cy);

   };


   class CLASS_DECL_AURA icon_int_map :
      virtual public int_map < icon * >
   {
   public:

   };


} // namespace visual

