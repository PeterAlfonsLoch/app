#pragma once

#include "pane_view_update_hint.h"

namespace flag
{

   class view;

   class CLASS_DECL_CA2_FLAG pane_view : 
      public ::userex::pane_tab_view,
      public FileManagerCallbackInterface,
      public flag::form_callback
   {
   public:

      ::flag::view *                     m_pwinactionareaview;

	   pane_view(::ca::application * papp);

      void rotate();
      
      void on_create_view(view_data * pviewdata);
      void on_show_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      //void check_menu_dir(const char * psz);
      void check_3click_dir(const char * psz);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


      void request(var & varFile, var & varQuery);

      DECL_GEN_SIGNAL(_001OnMenuMessage)
	   virtual ~pane_view();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnShowWindow)

   };


} // namespace flag


