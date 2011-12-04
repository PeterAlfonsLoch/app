#pragma once

class CLASS_DECL_ca2 FileManagerMainFrame :
   public simple_frame_window
{
public:
   FileManagerMainFrame(::ca::application * papp);

   simple_menu_bar           m_menubar;
     simple_toolbar           m_toolbar;
//   SimpleReBar             m_rebar;

   bool CreateBars();

   virtual ~FileManagerMainFrame();

   int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

