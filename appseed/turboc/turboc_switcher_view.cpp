#include "framework.h"


namespace tc4
{


   switcher_view::switcher_view(::aura::application * papp):
      element(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

   }


   switcher_view::~switcher_view()
   {

   }


   void switcher_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void switcher_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void switcher_view::on_update(::aura::impact * pSender,LPARAM lHint,object* phint)
   {
      ::user::split_view::on_update(pSender,lHint,phint);
   }


   void switcher_view::on_create_views()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_view < top_view >(NULL,::null_rect(),NULL,"switcher_top");

      if(m_ptopview == NULL)
      {

         System.simple_message_box(NULL,"Could not create folder edit view");

      }

      SetPane(0,m_ptopview,false);

      m_pview = create_view < lite_view >();

      m_pview->m_bAlternate = true;

      if(m_pview == NULL)
      {

         System.simple_message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopview->m_pview = m_pview;


      SetPane(1,m_pview,false);


   }



   bool switcher_view::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "switcher_toggle")
         {

            sp(view) pview = m_pview;

            if(base_class < lite_view >::bases(pview))
            {

               m_pview = create_view < full_view >();

            }
            else
            {

               m_pview = create_view < lite_view >();

            }

            if(m_pview == NULL)
            {

               System.simple_message_box(NULL,"Could not create file list ::aura::impact");

            }

            m_pview->m_bAlternate = true;

            m_ptopview->m_pview = m_pview;

            SetPane(1,m_pview,false);

            pview->DestroyWindow();
            
         }

      }

      return true;

   }

} // namespace tc4



