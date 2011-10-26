#include "StdAfx.h"


namespace eluce
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      ::eluce::application * pappEluce = dynamic_cast < ::eluce::application * >(papp);
      pappEluce->m_ppaneview = this;
      m_pviewdataOld = NULL;

      
      m_etranslucency      = TranslucencyPresent;

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;


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

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      
      if(pobj->previous())
         return;

      set_tab("Menu", pane_view_menu);
      set_tab("Image", pane_view_image);
      set_tab("File Manager", "file_manager");

      set_cur_tab_by_id(pane_view_image);

      ::eluce::application * papp = dynamic_cast < ::eluce::application * > (get_app());
      papp->m_ppaneview = this;

   }


   void pane_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);

      if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint *) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeGetView))
            {
               puh->m_eview = (EPaneView) (int) get_view_id();
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
      if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
         }
      }

   }



   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::userbase::view::PreCreateWindow(cs);
   }

   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());

      switch(pcreatordata->m_id)
      {
      case pane_view_image:
         {
            eluce::document * pdoc = dynamic_cast < eluce::document * > (papp->m_ptemplateImage->open_document_file(NULL, true, pcreatordata->m_pholder));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view(0);
               m_peluceview = dynamic_cast < ::eluce::view * > (pview);
               pview->on_update(NULL, 0, NULL);
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
      }
   }

   void pane_view::rotate()
   {
      EPaneView eview = (EPaneView) (int) get_view_id();
      EPaneView eviewNew = pane_view_image;
   }

   void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      
      ::userex::pane_tab_view::install_message_handling(pinterface);

      USER_MESSAGE_LINK(message_create, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &pane_view::_001OnMenuMessage);

   }


} // namespace eluce


