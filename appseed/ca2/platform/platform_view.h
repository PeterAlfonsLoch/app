#pragma once

namespace platform
{

   class document;


   class CLASS_DECL_ca2 view :
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
         view *                  m_pview;
         ::ca::application *     m_papp;
         bool                    m_bMakeVisible;
      };

      class link
      {
      public:
         link(::ca::application * papp);
         int32_t                     m_iId;
         run *                   m_prun;
         string                  m_strName;
         string                  m_strBrief;
         string                  m_strDescription;
         string                  m_strSrc;
         ::userbase::button      m_button;
         
      };

      class show_window
      {
      public:
         show_window(oswindow oswindow, int32_t iShow);
         oswindow        m_oswindow;
         int32_t         m_iShow;
         void show();
      };

      int32_t                    m_iV; // veriwell votagus vida
      int32_t                    m_iVH;
      int32_t                    m_iVW;
      visual::dib_sp             m_dibV;
      int32_t                    m_i_veriwell; // veriwell votagus vida
      int32_t                    m_i_veriwell_h;
      int32_t                    m_i_veriwell_w;
      visual::dib_sp             m_dib_veriwell;
      int32_t                    m_i_winactionarea; // que ponta!!cc
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

      array_del_ptr < link, link & > 
                                 m_linka;

      int32_t                    m_iScreen;
      ::ca::font_sp              m_font1;
      ::ca::font_sp              m_font2;
      ::ca::font_sp              m_font3;
      ::ca::brush_sp             m_brushBk;
      ::ca::brush_sp             m_brushProgress3;
      ::ca::brush_sp             m_brushProgress2;
      ::ca::brush_sp             m_brushProgress1;
      visual::dib_sp             m_dibBk;
      visual::dib_sp             m_dibBkImage;
      double                     m_dProgress;
      double                     m_dProgress1;
      double                     m_dProgress2;
      string                     m_strStatus1;
      string                     m_strStatus2;


      
      view(::ca::application * papp);
      virtual ~view();

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      void SetScreen(int32_t iScreen);

      virtual void open_document_file(::ca::create_context * pcreatecontext);

      bool BaseOnControlEvent(::user::control_event * pevent);

      virtual database::user::interaction* BackViewGetWnd();
      virtual ::user::interaction* get_guie();

      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void install_message_handling(::ca::message::dispatch * pinterface);
      virtual bool pre_create_window(CREATESTRUCT& cs);
      virtual void on_update(::view * pSender, LPARAM lHint, ::ca::object* pHint);

      document * get_document();

      DECL_GEN_SIGNAL(_001OnInitialUpdate)

      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnPaint)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnAppLanguage)

      void load_links();
      void layout();
      void check_apps();

      void GetAreaThumbRect(LPRECT lprect, int32_t iArea);
      index hit_test(point pt, e_element & eelement);


      void mt_show_window(oswindow oswindow, int32_t iShow);

      static UINT c_cdecl ThreadProcShowWindow(LPVOID lpparam);

   };

} // namespace platform