#pragma once


namespace user
{


   class CLASS_DECL_BASE box :
      virtual public scroll,
      virtual public ::simple_ui::interaction,
      virtual public ::database::client
   {
   public:


      string         m_strDisplay;

      box();
      virtual ~box();

      void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void _001WindowRestore();

      virtual string calc_display();
      virtual bool does_display_match();
      virtual void defer_update_display();

      virtual bool IsFullScreen();
      void WindowDataEnableSaveWindowRect(bool bEnable);
      bool WindowDataSaveWindowRect();
      bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false);

      virtual bool LoadWindowRect_(class ::database::id id, sp(::user::box) pwindow, bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool SaveWindowRect_(class ::database::id id, sp(::user::box) pwindow);


      virtual bool on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult);

      virtual void on_set_parent(sp(::user::box) puiParent);
      virtual bool on_before_set_parent(sp(::user::box) pinterface);


      virtual string calc_data_id();


   };


} // namespace user





