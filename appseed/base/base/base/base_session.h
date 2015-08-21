#pragma once




namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application,
      virtual public ::user::schema
   {
   public:


      ::user::user *                                          m_puser;




      ::user::schema_simple_impl *                            m_pschemasimple;


      session(::aura::application * papp);
      virtual ~session_parent;

      inline ::user::user *                        user()         { return m_puser; }

      virtual index get_good_restore(LPRECT lprect,const RECT & rect,::user::interaction * pui);
      virtual index get_good_move(LPRECT lprect,const RECT & rect,::user::interaction * pui);
      virtual index get_ui_wkspace(::user::interaction * pui);

      virtual index initial_frame_position(LPRECT lprect,const RECT & rect,bool bMove,::user::interaction * pui);

      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();
      virtual void frame_pre_translate_message(signal_details * pobj);

      bool process_initialize();

      bool initialize1();

      bool initialize();

      virtual string get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);

      virtual void get_cursor_pos(LPPOINT lppoint);
      
   };


} // namespace base





































