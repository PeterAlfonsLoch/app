#pragma once

class html_document;


class CLASS_DECL_CORE html_view :
   virtual public html_form
{
public:


   string m_strLocationURL;


   html_view(sp(::base::application) papp);
   virtual ~html_view();


#ifdef DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif



   string GetLocationURL();
   bool Refresh2(int32_t i);
   bool Navigate(const char * pszUrl);

   virtual void on_document_complete(const char * pszUrl);


   virtual void install_message_handling(::message::dispatch * pinterface);
   virtual bool pre_create_window(CREATESTRUCT& cs);
   DECL_GEN_SIGNAL(_001OnInitialUpdate);
   virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

   sp(html_document) get_document();


   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnContextMenu);
   DECL_GEN_SIGNAL(_001OnSetCursor);

};

