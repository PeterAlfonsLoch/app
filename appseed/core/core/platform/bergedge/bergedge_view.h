#pragma once

namespace bergedge
{

   class document;
   class pane_view;

   class CLASS_DECL_CORE view :
      virtual public ::user::scroll_view,
      virtual public ::user::place_holder,
      virtual public ::backview::user::interaction
   {
   public:

      sp(::bergedge::pane_view)    m_ppaneview;

      int32_t m_iV;
      int32_t m_iVH;
      int32_t m_iVW;
      visual::dib_sp m_dibV;
      int32_t m_i_veriwell;
      int32_t m_i_veriwell_h;
      int32_t m_i_veriwell_w;
      visual::dib_sp m_dib_veriwell;
      int32_t m_i_winactionarea;
      int32_t m_i_winactionarea_h;
      int32_t m_i_winactionarea_w;
      visual::dib_sp m_dib_winactionarea;


      visual::dib_sp m_dibBk;

      oswindow                  m_oswindowWinactionarea;
      oswindow                  m_oswindowCommand;
      oswindow                  m_oswindowWinutil;
      oswindow                 m_oswindowWinservice1;
      oswindow                  m_oswindowBergedge;


      ::draw2d::font_sp m_font;
      stringa m_straImagePath;
      string m_strCurrentImagePath;
      bool m_bDestroy;
      //::user::buffer                  m_gdibuffer;
      rect_array       m_rectaUpdate;
      uint32_t                m_dwLastUpdate;
      mutex m_mutexDraw;


      view(sp(::axis::application) papp);
      virtual ~view();

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      enum ETimer
      {
         TimerBackView = 1000,
      };

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics);


      virtual void pre_translate_message(signal_details * pobj);

      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

      sp(::user::document) get_document();

      void GetAreaThumbRect(LPRECT lprect, int32_t iArea);

      index hit_test(point pt, e_element & eelement);

      DECL_GEN_SIGNAL(_001OnInitialUpdate);

      bool UpdateScreen(rect_array & recta, UINT uiRedraw);
      void BackViewUpdateScreen(const RECT & rect, UINT uiRedraw);
      void BackViewUpdateScreen(rect_array & recta, UINT uiRedraw);
      void BackViewUpdateScreen();
      void BackViewGetData(::backview::InterfaceData & data);
      void BackViewSetData(::backview::InterfaceData & data);
      bool BackViewGetDestroy();

      string GetNextBackgroundImagePath();
      void SetCurrentBackgroundImagePath(string &str);

      //virtual void layout();

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual void _001OnTabClick(int32_t iTab);

      void check_apps();

      void mt_show_window(oswindow oswindow, int32_t iShow);

      static UINT c_cdecl ThreadProcShowWindow(LPVOID lpparam);

      void _000OnMouse(::message::mouse * pmouse);

   };


} // namespace bergedge
