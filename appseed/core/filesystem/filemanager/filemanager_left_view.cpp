#include "framework.h"


namespace filemanager
{


   left_view::left_view(sp(base_application) papp) :
      element(papp),
      ::filemanager::data_interface(papp),
      ::user::split_layout(papp),

      ::user::split_view(papp),
      place_holder_container(papp)
   {

   }


   left_view::~left_view()
   {

   }


#ifdef DEBUG
   void left_view::assert_valid() const
   {
      ::user::split_view::assert_valid();
   }

   void left_view::dump(dump_context & dumpcontext) const
   {
      ::user::split_view::dump(dumpcontext);
   }

#endif //DEBUG


   void left_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint)
   {
      
      data_interface::on_update(pSender, lHint, phint);
      
      ::user::split_view::on_update(pSender, lHint, phint);

      if (phint != NULL)
      {
         if (base < update_hint > ::bases(phint))
         {
            update_hint * puh = (update_hint *) phint;
            if (GetFileManager() == puh->m_pmanager)
            {
               if (puh->is_type_of(update_hint::TypeInitialize))
               {
                  string str;
                  str.Format("frame(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
                  sp(frame) pframe = GetParentFrame();
                  if (pframe != NULL)
                  {
                     pframe->m_dataid = str;
                  }
               }
            }
         }
      }


   }

   void left_view::on_create_views()
   {

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position_rate(0, 0.30);



      file_list * plist = create_view < file_list >();

      if (plist == NULL)
      {
         System.simple_message_box(NULL, "Could not create folder tree ::user::impact");
      }

      plist->m_bStatic = true;

      plist->m_scrollinfo.m_rectMargin.null();

      SetPane(0, plist, false);

      ::user::tree * pusertree = create_view < ::user::tree >();

      if (pusertree == NULL)
      {
         System.simple_message_box(NULL, "Could not create file list ::user::impact");
      }

      tree * ptree = new tree(get_app());

      pusertree->merge(ptree, true);

      SetPane(1, pusertree, false);


   }


} // namespace filemanager




