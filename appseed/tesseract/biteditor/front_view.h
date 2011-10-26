#pragma once


class biteditor_document;

namespace biteditor
{
   class KeyboardFocus;
   class Element2D;
} // namespace biteditor


class CLASS_DECL_CA2_TESSERACT front_view : public html_view
{
public:

   
   biteditor::KeyboardFocus *   m_pkeyboardfocus;
   biteditor::Element2D * m_pelementMouseDown;
   DWORD m_dwLastKeyWparam;
   DWORD m_dwLastKeyLparam;


   front_view(::ca::application * papp);
   virtual ~front_view();

#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual void _001OnDraw(::ca::graphics * pdc);



   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnKeyDown)
   DECL_GEN_SIGNAL(_001OnKeyUp)
   DECL_GEN_SIGNAL(_001OnTimer)


   DECL_GEN_SIGNAL(_001OnChar)
   DECL_GEN_SIGNAL(_001OnSysChar)

   DECL_GEN_SIGNAL(_001OnPost)

   using html_view::hit_test;
   biteditor::Element2D * hit_test(int x, int y);
   void on_update(::view* pSender, LPARAM lHint, ::radix::object* phint);

   void key_to_char(WPARAM wparam, LPARAM lparam);

   biteditor_document * get_document() const;

   //virtual void pre_translate_message(gen::signal_object * pobj);
   virtual void install_message_handling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   DECL_GEN_SIGNAL(_001OnInitialUpdate)

  void OnDocumentComplete(const char * lpszURL);

   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnPaint)
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnContextMenu)
   DECL_GEN_SIGNAL(_001OnSetCursor)
   DECL_GEN_SIGNAL(_001OnUpdateViewEncoding)
   DECL_GEN_SIGNAL(_001OnViewEncoding)
   DECL_GEN_SIGNAL(_001OnWavePlayerEvent)

   
};
