#include "StdAfx.h"
#include "FileManagerFrame.h"


FileManagerFrame::FileManagerFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp),
   m_toolbar(papp),
   m_menubar(papp)
{
}

FileManagerFrame::~FileManagerFrame()
{
}


 // BEGIN_MESSAGE_MAP(FileManagerFrame, simple_frame_window)
   //{{AFX_MSG_MAP(FileManagerFrame)
// xxx   ON_WM_CREATE()
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileManagerFrame message handlers

void FileManagerFrame::_001OnCreate(gen::signal_object * pobj) 
{
   
   pobj->previous();
/* trans   if (simple_frame_window::OnCreate(lpCreateStruct) == -1)
      return -1; */

   
}

bool FileManagerFrame::DestroyBars()
{

   m_toolbar.DestroyWindow();
   m_toolbar.RemoveAllTools();

   return true;
}


bool FileManagerFrame::CreateBars()
{
   ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (GetActiveDocument());
   
   ASSERT(pdoc != NULL);
   ASSERT(base < ::filemanager::document > :: bases(pdoc));

   DestroyBars();

  // CBaseRelation < UINT, UINT, UINT, UINT > * prel;
//   BaseMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
   //m_menuhook.Initialize(
     // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      //NULL,
      //System.font_central().GetMenuFont());

   //m_menuhook.Install(this);

   //UINT uiMenuBar = pdoc->get_filemanager_data()->m_ptemplate->m_uiMenuBar;

//  SetMenu(NULL);

/*    if (!m_menubar.CreateEx(this))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }*/
/*
   if(!m_menubar.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListHueLight(),
      NULL,
      System.font_central().GetMenuFont()) ||
      VMS_FAILED(m_menubar.LoadMenuBar(uiMenuBar)))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }
*/
   string strToolBar = pdoc->get_filemanager_data()->m_ptemplate->m_strToolBar;


   if(strToolBar.is_empty())
   {
      if(pdoc->get_filemanager_data()->is_saving())
      {
         strToolBar = pdoc->get_filemanager_data()->m_strToolBarSave;
      }
      else
      {
         strToolBar = pdoc->get_filemanager_data()->m_strToolBar;
      }
   }

   if (!m_toolbar.CreateEx(this) ||
      !m_toolbar.LoadXmlToolBar(Application.file().as_string(Application.dir().matter(strToolBar))))
   {
      TRACE0("Failed to create toolbar\n");
      return false;      // fail to create
   }



   return true;
}


void FileManagerFrame::install_message_handling(::gen::message::dispatch * pinterface)
{
   simple_frame_window::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SETTEXT, pinterface, this, &FileManagerFrame::_001OnSetText);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &FileManagerFrame::_001OnCreate);
}


void FileManagerFrame::_001OnSetText(gen::signal_object * pobj)
{
//   SCAST_PTR(::gen::message::base, pbase, pobj)

   pobj->previous();

   string str;
   
   FileManagerTabView * ptabview = GetTypedParent < FileManagerTabView >();
   if(ptabview != NULL)
   {
      GetWindowText(str);
      ptabview->SetTitleById(m_idTab, str);
   }
}