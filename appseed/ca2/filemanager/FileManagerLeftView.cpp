#include "framework.h"
#include "FileManagerFrame.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListView.h"
#include "SimpleFolderListView.h"
#include "SimpleFolderTreeView.h"


FileManagerLeftView::FileManagerLeftView(::ca::application * papp) :
   ca(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
}

FileManagerLeftView::~FileManagerLeftView()
{
}

#ifdef DEBUG
void FileManagerLeftView::assert_valid() const
{
   ::userbase::split_view::assert_valid();
}

void FileManagerLeftView::dump(dump_context & dumpcontext) const
{
   ::userbase::split_view::dump(dumpcontext);
}

#endif //DEBUG


void FileManagerLeftView::on_update(::view * pSender, LPARAM lHint, ::ca::object* phint) 
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
               FileManagerFrame * pframe =dynamic_cast < FileManagerFrame * > ((::ca::window *) GetParentFrame());
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
      System.simple_message_box(NULL, "Could not create folder tree ::view");
   }
   
   plist->m_bStatic = true;

   plist->m_scrollinfo.m_rectMargin.null();

   SetPane(0, plist, false);

   //plist->add_item("V:\\", "votagus");

  filemanager:: SimpleFolderTreeView * pmediaview = create_view < filemanager::SimpleFolderTreeView > ();

   if(pmediaview == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::view");
   }

   SetPane(1, pmediaview, false);

}
