#include "framework.h"


namespace turboc
{


   main_view::main_view(::aura::application * papp):
      element(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

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


   void main_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {
       ::user::split_view::on_update(pSender,lHint,phint);
   }


   void main_view::on_create_views()
   {

      if(get_pane_count() > 0)
         return;

      if(Application.m_bMultiverseChat)
      {

         SetPaneCount(2);

      }

      SetSplitOrientation(orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      if(Application.m_bMultiverseChat)
      {

         m_ptopview = create_view < top_view >(NULL,::null_rect(),NULL,"turboc_top");

         if(m_ptopview == NULL)
         {

            System.simple_message_box(NULL,"Could not create folder edit view");

         }

         SetPane(0,m_ptopview,false);

      }

      //m_pview = create_view < lite_view >();

      m_pview = create_view < view >();

      if(m_pview == NULL)
      {

         System.simple_message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopview->m_pview = m_pview;


      if(Application.m_bMultiverseChat)
      {
         SetPane(1,m_pview,false);

      }

      else
      {
         SetPane(1,m_pview,false);
      }


   }


   
   bool main_view::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "turboc_toggle")
         {

            if(m_pview->m_bLite && !Application.m_bLoadAiFont)
            {

               Application.load_ai_font();

            }

            m_pview->m_bLite = !m_pview->m_bLite;


            m_pview->layout();

         }

      }

      return true;

   }


} // namespace turboc



