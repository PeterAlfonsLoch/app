#include "StdAfx.h"

namespace md5
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

   void pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {

      ::userex::pane_tab_view::install_message_handling(pinterface);

      USER_MESSAGE_LINK(message_create, pinterface, this, &pane_view::_001OnCreate);

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

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      add_tab("md5", pane_view_md5);
      add_tab("file manager", pane_view_file_manager);

      set_cur_tab_by_id(pane_view_md5);


   }



   void pane_view::on_create_view(view_data * pviewdata)
   {
      ::md5::application * papp = dynamic_cast < ::md5::application * > (get_app());
      switch(pviewdata->m_id)
      {
      case pane_view_md5:
         {
            ::md5::document * pdoc = dynamic_cast < ::md5::document * > (papp->m_ptemplateMd5->open_document_file(NULL, TRUE, this));
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
                     pviewdata->m_eflag.signalize(::user::view_creator::view_data::flag_hide_all_others_on_show);
                  }
               }
            }
         }
         break;
      case pane_view_file_manager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
            if(pdoc != NULL)
            {
               pdoc->m_dataid = "biteditor:filemanager";
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

} // namespace md5