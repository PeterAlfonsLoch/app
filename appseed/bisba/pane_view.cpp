#include "StdAfx.h"

namespace bisba
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_etranslucency      = TranslucencyPresent;

   }

   pane_view::~pane_view()
   {
   }


#ifdef _DEBUG
   void pane_view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG


   void pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);

   }


   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      add_tab("bisba", ::bisba::PaneViewbisba);
      add_tab("file manager", ::bisba::PaneViewFileManager);

      set_cur_tab_by_id(::bisba::PaneViewbisba);

   }




   void pane_view::on_create_view(::user::view_creator_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case PaneViewbisba:
         {
            ::bisba::document * pdoc = dynamic_cast < ::bisba::document * > (Application.m_ptemplateVideo->open_document_file(NULL, true, this));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view(0);
               pview->on_update(NULL, 0, NULL);
               if(pview != NULL)
               {
                  ::bisba::frame * pframe = dynamic_cast < ::bisba::frame * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                     pviewdata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
                  }
               }
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = Application.GetStdFileManagerTemplate()->OpenChild(&Application, false, true, this);
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }




} // namespace bisba