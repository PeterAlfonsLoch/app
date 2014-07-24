#pragma once

namespace platform
{

   class document;


   class CLASS_DECL_CORE view :
      virtual public form_view
   {
   public:


      class link;

      class run
      {
      public:
         run();
         index                     m_iEdge;
         link *                  m_plink;
         string                  m_strApp;
         string                  m_strQuery;
         sp(view)                  m_pview;
         sp(::base::application)     m_pbaseapp;
         bool                    m_bMakeVisible;
      };

      class link :
         virtual public element
      {
      public:
         link(sp(::base::application) papp);
         int32_t                     m_iId;
         run *                   m_prun;
         string                  m_strName;
         string                  m_strBrief;
         string                  m_strDescription;
         string                  m_strSrc;
         ::user::button      m_button;
         
      };

      class show_window
      {
      public:
         show_window(oswindow oswindow, int32_t iShow);
         oswindow        m_oswindow;
         int32_t         m_iShow;
         void show();
      };

      int32_t                    m_iV; 
      int32_t                    m_iVH;
      int32_t                    m_iVW;
      visual::dib_sp             m_dibV;
      int32_t                    m_i_veriwell; 
      int32_t                    m_i_veriwell_h;
      int32_t                    m_i_veriwell_w;
      visual::dib_sp             m_dib_veriwell;
      int32_t                    m_i_winactionarea; 
      int32_t                    m_i_winactionarea_h;
      int32_t                    m_i_winactionarea_w;
      visual::dib_sp             m_dib_winactionarea;
      oswindow                   m_oswindowWinactionarea;
      oswindow                   m_oswindowCommand;
      oswindow                   m_oswindowWinutil;
      oswindow                   m_oswindowWinservice1;
      oswindow                   m_oswindowBergedge;
      index                      m_iHitArea;

      ::user::front_end_schema::button  
                                 m_buttonschema;

      spa(link)                  m_linka;

      int32_t                    m_iScreen;
      ::draw2d::font_sp              m_font1;
      ::draw2d::font_sp              m_font2;
      ::draw2d::font_sp              m_font3;
      ::draw2d::brush_sp             m_brushBk;
      ::draw2d::brush_sp             m_brushProgress3;
      ::draw2d::brush_sp             m_brushProgress2;
      ::draw2d::brush_sp             m_brushProgress1;
      visual::dib_sp             m_dibBk;
      visual::dib_sp             m_dibBkImage;
      double                     m_dProgress;
      double                     m_dProgress1;
      double                     m_dProgress2;
      string                     m_strStatus1;
      string                     m_strStatus2;


      
      view(sp(::base::application) papp);
      virtual ~view();

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      void SetScreen(int32_t iScreen);

      virtual void open_document_file(sp(::create_context) pcreatecontext);

      bool BaseOnControlEvent(::user::control_event * pevent);

      virtual sp(::database::user::interaction) BackViewGetWnd();

      virtual void _001OnDraw(::draw2d::graphics * pdc);


      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool pre_create_window(CREATESTRUCT& cs);
      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

      sp(::user::document) get_document();

      DECL_GEN_SIGNAL(_001OnInitialUpdate);

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnAppLanguage);

      void load_links();
      void layout();
      void check_apps();

      void GetAreaThumbRect(LPRECT lprect, int32_t iArea);
      index hit_test(point pt, e_element & eelement);


      void mt_show_window(oswindow oswindow, int32_t iShow);

      static UINT c_cdecl ThreadProcShowWindow(LPVOID lpparam);

   };

} // namespace platform