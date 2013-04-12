#pragma once


namespace userex
{


   class CLASS_DECL_ca2 userex :
      virtual public ::ca::section
   {
   public:


      sp(::userbase::multiple_document_template)     m_ptemplateForm;
      sp(::userbase::multiple_document_template)     m_ptemplateChildForm;
      sp(::userbase::multiple_document_template)     m_ptemplatePlaceHolder;


      userex();
      virtual ~userex();

      sp(::form_document)   create_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_form(sp(form_view) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_child_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_child_form(sp(form_view) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::document) hold(sp(::user::interaction) pui);

      virtual bool initialize1();
      virtual bool initialize2();

   };


} // namespace ca



