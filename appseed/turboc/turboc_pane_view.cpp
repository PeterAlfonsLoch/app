#include "framework.h"

namespace tc4
{

   pane_view::pane_view(::aura::application * papp) :
      element(papp),
      ::user::tab(papp),

      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::assert_valid() const
   {

	   ::aura::impact::assert_valid();

   }


   void pane_view::dump(dump_context & dumpcontext) const
   {

	   ::aura::impact::dump(dumpcontext);

   }


   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {

      ::userex::pane_tab_view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      set_tab("tc4", ::tc4::PaneViewHelloMultiverse);
      set_tab("switcher",::tc4::PaneViewHelloMultiverseSwitcher);
      set_tab("Open", "file_manager");

      //set_cur_tab_by_id(::tc4::PaneViewHelloMultiverseSwitcher);
      set_cur_tab_by_id(::tc4::PaneViewHelloMultiverse);

   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      switch(pcreatordata->m_id)
      {
      case PaneViewHelloMultiverse:
         {
         Application.m_ptemplateHelloMultiverseView->open_document_file(NULL,true,pcreatordata->m_pholder);


         }

         break;

      case PaneViewHelloMultiverseSwitcher:
      {

         Application.m_ptemplateHelloMultiverseSwitcher->open_document_file(NULL,true,pcreatordata->m_pholder);



      }

         break;

      default:

         break;

      }

      ::userex::pane_tab_view::on_create_view(pcreatordata);

   }




} // namespace tc4
