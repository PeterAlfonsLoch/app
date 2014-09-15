#include "framework.h"


namespace filemanager
{


   file_properties_form::file_properties_form(sp(::aura::application) papp) :
      element(papp)
   {
      m_ptemplatePane = new ::user::single_document_template(
         papp,
         "system/auth",
         System.type_info < form_document > (),
         System.type_info < simple_frame_window > (),
         System.type_info < ::userex::pane_tab_view > ());
   }

   file_properties_form::~file_properties_form()
   {
   }

   sp(::user::interaction) file_properties_form::open(sp(::user::interaction) puieParent, ::fs::item_array & itema)
   {
      m_itema = itema;
      if(itema.get_count() <= 0)
         return NULL;
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = puieParent;
      sp(::form_document) pdoc = (m_ptemplatePane->open_document_file(createcontext));
      sp(::userex::pane_tab_view) pview = pdoc->get_typed_view < ::userex::pane_tab_view > ();
      pview->set_view_creator(this);
      m_ptabview = pview;
      pview->add_tab("general", 1);
      pview->add_tab("advanced", 2);
      pview->set_cur_tab_by_id(1);
      return pview->GetParentFrame();
   }

   void file_properties_form::page2()
   {
   }

   void file_properties_form::page1()
   {
      if(!m_pdocGeneral->on_open_document(Application.dir().matter("filemanager/file_properties.html")))
      {
         return;
      }
      if(m_itema.get_count() <= 0)
         return;
      sp(::user::interaction) pui = m_pviewGeneral->get_child_by_name("name");
      sp(text_interface) ptext =  (pui.m_p);
      ptext->_001SetText(System.file().name_(m_itema[0].m_strPath), ::action::source_none);
   }

   void file_properties_form::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case 1:
         {
            m_pdocGeneral = System.Platform.userex()->create_form(this, m_ptabview);
            if(m_pdocGeneral != NULL)
            {
               m_pviewGeneral = m_pdocGeneral->get_typed_view < form_view > ();
               m_pviewGeneral->m_pcallback = this;
               pcreatordata->m_pdoc = m_pdocGeneral;
               pcreatordata->m_pwnd = m_pviewGeneral->GetParentFrame();
            }
         }
         break;
      case 2:
         {
            /*if(m_netcfg.create(m_ptabview))
            {
               pcreatordata->m_pdoc = m_netcfg.m_pdoc;
               pcreatordata->m_pwnd = m_netcfg.m_pview->GetParentFrame();
            }*/

         }
         break;
      }
      if(pcreatordata->m_pwnd != NULL)
      {
         pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
      }

   }

   void file_properties_form::on_show_view()
   {
      switch(get_view_id())
      {
      case 1:
         {
            page1();
         }
         break;
      case 2:
         {
            //m_netcfg.on_show();
         }
         break;
      }
   }

   bool file_properties_form::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
         }
      }
      return false;

   }


} // namespace filemanager


