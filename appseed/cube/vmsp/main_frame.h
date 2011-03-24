#pragma once

namespace vmsp
{

   class CLASS_DECL_CA2_CUBE main_frame :
      public simple_frame_window
   {
   public:
      main_frame(::ca::application * papp);

   //   SimpleReBar m_rebar;


      virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);

      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      
      virtual ~main_frame();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      simple_status_bar      m_statusbar;
      simple_toolbar        m_toolbar;

      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   };

} // namespace vmsp