#pragma once


class document;

namespace devedge
{
   class KeyboardFocus;
   class Element2D;
} // namespace devedge


class CLASS_DECL_CA2_CUBE devedgeHtmlEditView : public html_view
{
public:
   devedgeHtmlEditView(::ca::application * papp);

   virtual ~devedgeHtmlEditView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   enum e_message
   {
      MessageUserCheckChange,
   };

   
   virtual database::user::interaction* BackViewGetWnd();
   virtual ::user::interaction* get_guie();

   virtual void _001OnDraw(::ca::graphics * pdc);

   void transform();
   void transform_back();


   devedge::KeyboardFocus *   m_pkeyboardfocus;
   devedge::Element2D * m_pelementMouseDown;
   DWORD m_dwLastKeyWparam;
   DWORD m_dwLastKeyLparam;

   string m_str;

   stringa m_straScript;

   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnKeyDown)
   DECL_GEN_SIGNAL(_001OnKeyUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnUser)


   DECL_GEN_SIGNAL(_001OnChar)
   DECL_GEN_SIGNAL(_001OnSysChar)

   DECL_GEN_SIGNAL(_001OnPost)

   devedge::Element2D * hit_test(int x, int y);
   void on_update(::view* pSender, LPARAM lHint, ::radix::object* phint);

   virtual void key_to_char(WPARAM wparam, LPARAM lparam);

   document * get_document() const;


   
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
