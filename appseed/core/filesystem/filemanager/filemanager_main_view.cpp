#include "framework.h"


namespace filemanager
{


   main_view::main_view(sp(::aura::application) papp):
      element(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

         m_ppropform = NULL;

      }


   main_view::~main_view()
   {

   }


   void main_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void main_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void main_view::on_update(sp(::user::impact) pSender,LPARAM lHint,object* phint)
   {
      ::filemanager:: impact::on_update(pSender,lHint,phint);
      ::user::split_view::on_update(pSender,lHint,phint);
      if(phint != NULL)
      {
         if(base_class < update_hint >::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if(get_filemanager_manager() == puh->m_pmanager)
            {
               if(puh->is_type_of(update_hint::TypeInitialize))
               {
                  string str;
                  str.Format("::frame(%d,%d)",get_filemanager_data()->m_iTemplate,get_filemanager_data()->m_iDocument);
                  sp(frame) pframe = ((::window_sp) GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->m_dataid = str;
                  }

               }
               else if(puh->is_type_of(update_hint::TypeOpenSelectionProperties))
               {
                  OpenSelectionProperties();
               }
               else if(puh->is_type_of(update_hint::TypePop))
               {
                  OnActivateFrame(WA_INACTIVE,((GetParentFrame())));
                  GetParentFrame()->ActivateFrame(SW_SHOW);
                  OnActivateView(TRUE,this,this);
                  RedrawWindow();
                  sp(frame) pframe = ((::window_sp) GetParentFrame());
                  if(pframe != NULL)
                  {
                     //xxx               pframe->WindowDataLoadWindowRect();
                     //xxx          pframe->WindowDataEnableSaveWindowRect(true);
                  }
               }
               else if(puh->is_type_of(update_hint::TypeCreateBars))
               {

                  sp(simple_frame_window) pframe = GetParentFrame();

                  if(pframe != NULL)
                  {

                     pframe->create_bars();

                  }

               }

            }

         }

      }

   }


   void main_view::on_create_views()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0,0.3);

      initialize_split_layout();

      left_view * pleftview = create_view < left_view >();

      if(pleftview == NULL)
      {

         System.simple_message_box(NULL,"Could not create folder tree ::user::impact");

      }

      SetPane(0,pleftview,false);

      pleftview->create_views();

      m_pfilelist = create_view < file_list >();

      if(m_pfilelist == NULL)
      {

         System.simple_message_box(NULL,"Could not create file list ::user::impact");

      }

      SetPane(1,m_pfilelist,false);

      m_ppreview = create_view < preview >();

      m_ppreview->ShowWindow(SW_HIDE);

   }


   void main_view::OpenSelectionProperties()
   {
      ::fs::item_array itema;
      m_pfilelist->GetSelected(itema);
      if(m_ppropform == NULL)
      {
         m_ppropform = new file_properties_form(get_app());
      }
      sp(::user::interaction) puie = m_ppropform->open(this,itema);
      if(puie == NULL)
         return;
      SetPane(1,puie,false);
      layout();
   }

   bool main_view::on_simple_action(id id)
   {
      //  int32_t iPos = -1;
      if(id == "change_view")
      {
         if(m_ppreview->IsWindowVisible())
         {
            SetPane(1,m_pfilelist,false);
            layout();
            m_ppreview->ShowWindow(SW_HIDE);
         }
         else
         {
            SetPane(1,m_ppreview,false);
            layout();
            m_pfilelist->ShowWindow(SW_HIDE);
         }
         return true;
      }
      return false;
   }



} // namespace filemanager



