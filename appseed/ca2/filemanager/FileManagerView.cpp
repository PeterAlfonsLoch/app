#include "StdAfx.h"
#include "FileManagerFrame.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListView.h"
#include "SimpleFolderListView.h"
#include "SimpleFolderTreeView.h"



FileManagerAView::FileManagerAView(::ca::application * papp) :
   ca(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
}

FileManagerAView::~FileManagerAView()
{
}

#ifdef _DEBUG
void FileManagerAView::assert_valid() const
{
   ::userbase::split_view::assert_valid();
}

void FileManagerAView::dump(dump_context & dumpcontext) const
{
   ::userbase::split_view::dump(dumpcontext);
}

#endif //_DEBUG


void FileManagerAView::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(base < FileManagerViewUpdateHint >::bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews)
         && get_pane_count() == 0)
         {
            CreateViews();
         }
         else if(GetFileManager() == puh->m_pmanager)
         {
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               string str;
               str.Format("FileManagerFrame(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
               if(pframe != NULL)
               {
                  pframe->m_dataid = str;
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypePop))
            {
               OnActivateFrame(WA_INACTIVE, dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame())));
               GetParentFrame()->ActivateFrame(SW_SHOW);
               OnActivateView(TRUE, this, this);
               RedrawWindow();
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
               if(pframe != NULL)
               {
   //xxx               pframe->WindowDataLoadWindowRect();
        //xxx          pframe->WindowDataEnableSaveWindowRect(true);
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateBars))
            {
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > (GetParentFrame());
               if(pframe != NULL)
               {
                  ASSERT(pframe != NULL);
                  ASSERT(base < FileManagerFrame > :: bases(pframe));
                  pframe->SetActiveView(this);
                  pframe->CreateBars();
               }
               FileManagerMainFrame * pmainframe =dynamic_cast < FileManagerMainFrame * > (GetTopLevelFrame());
               if(pmainframe != NULL)
               {
                  pmainframe->SetActiveView(this);
                  pmainframe->CreateBars();
               }
               FileManagerChildFrame * pchildframe =dynamic_cast < FileManagerChildFrame * > (GetParentFrame());
               if(pchildframe != NULL)
               {
                  ASSERT(pchildframe != NULL);
                  ASSERT(base < FileManagerChildFrame > :: bases(pchildframe));

                  pchildframe->SetActiveView(this);
                  pchildframe->CreateBars();
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSaveAsStart))
            {
               if(!base < FileManagerSaveAsView >::bases(get_pane_window(0)))
               {
                  //::ca::create_context cc;
                  //cc.m_usercreatecontext.m_pCurrentDoc = get_document();
                  //cc.m_usercreatecontext.m_typeinfoNewView =  System.type_info < FileManagerSaveAsView > ();
                  //cc.m_usercreatecontext.m_pCurrentFrame = this;

                  FileManagerSaveAsView * ptopview = create_view < FileManagerSaveAsView > ();
                  if(ptopview == NULL)
                  {
                     System.simple_message_box(NULL, "Could not create folder tree ::view");
                  }
                  ptopview->m_pfilemanagerinterface = GetFileManager();
                  InsertPaneAt(0, ptopview, true);
                  string strName = 
                     System.file().title_(GetFileManager()->get_filemanager_data()->m_pdocumentSave->get_path_name()) 
                  + " - " + System.datetime().international().get_gmt_date_time() 
                  + "." + System.file().extension(GetFileManager()->get_filemanager_data()->m_pdocumentSave->get_path_name());
                  strName.replace(":", "-");
                  strName = System.dir().path(GetFileManager()->get_item().m_strPath, strName);
                  ptopview->_001SetText(strName);
                  GetFileManager()->get_filemanager_data()->m_pmanager->m_strTopic = strName;
                  set_position(0, 49);
                  set_position(1, 49 + 49);
                  layout();
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSaveAsCancel))
            {
               if(base < FileManagerSaveAsView >::bases(get_pane_window(0)))
               {
                  RemovePaneAt(0);
                  set_position(0, 49);
                  layout();
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSaveAsOK))
            {
               ASSERT(GetFileManager()->get_filemanager_data()->m_pdocumentSave != NULL);
               
               string strPath = puh->m_strPath;
               if(strPath.is_empty())
               {
                  string strTitle;
                  dynamic_cast < FileManagerSaveAsView * >(get_pane_window(0))->_001GetText(strTitle);
                  if(System.dir().is(GetFileManager()->get_item().m_strPath))
                  {
                     strPath = System.dir().path(GetFileManager()->get_item().m_strPath, strTitle);
                  }
                  else if(strTitle.has_char())
                  {
                     strPath = System.dir().path(GetFileManager()->get_item().m_strPath, strTitle);
                  }
                  else
                  {
                     strPath = GetFileManager()->get_item().m_strPath;
                  }
               }

               bool bSave = !System.dir().is(strPath);

               if(bSave && System.file().exists(strPath))
               {
                  if(System.simple_message_box(Bergedge.get_document()->get_view(), "Do you want to replace the existing file " + strPath + "?", MB_YESNO) == IDNO)
                  {
                     bSave = false;
                  }
               }
            
               FileManagerViewUpdateHint uh;
            
               if(bSave)
               {
                  if(GetFileManager()->get_filemanager_data()->m_pdocumentSave->do_save(strPath))
                  {
                     uh.set_type(FileManagerViewUpdateHint::TypeSaveAsSaved);
                     uh.m_strPath = strPath;
                  }
                  else
                  {
                     uh.set_type(FileManagerViewUpdateHint::TypeSaveAsSaveFailed);
                  }
               }
               else
               {
                  uh.set_type(FileManagerViewUpdateHint::TypeSaveAsCancel);
               }
               get_document()->update_all_views(NULL, 0, &uh);

               GetFileManager()->get_filemanager_data()->m_pdocumentSave = NULL;

               if(base < FileManagerSaveAsView >::bases(get_pane_window(0)))
               {
                  RemovePaneAt(0);
                  set_position(0, 49);
                  layout();
               }
            }
         }
      }
   }
   
   FileManagerTabView * ptabview = GetParentFrame()->GetTypedParent < FileManagerTabView > ();
   if(ptabview != NULL)
   {
      ptabview->on_update(this, lHint, phint);
   }
   
}

void FileManagerAView::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(orientation_horizontal);
  
   set_position(0, 24);

   

   FileManagerPathView * ptopview = create_view < FileManagerPathView > ();
   if(ptopview == NULL)
   {
      System.simple_message_box(NULL, "Could not create folder tree ::view");
   }
   SetPane(0, ptopview, false);
   //ptopview->CreateViews();


   FileManagerView * pmediaview = create_view < FileManagerView > ();

   if(pmediaview == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::view");
   }
   SetPane(1, pmediaview, false);
   pmediaview->CreateViews();

}



FileManagerView::FileManagerView(::ca::application * papp) :
   ca(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
   m_ppropform = NULL;
}

FileManagerView::~FileManagerView()
{
}


 // BEGIN_MESSAGE_MAP(FileManagerView, ::userbase::split_view)
   //{{AFX_MSG_MAP(FileManagerView)
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileManagerView diagnostics

#ifdef _DEBUG
void FileManagerView::assert_valid() const
{
   ::userbase::split_view::assert_valid();
}

void FileManagerView::dump(dump_context & dumpcontext) const
{
   ::userbase::split_view::dump(dumpcontext);
}

#endif //_DEBUG



void FileManagerView::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(base < FileManagerViewUpdateHint >::bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews)
         && get_pane_count() == 0)
         {
            CreateViews();
         }
         else if(GetFileManager() == puh->m_pmanager)
         {
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               string str;
               str.Format("FileManagerFrame(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
               if(pframe != NULL)
               {
                  pframe->m_dataid = str;
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews)
               && get_pane_count() == 0)
            {
               CreateViews();
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeOpenSelectionProperties))
            {
               OpenSelectionProperties(); 
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypePop))
            {
               OnActivateFrame(WA_INACTIVE, dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame())));
               GetParentFrame()->ActivateFrame(SW_SHOW);
               OnActivateView(TRUE, this, this);
               RedrawWindow();
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
               if(pframe != NULL)
               {
   //xxx               pframe->WindowDataLoadWindowRect();
        //xxx          pframe->WindowDataEnableSaveWindowRect(true);
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateBars))
            {
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
               if(pframe != NULL)
               {
                  ASSERT(pframe != NULL);
                  ASSERT(base < FileManagerFrame > :: bases(pframe));

                  pframe->CreateBars();
               }
               FileManagerMainFrame * pmainframe =dynamic_cast < FileManagerMainFrame * > (GetTopLevelFrame());
               if(pmainframe != NULL)
               {
                  pmainframe->CreateBars();
               }
               FileManagerChildFrame * pchildframe =dynamic_cast < FileManagerChildFrame * > ((::ca::window *) GetParentFrame());
               if(pchildframe != NULL)
               {
                  ASSERT(pchildframe != NULL);
                  ASSERT(base < FileManagerChildFrame > :: bases(pchildframe));


                  pchildframe->CreateBars();
               }
            }
         }
      }
   }
   
   
}

void FileManagerView::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(orientation_vertical);
  
   set_position_rate(0, 0.3);

   

   FileManagerLeftView * pleftview = create_view < FileManagerLeftView > ();

   if(pleftview == NULL)
   {
      System.simple_message_box(NULL, "Could not create folder tree ::view");
   }
   SetPane(0, pleftview, false);
   pleftview->CreateViews();

   m_pfilelist = create_view < filemanager::SimpleFileListView > ();
   
   if(m_pfilelist == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::view");
   }
   SetPane(1, m_pfilelist, false);

   m_ppreview = create_view < filemanager::SimplePreview > ();
   m_ppreview->ShowWindow(SW_HIDE);
}


void FileManagerView::OpenSelectionProperties()
{
   ::fs::item_array itema;
   m_pfilelist->GetSelected(itema);
   if(m_ppropform == NULL)
   {
      m_ppropform = new filemanager::SimpleFilePropertiesForm(get_app());
   }
   ::user::interaction* puie = m_ppropform->open(this, itema);
   if(puie == NULL)
      return;
   SetPane(1, puie, false);
   layout();
}

bool FileManagerView::_001OnCommand(id id)
{
 //  int iPos = -1;
   if(id == "change_view")
   {
      if(m_ppreview->IsWindowVisible())
      {
         SetPane(1, m_pfilelist, false);
         layout();
         m_ppreview->ShowWindow(SW_HIDE);
      }
      else 
      {
         SetPane(1, m_ppreview, false);
         layout();
         m_pfilelist->ShowWindow(SW_HIDE);
      }
      return true;
   }
   return false;   
}

