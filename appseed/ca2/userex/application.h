#pragma once


namespace userex
{


   class CLASS_DECL_ca2 application :
      virtual public ::html::application
   {
   public:


      ::userbase::multiple_document_template *     m_ptemplateForm;
      ::userbase::multiple_document_template *     m_ptemplateChildForm;
      ::userbase::multiple_document_template *     m_ptemplatePlaceHolder;


      application();
      virtual ~application();

      form_document *   create_form(::user::form_callback * pcallback, ::user::interaction * pwndParent, var var = gen::g_emptyargumentconst);
      form_document *   create_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent);
      form_document *   create_child_form(::user::form_callback * pcallback, ::user::interaction * pwndParent, var var = gen::g_emptyargumentconst);
      form_document *   create_child_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent);
      ::document * hold(::user::interaction * pui);

      virtual bool initialize1();

   };


} // namespace ca



