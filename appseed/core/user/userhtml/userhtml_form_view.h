#pragma once

class CLASS_DECL_CORE html_form_view :
   virtual public html_form
{
public:


   html::elemental * m_pelementalLButtonDown;


   html_form_view(sp(::axis::application) papp);
   virtual ~html_form_view();


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   string GetLocationURL();
   bool Refresh2(int32_t i);
   bool Navigate(const char * pszUrl);

   virtual void on_document_complete(const char * pszUrl);

   virtual void install_message_handling(::message::dispatch * pinterface);
   virtual bool pre_create_window(::user::create_struct& cs);
   virtual void OnDraw(::draw2d::graphics * pgraphics);      // overridden to draw this ::user::impact
   virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);


   DECL_GEN_SIGNAL(_001OnInitialUpdate);
   DECL_GEN_SIGNAL(_001OnSetFocus);
   DECL_GEN_SIGNAL(_001OnKillFocus);


};



