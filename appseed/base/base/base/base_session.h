#pragma once




namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application,
      virtual public ::user::schema
   {
   public:






      session(::aura::application * papp);
      virtual ~session_parent;



   };


} // namespace base





































