#include "StdAfx.h"


namespace filemanager
{


   SimpleFilePropertiesForm::SimpleFilePropertiesForm(::ca::application * papp) :
      ca(papp)
   {
      m_ptemplatePane = new ::userbase::single_document_template(
         papp,
         "system/auth",
         ::ca::get_type_info < form_document > (),
         ::ca::get_type_info < simple_frame_window > (),
         ::ca::get_type_info < ::userex::pane_tab_view > ());
   }

   SimpleFilePropertiesForm::~SimpleFilePropertiesForm()
   {
   }

   ::user::interaction * SimpleFilePropertiesForm::open(::user::interaction * puieParent, ::fs::item_array & itema)
   {
      m_itema = itema;
      if(itema.get_count() <= 0)
         return NULL;
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible = false;
      createcontext->m_puiParent = puieParent;
      form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(createcontext));
      ::userex::pane_tab_view * pview = pdoc->get_typed_view < ::userex::pane_tab_view > ();
      pview->set_view_creator(this);
      m_ptabview = pview;
      pview->add_tab("general", 1);
      pview->add_tab("advanced", 2);
      pview->set_cur_tab_by_id(1);
      return pview->GetParentFrame();
   }

   void SimpleFilePropertiesForm::page2()
   {
   }

   void SimpleFilePropertiesForm::page1()
   {
      if(!m_pdocGeneral->on_open_document(Application.dir().matter("filemanager/file_properties.html")))
      {
         return;
      }
      if(m_itema.get_count() <= 0)
         return;
      ::user::interaction * pguie = m_pviewGeneral->GetChildByName("name");
      text_interface * ptext = dynamic_cast < text_interface * > (pguie);
      ptext->_001SetText(System.file().name_(m_itema[0].m_strPath));
   }

   void SimpleFilePropertiesForm::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case 1:
         {
            m_pdocGeneral = Cube.create_form(this, m_ptabview);
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

   void SimpleFilePropertiesForm::on_show_view()
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

   bool SimpleFilePropertiesForm::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
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


