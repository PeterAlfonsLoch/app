#include "StdAfx.h"


static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

namespace vmsp
{

   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp), 
      m_toolbar(papp),
      m_statusbar(papp)
   {
   //   m_eappearancestyle = window_frame::StyleBlueRedPurple;

      m_bLayered = false;
   }

   main_frame::~main_frame()
   {
   }

   int main_frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
   {
   //   if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
   //      return -1;
      /*
      if (!m_toolbar.CreateEx(this) ||
         !m_toolbar.LoadToolBar(IDR_MAINFRAME))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }*/

      m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() & ~CBRS_HIDE_INPLACE);
   /*   if (!m_wndDlgBar.create(this, IDR_MAINFRAME, 
         CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
      {
         TRACE0("Failed to create dialogbar\n");
         return -1;      // fail to create
      }*/

   /*   if (!m_rebar.AddBar(&m_toolbar) ) // ||
   //      !m_rebar.AddBar(&m_wndDlgBar))
      {
         TRACE0("Failed to create rebar\n");
         return -1;      // fail to create
      }
      m_rebar.SetBarStyle(m_rebar.GetBarStyle() & ~CBRS_HIDE_INPLACE);
   */
      /*
      if (!m_statusbar.create(this) ||
         !m_statusbar.SetIndicators(indicators,
           sizeof(indicators)/sizeof(UINT)))
      {
         TRACE0("Failed to create status bar\n");
         return -1;      // fail to create
      }

      */

      // TODO: remove this if you don't want tool tips
      m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
         CBRS_TOOLTIPS | CBRS_FLYBY);
   /*   m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
         CBRS_TOOLTIPS | CBRS_FLYBY);*/

      return 0;
   }

   BOOL main_frame::PreCreateWindow(CREATESTRUCT& cs)
   {
      if( !simple_frame_window::PreCreateWindow(cs) )
         return FALSE;
      // TODO: Modify the Window class or styles here by modifying
      //  the CREATESTRUCT cs
      cs.style |= WS_CLIPCHILDREN;
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // main_frame diagnostics

   #ifdef _DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }

   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // main_frame message handlers


   void main_frame::OnUpdateFrameMenu(HMENU hMenuAlt)
   {
      simple_frame_window::OnUpdateFrameMenu(hMenuAlt);
   }
   void main_frame::DelayUpdateFrameMenu(HMENU hMenuAlt)
   {
      simple_frame_window::DelayUpdateFrameMenu(hMenuAlt);
   }

} // namespace vmsp