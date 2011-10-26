#include "StdAfx.h"


namespace veriedit
{

   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      m_toolbar(papp)
   {
      WfiEnableFullScreen();
   }
   
   main_frame::~main_frame()
   {
   }

   bool main_frame::LoadToolBar(const char * lpcszMatter)
   {
         string strToolBar =lpcszMatter;
         m_toolbar.DestroyWindow();
         m_toolbar.RemoveAllTools();

   if (!m_toolbar.CreateEx(this) ||
      !m_toolbar.LoadXmlToolBar(Application.file().as_string(Application.dir().matter(strToolBar))))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }
   layout();
      return true;
   }
} // namespace syllomatter