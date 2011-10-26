#include "StdAfx.h"
#include "biteditor_child_frame.h"

biteditor_child_frame::biteditor_child_frame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
   IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, this, this, &biteditor_child_frame::_001OnAppLanguage);
}

biteditor_child_frame::~biteditor_child_frame()
{
}



bool biteditor_child_frame::CreateBars()
{

   DestroyBars();
    /*if (!m_menubar.CreateEx(this))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }

   if(!m_menubar.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      prel,
      System.font_central().GetMenuFont()) ||
      VMS_FAILED(m_menubar.LoadMenuBar(uiMenuBar)))
   {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
   }*/

   ex1::text_file_sp spfile(get_app());

   string str = Application.file().as_string(Application.dir().matter("biteditor_toolbar.xml"));

   if (!m_toolbar.CreateEx(this) ||
       !m_toolbar.LoadXmlToolBar(str))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }

   layout();

   return true;

/*   if(m_dialogbar.GetSafeHwnd() == NULL)
   {
      UINT uiDialogBar = pdoc->get_filemanager_data()->m_ptemplate->m_uiDialogBar;

      if (!m_dialogbar.create(this, uiDialogBar, 
         CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
      {
         TRACE0("Failed to create dialogbar\n");
         return false;      // fail to create
      }
   }
   pdoc->get_filemanager_data()->m_ptemplate->m_pdialogbar = &m_dialogbar;*/


//   HINSTANCE hinstance = AfxGetResourceHandle();
  // AfxSetResourceHandle(GetModuleHandle("vmsfilemanager.dll"));
   //AfxSetResourceHandle(hinstance);

/*   if (!m_rebar.create(this) ||
//       !m_rebar.AddBar(&m_menubar) ||
       !m_rebar.AddBar(&m_toolbar) ||
       !m_rebar.AddBar(&m_dialogbar))
   {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
   }*/

   layout();

   return true;
}

bool biteditor_child_frame::DestroyBars()
{

   m_toolbar.DestroyWindow();
   m_toolbar.RemoveAllTools();

//   m_dialogbar.DestroyWindow();

   return true;
}


void biteditor_child_frame::_001OnCreate(gen::signal_object * pobj) 
{
   pobj->previous();

   CreateBars();
   

//   SetMenu(NULL);

   m_hMenuDefault = NULL;
   
}


void biteditor_child_frame::_001OnAppLanguage(gen::signal_object * pobj)
{
   CreateBars();
   pobj->m_bRet = false;
}

