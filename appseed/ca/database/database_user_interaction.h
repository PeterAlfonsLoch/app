#pragma once


namespace database
{


   namespace user
   {


      class CLASS_DECL_ca interaction :
         virtual public ::user::interaction,
         virtual public client
      {
      public:


         string         m_strDisplay;

         bool           m_bEnableSaveWindowRect;
         id             m_dataidWindow;


         interaction();
         virtual ~interaction();

         void install_message_handling(::ca::message::dispatch * pinterface);

         DECL_GEN_SIGNAL(_001OnCreate)
         DECL_GEN_SIGNAL(_001OnSize)
         DECL_GEN_SIGNAL(_001OnMove)
         DECL_GEN_SIGNAL(_001OnShowWindow)

         virtual void _001WindowRestore();

         virtual string calc_display();
         virtual bool does_display_match();

         virtual bool IsFullScreen();
         void WindowDataEnableSaveWindowRect(bool bEnable);
         bool WindowDataSaveWindowRect();
         bool WindowDataLoadWindowRect(bool bForceRestore = false);

         virtual bool LoadWindowRect_(class id key, class id idIndex, sp(::user::interaction) pWnd, bool bForceRestore = false);
         virtual bool SaveWindowRect_(class id key, class id idIndex, sp(::user::interaction) pWnd);
        
         
         virtual bool on_simple_command(e_simple_command ecommand, LPARAM lparam, LRESULT & lresult);


      };


   } // namespace user


} // namespace database


