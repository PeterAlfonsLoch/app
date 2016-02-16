#pragma once




namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application,
      virtual public ::user::schema
   {
   public:


      sp(::user::user)              m_puser;
      sp(::user::schema)            m_pschemasimple;


      session(::aura::application * papp);
      virtual ~session_parent;

      inline ::user::user *                        user()         { return m_puser; }

      virtual index get_good_restore(LPRECT lprect,const RECT & rect,::user::interaction * pui);
      virtual index get_good_move(LPRECT lprect,const RECT & rect,::user::interaction * pui);
      virtual index get_ui_wkspace(::user::interaction * pui);

      virtual index initial_frame_position(LPRECT lprect,const RECT & rect,bool bMove,::user::interaction * pui);

      virtual void frame_pre_translate_message(signal_details * pobj);

      bool process_initialize();

      bool initialize1();

      bool initialize();

      virtual string get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);

      virtual void get_cursor_pos(LPPOINT lppoint);

      virtual ::user::primitive * get_active_ui();
      virtual ::user::primitive * get_focus_ui();

      ::user::elemental * get_keyboard_focus();

      sp(::user::schema) get_new_user_schema(const char * pszUinteractionLibrary);


      virtual void on_finally_focus_set(::user::elemental * pelementalFocus) override;

   };


} // namespace base





































