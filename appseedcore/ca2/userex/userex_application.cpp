#include "StdAfx.h"

namespace userex
{

   application::application()
   {
      m_ptemplateForm = NULL;
      m_ptemplateChildForm = NULL;
      m_ptemplatePlaceHolder = NULL;
   }

   application::~application()
   {
   }


   bool application::initialize()
   {
      // menu
      System.factory().creatable_small < menu_document > ();
      System.factory().creatable_small < menu_frame > ();
      System.factory().creatable_small < menu_view > ();

      // form
      System.factory().creatable_small < form_document > ();
      System.factory().creatable_small < ::userex::pane_tab_view > ();
      System.factory().creatable_small < form_frame > ();
      System.factory().creatable_small < form_child_frame > ();
      System.factory().creatable_small < form_view > ();

      System.factory().creatable_small < ::userex::hour_list_view > ();
      System.factory().creatable_small < ::userex::minute_list_view > ();
      System.factory().creatable_small < ::userex::second_list_view > ();

      m_ptemplateForm = new ::userbase::multiple_document_template(
         this,
         "system/form",
         &typeid(form_document),
         &typeid(form_frame),
         &typeid(form_view));

      m_ptemplateChildForm = new ::userbase::multiple_document_template(
         this,
         "system/form",
         &typeid(form_document),
         &typeid(form_child_frame),
         &typeid(form_view));

      m_ptemplatePlaceHolder = new ::userbase::multiple_document_template(
         this,
         "system/form",
         &typeid(simple_document),
         &typeid(simple_frame_window),
         &typeid(user::place_holder));


      if(!html::application::initialize())     
         return false;

      return true;
   }


   form_document * application::create_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent)
   {
      form_document * pdoc;
      if(pwndParent == NULL || pwndParent == System.m_puiInitialPlaceHolderContainer)
      {
         if(m_ptemplateForm == NULL)
            return NULL;
         pdoc = dynamic_cast < form_document * > (m_ptemplateForm->open_document_file(NULL, FALSE, pwndParent, pview));
      }
      else
      {
         if(m_ptemplateChildForm == NULL)
            return NULL;
         pdoc = dynamic_cast < form_document * > (m_ptemplateChildForm->open_document_file(NULL, FALSE, pwndParent, pview));
      }
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   form_document * application::create_form(::user::form_callback * pcallback, ::user::interaction * pwndParent)
   {
      form_document * pdoc;
      if(pwndParent == NULL || pwndParent == System.m_puiInitialPlaceHolderContainer)
      {
         if(m_ptemplateForm == NULL)
            return NULL;
         pdoc = dynamic_cast < form_document * > 
            (m_ptemplateForm->open_document_file(NULL, FALSE, pwndParent));
      }
      else
      {
         if(m_ptemplateChildForm == NULL)
            return NULL;
         pdoc = dynamic_cast < form_document * > 
            (m_ptemplateChildForm->open_document_file(NULL, FALSE, pwndParent));
      }
      ::view * pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform = dynamic_cast < ::user::form * > (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   simple_document * application::hold(::user::interaction * pui)
   {
      simple_document * pdoc = dynamic_cast < simple_document * > (m_ptemplatePlaceHolder->open_document_file(NULL, FALSE, System.m_puiInitialPlaceHolderContainer));
      user::place_holder * pholder = pdoc->get_typed_view < user::place_holder  >();
      pholder->hold(pui);
      return pdoc;
   }

} //namespace userex