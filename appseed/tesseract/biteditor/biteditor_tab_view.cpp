#include "StdAfx.h"
#include "tab_view.h"
#include "biteditor_application.h"
#include "biteditor_view.h"
#include "biteditor_document.h"
#include "front_document.h"

namespace biteditor
{

   tab_view::tab_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_etranslucency      = TranslucencyPresent;

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

   /*   ::userbase::single_document_template* pdoctemplate;
      pdoctemplate = new ::userbase::single_document_template(
         IDR_ALBUM,
         ::ca::get_type_info < MediaLibraryDoc > (),
         ::ca::get_type_info < MediaLibraryChildFrame > (),
         ::ca::get_type_info < ::mplite::library::view > ());
      m_pdoctemplateAlbum = pdoctemplate;

      pdoctemplate = new ::userbase::single_document_template(
         IDR_ALBUM,
         ::ca::get_type_info < OptionsDoc > (),
         ::ca::get_type_info < OptionsChildFrame > (),
         ::ca::get_type_info < OptionsView > ());

      
      m_pdoctemplateOptions = pdoctemplate;

      pdoctemplate = new ::userbase::single_document_template(
         IDR_ALBUM,
         ::ca::get_type_info < GoodMixerDoc > (),
         ::ca::get_type_info < simple_child_frame > (),
         ::ca::get_type_info < MixerMainView > ());

      m_pdoctemplateAudioControl = pdoctemplate;*/
      

   }

   tab_view::~tab_view()
   {
   }

   void tab_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tab_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &tab_view::_001OnMenuMessage);
   }



#ifdef _DEBUG
   void tab_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG


   void tab_view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      add_tab("bit editor", pane_view_bit_editor);
      add_tab("file manager", pane_view_file_manager);

      set_cur_tab_by_id(pane_view_bit_editor);

   }



   void tab_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      biteditor_application * papp = dynamic_cast < biteditor_application * > (get_app());
      switch(pcreatordata->m_id)
      {
      case pane_view_context_menu:
         {
            ::ca::create_context_sp cc(get_app());
            cc->m_spCommandLine->m_varFile = "http://localhost:10011/";
            front_document * pdoc = dynamic_cast < front_document * > ((dynamic_cast < biteditor_application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app()))->m_ptemplateFront->open_document_file(cc));
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
         
   /*         create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  ::ca::get_type_info < ::userbase::menu_list_view > ();

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (CreateView(&cc, 101, this));
            if(pview != NULL)
            {
               ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
               pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
               pmenuview->m_wnd.m_bAutoClose = false;
               pcreatordata = new ViewData();
               pcreatordata->m_eview = eview;
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }*/
      case pane_view_bit_editor:
         {
            ::ca::create_context_sp cc(get_app());
            cc->m_puiParent = this;
            biteditor_document * pdoc = dynamic_cast < biteditor_document * > (papp->m_ptemplate_devedge->open_document_file(cc));
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
                     pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
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
               pdoc->Initialize(true);
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

} // namespace biteditor