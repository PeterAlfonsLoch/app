#pragma once


namespace userex
{


   class CLASS_DECL_ca2 userex :
      virtual public ::ca::section
   {
   public:


      ::userbase::multiple_document_template *     m_ptemplateForm;
      ::userbase::multiple_document_template *     m_ptemplateChildForm;
      ::userbase::multiple_document_template *     m_ptemplatePlaceHolder;


      userex();
      virtual ~userex();

      form_document *   create_form(::user::form_callback * pcallback, ::user::interaction * pwndParent, var var = ::var(::var::type_empty_argument));
      form_document *   create_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent, var var = ::var(::var::type_empty_argument));
      form_document *   create_child_form(::user::form_callback * pcallback, ::user::interaction * pwndParent, var var = ::var(::var::type_empty_argument));
      form_document *   create_child_form(form_view * pview, ::user::form_callback * pcallback, ::user::interaction * pwndParent, var var = ::var(::var::type_empty_argument));
      ::document * hold(::user::interaction * pui);

      virtual bool initialize1();
      virtual bool initialize2();

   };


} // namespace ca



