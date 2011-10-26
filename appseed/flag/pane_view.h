#pragma once

#include "pane_view_update_hint.h"

namespace flag
{

   class view;

   class CLASS_DECL_CA2_FLAG pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      ::flag::view *                     m_pflagview;


      pane_view(::ca::application * papp);
	   virtual ~pane_view();

      
      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)

   };


} // namespace flag


