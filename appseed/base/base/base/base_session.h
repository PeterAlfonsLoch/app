#pragma once




namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application,
      virtual public ::user::schema
   {
   public:


      ::user::interaction *                                   m_puiFocus;
      ::user::user *                                          m_puser;




      ::user::schema_simple_impl *                            m_pschemasimple;


      session(::aura::application * papp);
      virtual ~session_parent;

      inline ::user::user *                        user()         { return m_puser; }


      bool process_initialize();

      bool initialize1();

      bool initialize();
   };


} // namespace base





































