#include "framework.h"



FileManagerAView::FileManagerAView(sp(::ca::application) papp) :
   ca(papp),
   ::user::split_layout(papp),
   
   ::user::split_view(papp),
   place_holder_container(papp)
{
}

FileManagerAView::~FileManagerAView()
{
}

#ifdef DEBUG
void FileManagerAView::assert_valid() const
{
   ::user::split_view::assert_valid();
}

void FileManagerAView::dump(dump_context & dumpcontext) const
{
   ::user::split_view::dump(dumpcontext);
}

#endif //DEBUG


void FileManagerAView::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object* phint)
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   if(phint != ::null())
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
               sp(FileManagerFrame) pframe = ((sp(::ca::window)) GetParentFrame());
               if(pframe != ::null())
               {
                  pframe->m_dataid = str;
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypePop))
            {
               OnActivateFrame(WA_INACTIVE, ( (GetParentFrame())));
               GetParentFrame()->ActivateFrame(SW_SHOW);
               OnActivateView(TRUE, this, this);
               RedrawWindow();
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateBars))
            {
               sp(FileManagerFrame) pframe = (GetParentFrame());
               if(pframe != ::null())
               {
                  ASSERT(pframe != ::null());
                  ASSERT(base < FileManagerFrame > :: bases(pframe));
                  pframe->SetActiveView(this);
                  pframe->CreateBars();
               }
               sp(FileManagerMainFrame) pmainframe = (GetTopLevelFrame());
               if(pmainframe != ::null())
               {
                  pmainframe->SetActiveView(this);
                  pmainframe->CreateBars();
               }
               sp(FileManagerChildFrame) pchildframe = (GetParentFrame());
               if(pchildframe != ::null())
               {
                  ASSERT(pchildframe != ::null());
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
                  if(ptopview == ::null())
                  {
                     System.simple_message_box(::null(), "Could not create folder tree ::user::view");
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
               ASSERT(GetFileManager()->get_filemanager_data()->m_pdocumentSave != ::null());

               string strPath = puh->m_strPath;
               if(strPath.is_empty())
               {
                  string strTitle;
                  dynamic_cast < FileManagerSaveAsView * >(get_pane_window(0).m_p)->_001GetText(strTitle);
                  if(System.dir().name(strTitle).has_char() && GetFileManagerDoc()->get_fs_data()->is_dir(System.dir().name(strTitle)))
                  {
                     strPath = strTitle;
                  }
                  else if(GetFileManagerDoc()->get_fs_data()->is_dir(GetFileManager()->get_item().m_strPath))
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

               bool bSave = !Application.dir().is(strPath);

               if(bSave && GetFileManagerDoc()->get_fs_data()->file_exists(strPath))
               {
                  if(System.simple_message_box(Session.get_view(), "Do you want to replace the existing file " + strPath + "?", MB_YESNO) == IDNO)
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
               get_document()->update_all_views(::null(), 0, &uh);

               GetFileManager()->get_filemanager_data()->m_pdocumentSave = ::null();

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
   if(ptabview != ::null())
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
   if(ptopview == ::null())
   {
      System.simple_message_box(::null(), "Could not create folder tree ::user::view");
   }
   SetPane(0, ptopview, false);
   //ptopview->CreateViews();


   FileManagerView * pmediaview = create_view < FileManagerView > ();

   if(pmediaview == ::null())
   {
      System.simple_message_box(::null(), "Could not create file list ::user::view");
   }
   SetPane(1, pmediaview, false);
   pmediaview->CreateViews();

}



FileManagerView::FileManagerView(sp(::ca::application) papp) :
   ca(papp),
   ::user::split_layout(papp),
   
   ::user::split_view(papp),
   place_holder_container(papp)
{
   m_ppropform = ::null();
}

FileManagerView::~FileManagerView()
{
}


 // BEGIN_MESSAGE_MAP(FileManagerView, ::user::split_view)
   //{{__MSG_MAP(FileManagerView)
   //}}__MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileManagerView diagnostics

#ifdef DEBUG
void FileManagerView::assert_valid() const
{
   ::user::split_view::assert_valid();
}

void FileManagerView::dump(dump_context & dumpcontext) const
{
   ::user::split_view::dump(dumpcontext);
}

#endif //DEBUG



void FileManagerView::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca::object* phint)
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   if(phint != ::null())
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
               sp(FileManagerFrame) pframe = ((sp(::ca::window)) GetParentFrame());
               if(pframe != ::null())
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
               OnActivateFrame(WA_INACTIVE, ( (GetParentFrame())));
               GetParentFrame()->ActivateFrame(SW_SHOW);
               OnActivateView(TRUE, this, this);
               RedrawWindow();
               sp(FileManagerFrame) pframe = ((sp(::ca::window)) GetParentFrame());
               if(pframe != ::null())
               {
   //xxx               pframe->WindowDataLoadWindowRect();
        //xxx          pframe->WindowDataEnableSaveWindowRect(true);
               }
            }
            else if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateBars))
            {
               sp(FileManagerFrame) pframe = ((sp(::ca::window)) GetParentFrame());
               if(pframe != ::null())
               {
                  ASSERT(pframe != ::null());
                  ASSERT(base < FileManagerFrame > :: bases(pframe));

                  pframe->CreateBars();
               }
               sp(FileManagerMainFrame) pmainframe = (GetTopLevelFrame());
               if(pmainframe != ::null())
               {
                  pmainframe->CreateBars();
               }
               sp(FileManagerChildFrame) pchildframe = ((sp(::ca::window)) GetParentFrame());
               if(pchildframe != ::null())
               {
                  ASSERT(pchildframe != ::null());
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

   if(pleftview == ::null())
   {
      System.simple_message_box(::null(), "Could not create folder tree ::user::view");
   }
   SetPane(0, pleftview, false);
   pleftview->CreateViews();

   m_pfilelist = create_view < filemanager::SimpleFileListView > ();

   if(m_pfilelist == ::null())
   {
      System.simple_message_box(::null(), "Could not create file list ::user::view");
   }
   SetPane(1, m_pfilelist, false);

   m_ppreview = create_view < filemanager::SimplePreview > ();
   m_ppreview->ShowWindow(SW_HIDE);
}


void FileManagerView::OpenSelectionProperties()
{
   ::fs::item_array itema;
   m_pfilelist->GetSelected(itema);
   if(m_ppropform == ::null())
   {
      m_ppropform = new filemanager::SimpleFilePropertiesForm(get_app());
   }
   sp(::user::interaction) puie = m_ppropform->open(this, itema);
   if(puie == ::null())
      return;
   SetPane(1, puie, false);
   layout();
}

bool FileManagerView::_001OnCommand(id id)
{
 //  int32_t iPos = -1;
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

