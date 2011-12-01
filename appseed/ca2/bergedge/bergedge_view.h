#pragma once

namespace bergedge
{

   class document;
   class pane_view;

   class CLASS_DECL_ca view :
      virtual public ::userbase::scroll_view,
      virtual public ::user::place_holder,
      virtual public gcom::backview::user::interaction
   {
   public:

      pane_view *    m_ppaneview;

      int m_iV; // veriwell votagus vida
      int m_iVH;
      int m_iVW;
      visual::dib_sp m_dibV;
      int m_i_veriwell; // veriwell votagus vida
      int m_i_veriwell_h;
      int m_i_veriwell_w;
      visual::dib_sp m_dib_veriwell;
      int m_i_winactionarea; // que ponta!!cc
      int m_i_winactionarea_h;
      int m_i_winactionarea_w;
      visual::dib_sp m_dib_winactionarea;


      visual::dib_sp m_dibBk;

      HWND                  m_hwndWinactionarea;
      HWND                  m_hwndCommand;
      HWND                  m_hwndWinutil;
      HWND                 m_hwndWinservice1;
      HWND                  m_hwndBergedge;


      ::ca::font_sp m_font;
      stringa m_straImagePath;
      string m_strCurrentImagePath;
      bool m_bDestroy;
      //::user::buffer                  m_gdibuffer;
      rect_array       m_rectaUpdate;
      DWORD                m_dwLastUpdate;
      mutex m_mutexDraw;


      view(::ca::application * papp);
      virtual ~view();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      enum ETimer
      {
         TimerBackView = 1000,
      };

      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void pre_translate_message(gen::signal_object * pobj);

      virtual void install_message_handling(::gen::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void OnDraw(::ca::graphics * pgraphics);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      document * get_document();

      void GetAreaThumbRect(LPRECT lprect, int iArea);

      int hit_test(point pt, e_element & eelement);

      DECL_GEN_SIGNAL(_001OnInitialUpdate)
      
      VMSRESULT UpdateScreen(rect_array & recta, UINT uiRedraw);
      void BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw);
      void BackViewUpdateScreen(rect_array & recta, UINT uiRedraw);
      void BackViewUpdateScreen();
      void BackViewGetData(gcom::backview::InterfaceData & data);
      void BackViewSetData(gcom::backview::InterfaceData & data);
      bool BackViewGetDestroy();

      string GetNextBackgroundImagePath();
      void SetCurrentBackgroundImagePath(string &str);

      //virtual void layout();

      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnSetCursor)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonUp)

      virtual void _001OnTabClick(int iTab);

      void check_apps();

      void mt_show_window(HWND hwnd, int iShow);

      static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);
      
      void _000OnMouse(::gen::message::mouse * pmouse);

   };


} // namespace bergedge