#pragma once




namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application,
      virtual public ::user::schema
   {
   public:




      ::map < ::user::e_key,::user::e_key,bool,bool > *         m_pmapKeyPressed;


      session(::aura::application * papp);
      virtual ~session_parent;

      virtual bool is_key_pressed(::user::e_key ekey);

      virtual void set_key_pressed(::user::e_key ekey,bool bPressed);


   };


} // namespace base





































