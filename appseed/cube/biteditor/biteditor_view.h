#pragma once

class biteditor_document;

class _declspec(dllexport) biteditor_view : 
   virtual public ::userbase::scroll_view
{
public:
   biteditor_view(::ca::application * papp);

   virtual ~biteditor_view();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

//   virtual void _001OnDraw(::ca::graphics * pdc);

   int CalcLineCount();

   int UpdateScrollSizes();

   biteditor::ascii_box *     m_pasciibox;
   biteditor::hex_box *       m_phexbox;
   int                        m_iLineSize;
   int                        m_iLineHeight;

   DWORD m_dwLastKeyWparam;
   DWORD m_dwLastKeyLparam;

   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnKeyDown)
   DECL_GEN_SIGNAL(_001OnKeyUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnHScroll)

   DECL_GEN_SIGNAL(_001OnRButtonUp)

   DECL_GEN_SIGNAL(_001OnChar)
   DECL_GEN_SIGNAL(_001OnSysChar)

   void on_update(::view * pSender, LPARAM lHint, ::radix::object* phint);

   void key_to_char(WPARAM wparam, LPARAM lparam);

   biteditor_document * get_document() const;

   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   DECL_GEN_SIGNAL(_001OnInitialUpdate)

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
