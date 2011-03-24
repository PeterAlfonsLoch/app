#pragma once

class CLASS_DECL_ca html_form_view :
   virtual public html_form
{
public:


   html::elemental * m_pelementalLButtonDown;

   
   html_form_view(::ca::application * papp);
   virtual ~html_form_view();


#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   string GetLocationURL();
   bool Refresh2(int i);
   bool Navigate(const char * pszUrl);

   virtual void on_document_complete(const char * pszUrl);

   virtual html::data * calc_data();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnSetFocus)
   DECL_GEN_SIGNAL(_001OnKillFocus)

};

