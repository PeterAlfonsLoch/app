#pragma once

class html_document;


class CLASS_DECL_ca html_view :
   virtual public html_form
{
public:


   string m_strLocationURL;
   base_array < ::html::elemental *, ::html::elemental * > m_elementalptraMouseMove;
   html::elemental * m_pelementalLButtonDown;


   html_view(::ca::application * papp);
   virtual ~html_view();


#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif


   virtual void _001OnDraw(::ca::graphics * pdc);

   string GetLocationURL();
   bool Refresh2(int i);
   bool Navigate(const char * pszUrl);

   virtual void on_document_complete(const char * pszUrl);


   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void OnDraw(::ca::graphics * pgraphics);      // overridden to draw this ::view
   DECL_GEN_SIGNAL(_001OnInitialUpdate)
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

   html_document * get_document();


   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnContextMenu)
   DECL_GEN_SIGNAL(_001OnSetCursor)
   DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
   DECL_GEN_SIGNAL(_001OnViewEncoding)
   DECL_GEN_SIGNAL(_001OnImageLoaded)
   DECL_GEN_SIGNAL(_001OnKeyDown)

   virtual void _001OnTabClick(int iTab);
   
};

