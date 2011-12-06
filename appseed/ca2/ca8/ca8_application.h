#pragma once


namespace ca8
{


   class CLASS_DECL_ca2 application :
      virtual public ::ca2::fs::application
   {
   public:


      filemanager::_shell::ImageSet * m_pshellimageset;


      application();
      virtual ~application();

      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

      filemanager::_shell::ImageSet & shellimageset();

      virtual bool initialize1();
      virtual bool initialize();
      
      string message_box(const char * pszMatter, gen::property_set & propertyset);
      using ::radix::application::simple_message_box;
      virtual int simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int iTimeout, UINT fuStyle = MB_OK);
      virtual int simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending);
   
      virtual void data_on_after_change(gen::signal_object * pobj);

   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca