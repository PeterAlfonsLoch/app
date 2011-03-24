#pragma once

namespace md5
{

   class CLASS_DECL_CA2_MD5 pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:

	   pane_view(::ca::application * papp);
      virtual ~pane_view();

      void on_create_view(view_data * pviewdata);
      void _001InstallMessageHandling(user::win::message::dispatch * pinterface);

	   virtual void on_update(::view * pSender, LPARAM lHint, base_object* pHint);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)
   };

} // namespace md5