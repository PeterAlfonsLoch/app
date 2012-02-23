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
         int                     m_iId;
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
         show_window(HWND hwnd, int iShow);
         HWND        m_hwnd;
         int         m_iShow;
         void show();
      };

      int                  m_iV; // veriwell votagus vida
      int                  m_iVH;
      int                  m_iVW;
      visual::dib_sp       m_dibV;
      int                  m_i_veriwell; // veriwell votagus vida
      int                  m_i_veriwell_h;
      int                  m_i_veriwell_w;
      visual::dib_sp       m_dib_veriwell;
      int                  m_i_winactionarea; // que ponta!!cc
      int                  m_i_winactionarea_h;
      int                  m_i_winactionarea_w;
      visual::dib_sp       m_dib_winactionarea;
      HWND                  m_hwndWinactionarea;
      HWND                  m_hwndCommand;
      HWND                  m_hwndWinutil;
      HWND                 m_hwndWinservice1;
      HWND                  m_hwndBergedge;
      int                  m_iHitArea;

      ::user::front_end_schema::button  
                           m_buttonschema;

      array_del_ptr < link, link & > 
                           m_linka;

      int m_iScreen;
      ::ca::font_sp m_font1;
      ::ca::font_sp m_font2;
      ::ca::font_sp m_font3;
      ::ca::brush_sp m_brushBk;
      ::ca::brush_sp m_brushProgress3;
      ::ca::brush_sp m_brushProgress2;
      ::ca::brush_sp m_brushProgress1;
      visual::dib_sp m_dibBk;
      visual::dib_sp m_dibBkImage;
      double m_dProgress;
      double m_dProgress1;
      double m_dProgress2;
      string m_strStatus1;
      string m_strStatus2;


      
      view(::ca::application * papp);
      virtual ~view();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      void SetScreen(int iScreen);

      virtual void open_document_file(::ca::create_context * pcreatecontext);

      bool BaseOnControlEvent(::user::control_event * pevent);

      virtual database::user::interaction* BackViewGetWnd();
      virtual ::user::interaction* get_guie();

      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void install_message_handling(::gen::message::dispatch * pinterface);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

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

      void GetAreaThumbRect(LPRECT lprect, int iArea);
      int hit_test(point pt, e_element & eelement);


      void mt_show_window(HWND hwnd, int iShow);

      static UINT AFX_CDECL ThreadProcShowWindow(LPVOID lpparam);

   };

} // namespace platform