#include "framework.h"


namespace userex
{


   userex::userex()
   {

      m_ptemplateForm = ::null();
      //m_ptemplateChildForm = ::null();
      m_ptemplatePlaceHolder = ::null();

   }


   userex::~userex()
   {

   }


   bool userex::initialize1()
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



      if(!::ca::section::initialize1())
         return false;

      return true;
   }


   bool userex::initialize2()
   {


      if(!::ca::section::initialize2())
         return false;

      m_ptemplateForm = new ::userbase::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < form_document > (),
         System.type_info < form_frame > (),
         System.type_info < form_view > ());

      m_ptemplateChildForm = new ::userbase::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < form_document > (),
         System.type_info < form_child_frame > (),
         System.type_info < form_view > ());

      m_ptemplatePlaceHolder = new ::userbase::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < simple_document > (),
         System.type_info < simple_frame_window > (),
         System.type_info < user::place_holder > ());


      return true;


   }



   sp(::form_document) userex::create_form(form_view * pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {
      sp(::form_document) pdoc;
      if(m_ptemplateForm == ::null())
         return ::null();
      sp(::ca::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      createcontext->m_pviewAlloc                     = pview;

      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool) var["hold"])
      {
         createcontext->m_bHold                       = false;
      }

      pdoc = (m_ptemplateForm->open_document_file(createcontext));
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   sp(::form_document) userex::create_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {
      if(pwndParent != ::null() && pwndParent->m_papp != get_app())
      {
         return App(pwndParent->m_papp).userex().create_form(pcallback, pwndParent, var);
      }
      sp(::form_document) pdoc;
      if(m_ptemplateForm == ::null())
         return ::null();
      sp(::ca::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool) var["hold"])
      {
         createcontext->m_bHold                       = false;
      }

      pdoc = (m_ptemplateForm->open_document_file(createcontext));
      ::view * pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform = dynamic_cast < ::html_form * > (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   sp(::form_document) userex::create_child_form(form_view * pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {
      sp(::form_document) pdoc;
      if(m_ptemplateChildForm == ::null())
         return ::null();
      sp(::ca::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      createcontext->m_pviewAlloc                     = pview;

      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool) var["hold"])
      {
         createcontext->m_bHold                       = false;
      }

      pdoc = (m_ptemplateChildForm->open_document_file(createcontext));
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   sp(::form_document) userex::create_child_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {
      if(pwndParent != ::null() && pwndParent->m_papp != get_app())
      {
         return App(pwndParent->m_papp).userex().create_child_form(pcallback, pwndParent, var);
      }
      if(m_ptemplateChildForm == ::null())
         return ::null();
      sp(::form_document) pdoc;
      sp(::ca::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      pdoc = (m_ptemplateChildForm->open_document_file(createcontext));
      ::view * pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform = dynamic_cast < ::html_form * > (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   sp(::document) userex::hold(sp(::user::interaction) pui)
   {

      sp(::ca::create_context) createcontext(allocer());

      createcontext->m_bMakeVisible    = false;
      createcontext->m_bHold           = false;

      sp(simple_document) pdoc =  (m_ptemplatePlaceHolder->open_document_file(createcontext));

      sp(::user::place_holder) pholder = pdoc->get_typed_view < user::place_holder  >();

      pholder->hold(pui);

      return pdoc;
   }


} //namespace userex


