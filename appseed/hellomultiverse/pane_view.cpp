#include "StdAfx.h"

namespace hellomultiverse
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

      set_tab("hellomultiverse", ::hellomultiverse::PaneViewHelloMultiverse);
      set_tab("file manager", ::hellomultiverse::PaneViewFileManager);

      set_cur_tab_by_id(::hellomultiverse::PaneViewHelloMultiverse);

   }




   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case PaneViewHelloMultiverse:
         {
            ::hellomultiverse::document * pdoc = dynamic_cast < ::hellomultiverse::document * > (Application.m_ptemplateVideo->open_document_file(NULL, true, pcreatordata->m_pholder));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view(0);
               pview->on_update(NULL, 0, NULL);
               if(pview != NULL)
               {
                  ::hellomultiverse::frame * pframe = dynamic_cast < ::hellomultiverse::frame * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                     pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
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
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
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




} // namespace hellomultiverse