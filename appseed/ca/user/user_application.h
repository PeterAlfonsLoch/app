#pragma once


namespace user
{


   class CLASS_DECL_ca application :
      public ::visual::application
   {
   public:


      filemanager::_shell::ImageSet *        m_pshellimageset;
      ::user::keyboard_focus *               m_pkeyboardfocus;
      ::user::mouse_focus *                  m_pmousefocusLButtonDown;
      ::user::mouse_focus *                  m_pmousefocusRButtonDown;
      class window_map *                     m_pwindowmap;
      ::user::keyboard *                     m_pkeyboard;




      application();
      virtual ~application();

      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

      filemanager::_shell::ImageSet & shellimageset();

      virtual bool initialize1();
      virtual bool initialize();


      class window_map & window_map();


      virtual ::user::keyboard_focus * get_keyboard_focus();
      virtual void set_keyboard_focus(::user::keyboard_focus * pkeyboardfocus);
      virtual ::user::mouse_focus * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::mouse_focus * pmousefocus);
      virtual ::user::mouse_focus * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::mouse_focus * pmousefocus);

      
      string message_box(const char * pszMatter, gen::property_set & propertyset);
      using ::radix::application::simple_message_box;
      virtual int simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int iTimeout, UINT fuStyle = MB_OK);
      virtual int simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending);
   
      virtual void data_on_after_change(gen::signal_object * pobj);

      class keyboard & keyboard();


   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca