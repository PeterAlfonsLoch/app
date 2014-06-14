#pragma once


namespace database
{


   namespace user
   {


      class CLASS_DECL_BASE interaction :
         virtual public ::simple_ui::interaction,
         virtual public client
      {
      public:


         string         m_strDisplay;

         bool           m_bEnableSaveWindowRect;
         id             m_dataidWindow;


         interaction();
         virtual ~interaction();

         void install_message_handling(::message::dispatch * pinterface);

         DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnSize);
         DECL_GEN_SIGNAL(_001OnMove);
         DECL_GEN_SIGNAL(_001OnShowWindow);

         virtual void _001WindowRestore();

         virtual string calc_display();
         virtual bool does_display_match();
         virtual void defer_update_display();

         virtual bool IsFullScreen();
         void WindowDataEnableSaveWindowRect(bool bEnable);
         bool WindowDataSaveWindowRect();
         bool WindowDataLoadWindowRect(bool bForceRestore = false);

         virtual bool LoadWindowRect_(class id key, class id idIndex, sp(::user::interaction) pwindow, bool bForceRestore = false);
         virtual bool SaveWindowRect_(class id key, class id idIndex, sp(::user::interaction) pwindow);
        
         
         virtual bool on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult);

         virtual id calc_data_id();

         virtual void on_set_parent(sp(::user::interaction) puiParent);
         virtual bool on_before_set_parent(sp(::user::interaction) pinterface);



      };


   } // namespace user


} // namespace database


