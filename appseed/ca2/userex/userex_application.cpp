#include "StdAfx.h"

namespace userex
{

   application::application()
   {
      m_ptemplateForm = NULL;
      //m_ptemplateChildForm = NULL;
      m_ptemplatePlaceHolder = NULL;
   }

   application::~application()
   {
   }


   bool application::initialize1()
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
         System.template type_info < form_document > (),
         System.template type_info < form_frame > (),
         System.template type_info < form_view > ());

      m_ptemplateChildForm = new ::userbase::multiple_document_template(
         this,
         "system/form",
         System.template type_info < form_document > (),
         System.template type_info < form_child_frame > (),
         System.template type_info < form_view > ());

      m_ptemplatePlaceHolder = new ::userbase::multiple_document_template(
         this,
         "system/form",
         System.template type_info < simple_document > (),
         System.template type_info < simple_frame_window > (),
         System.template type_info < user::place_holder > ());


      if(!html::application::initialize1())     
         return false;

      return true;
   }


   form_document * application::create_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent)
   {
      form_document * pdoc;
      if(m_ptemplateForm == NULL)
         return NULL;
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      createcontext->m_pviewAlloc                     = pview;
      pdoc = dynamic_cast < form_document * > (m_ptemplateForm->open_document_file(createcontext));
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   form_document * application::create_form(::user::form_callback * pcallback, ::user::interaction * pwndParent, var var)
   {
      if(pwndParent != NULL && pwndParent->m_papp != this)
      {
         return App(pwndParent->m_papp).create_form(pcallback, pwndParent, var);
      }
      form_document * pdoc;
      if(m_ptemplateForm == NULL)
         return NULL;
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool) var["hold"])
      {
         createcontext->m_bHold                       = false;
      }
         
      pdoc = dynamic_cast < form_document * > (m_ptemplateForm->open_document_file(createcontext));
      ::view * pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform = dynamic_cast < ::user::form * > (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   form_document * application::create_child_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent)
   {
      form_document * pdoc;
      if(m_ptemplateChildForm == NULL)
         return NULL;
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      createcontext->m_pviewAlloc                     = pview;
      pdoc = dynamic_cast < form_document * > (m_ptemplateChildForm->open_document_file(createcontext));
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   form_document * application::create_child_form(::user::form_callback * pcallback, ::user::interaction * pwndParent, var var)
   {
      if(pwndParent != NULL && pwndParent->m_papp != this)
      {
         return App(pwndParent->m_papp).create_child_form(pcallback, pwndParent, var);
      }
      if(m_ptemplateChildForm == NULL)
         return NULL;
      form_document * pdoc;
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      pdoc = dynamic_cast < form_document * > (m_ptemplateChildForm->open_document_file(createcontext));
      ::view * pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform = dynamic_cast < ::user::form * > (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   ::document * application::hold(::user::interaction * pui)
   {

      ::ca::create_context_sp createcontext(get_app());

      createcontext->m_bMakeVisible    = false;
      createcontext->m_bHold           = false;

      simple_document * pdoc = dynamic_cast < simple_document * > (m_ptemplatePlaceHolder->open_document_file(createcontext));

      user::place_holder * pholder = pdoc->get_typed_view < user::place_holder  >();
      
      pholder->hold(pui);

      return pdoc;
   }


} //namespace userex


