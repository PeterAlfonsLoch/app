#pragma once



class CLASS_DECL_ca2 simple_tab_view :
   virtual public ::userbase::view,
   virtual public ::user::tab
{
public:
   simple_tab_view(::ca::application * papp);
   virtual ~simple_tab_view();



   virtual void _001OnDraw(::ca::graphics * pdc);

#ifdef DEBUG
   virtual void assert_valid() const;
#ifndef _WIN32_WCE
   virtual void dump(dump_context & dumpcontext) const;
#endif
#endif

   DECL_GEN_SIGNAL(_001OnSize)
   void layout();

   void _001OnCreate(::ca::signal_object * pobj);

   virtual void GetClientRect(LPRECT lprect);

   virtual void install_message_handling(::ca::message::dispatch * pinterface);

   DECL_GEN_VSIGNAL(_001OnLButtonUp)
   DECL_GEN_VSIGNAL(_001OnMouseMove)
   DECL_GEN_VSIGNAL(_001OnMouseLeave)

};


