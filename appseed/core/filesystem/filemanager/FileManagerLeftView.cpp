#include "framework.h"


FileManagerLeftView::FileManagerLeftView(sp(base_application) papp) :
   element(papp),
   ::user::split_layout(papp),
   
   ::user::split_view(papp),
   place_holder_container(papp)
{
}

FileManagerLeftView::~FileManagerLeftView()
{
}

#ifdef DEBUG
void FileManagerLeftView::assert_valid() const
{
   ::user::split_view::assert_valid();
}

void FileManagerLeftView::dump(dump_context & dumpcontext) const
{
   ::user::split_view::dump(dumpcontext);
}

#endif //DEBUG


void FileManagerLeftView::on_update(sp(::user::view) pSender, LPARAM lHint, object* phint) 
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(base < FileManagerViewUpdateHint > :: bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews) && get_pane_count() == 0)
         {
            CreateViews();
         }
         else if(GetFileManager() == puh->m_pmanager)
         {
            if(puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
            {
               string str;
               str.Format("FileManagerFrame(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
               sp(FileManagerFrame) pframe = GetParentFrame();
               if(pframe != NULL)
               {
                  pframe->m_dataid = str;
               }
            }
         }
      }
   }
   
   
}

void FileManagerLeftView::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(orientation_horizontal);
  
   set_position_rate(0, 0.30);

   

   filemanager::SimpleFileListView * plist = create_view < filemanager::SimpleFileListView >();

   if(plist == NULL)
   {
      System.simple_message_box(NULL, "Could not create folder tree ::user::view");
   }
   
   plist->m_bStatic = true;

   plist->m_scrollinfo.m_rectMargin.null();

   SetPane(0, plist, false);

  filemanager:: SimpleFolderTreeView * pmediaview = create_view < filemanager::SimpleFolderTreeView > ();

   if(pmediaview == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::user::view");
   }

   SetPane(1, pmediaview, false);

}
