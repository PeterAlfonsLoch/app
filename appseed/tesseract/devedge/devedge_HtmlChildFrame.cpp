#include "StdAfx.h"
#include "HtmlChildFrame.h"

devedgeHtmlChildFrame::devedgeHtmlChildFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
   IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, this, this, &devedgeHtmlChildFrame::_001OnAppLanguage);
}

devedgeHtmlChildFrame::~devedgeHtmlChildFrame()
{
}



bool devedgeHtmlChildFrame::CreateBars()
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

   string strModuleFolder;
   strModuleFolder = System.get_module_folder();

   if(!spfile->open(System.dir().path(strModuleFolder, "devedge_toolbar.xml"), ::ex1::file::type_text | ::ex1::file::mode_read))
      return false;

   string str;
   spfile->read_full_string(str);

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

bool devedgeHtmlChildFrame::DestroyBars()
{

   m_toolbar.DestroyWindow();
   m_toolbar.RemoveAllTools();

//   m_dialogbar.DestroyWindow();

   return true;
}

bool devedgeHtmlChildFrame::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{
   
//   FileManagerFileListCallback * pcallback = GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;
   /*if(pcallback != NULL && 
      pcallback->GetMenuItemCallback(nID))
   {
      ::fs::item_array itema;
      if(nCode == CN_UPDATE_COMMAND_UI)
      {
         GetSelected(itema);
         pcallback->GetMenuItemUpdate(nID, itema, (cmd_ui *) pExtra);
         return TRUE;
      }
      else
      {
         int nMsg;
         if (nCode != CN_UPDATE_COMMAND_UI)
         {
            nMsg = HIWORD(nCode);
         }

         // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
         if (nMsg == 0)
            nMsg = WM_COMMAND;
         
         if(nMsg == WM_COMMAND)
         {
            GetSelected(itema);
            pcallback->OnMenuItemAction(nID, itema);
            return TRUE;
         }
      }
   }*/
   return simple_child_frame::_001OnCmdMsg(pcmdmsg);
}

void devedgeHtmlChildFrame::OnChangeEditSearch()
{

/*   ::userbase::document * pdoc = GetActiveDocument();

   if(pdoc != NULL)
   {
      FileManagerViewUpdateHint uh;
      uh.set_type(FileManagerViewUpdateHint::TypeFilter);
      string str;
      ::ca::window * pwnd = m_dialogbar.GetDlgItem(IDC_EDIT_SEARCH);
      pwnd->GetWindowText(str);
      uh.m_wstrFilter = str;
      pdoc->update_all_views(
         NULL,
         0,
         &uh);

   }
*/
}

int devedgeHtmlChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
//   if (simple_child_frame::OnCreate(lpCreateStruct) == -1)
//      return -1;

   CreateBars();
   
   //CBaseRelation < UINT, UINT, UINT, UINT > * prel;
//   BaseMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
   //m_menuhook.Initialize(
      //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      //NULL,
      //System.font_central().GetMenuFont());

   //m_menuhook.Install(this);


   //UINT uiMenuBar = pdoc->get_filemanager_data()->m_ptemplate->m_uiMenuBar;

//   SetMenu(NULL);

   m_hMenuDefault = NULL;
   
   return 0;
}


void devedgeHtmlChildFrame::_001OnAppLanguage(gen::signal_object * pobj)
{
   CreateBars();
   pobj->m_bRet = false;
}


FileManagerInterface * devedgeHtmlChildFrame::GetFileManager()
{
   return dynamic_cast <FileManagerInterface *>(GetActiveDocument());
}

/*void devedgeHtmlChildFrame::GetSelected(::fs::item_array &itema)
{
   filemanager::SimpleFileListInterface * plistinterface = dynamic_cast <filemanager::SimpleFileListInterface *>
      (GetActiveView());
   if(plistinterface != NULL)
   {
      plistinterface->GetSelected(itema);
   }
}*/

BOOL devedgeHtmlChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style &= ~WS_BORDER;
   return simple_child_frame::PreCreateWindow(cs);
}
