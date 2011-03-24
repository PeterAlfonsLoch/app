#pragma once

class CLASS_DECL_ca simple_form_list_view :
   public ::userbase::view,
   public ::userbase::form_list
{
public:
   simple_form_list_view(::ca::application * papp);

   simple_list_header_control   m_headerctrl;
   simple_scroll_bar        m_scrollbarVert;
   simple_scroll_bar        m_scrollbarHorz;


   
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~simple_form_list_view();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   
};
