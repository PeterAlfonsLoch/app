#include "framework.h"


namespace user
{

   sp(::user::document_interface) document_request_interface::open_new_document()
   {
      return open_document_file(sp(::ca::create_context)());
   }

   sp(::user::document_interface) document_request_interface::open_document_file(sp(::ca::create_context) pcreatecontext)
   {

      sp(::ca::create_context) cc(canew(::ca::create_context(Application.creation(), var(var::type_empty), true, NULL)));

      if(pcreatecontext == NULL)
      {
         pcreatecontext = cc;
      }

      request_create(pcreatecontext);

      return pcreatecontext->m_spCommandLine->m_varQuery["document"].ca < ::user::document_interface > ();

   }

   sp(::user::document_interface) document_request_interface::open_document_file(var varFile, bool bMakeVisible, sp(::user::interaction) puiParent)
   {

      sp(::ca::create_context) cc(canew(::ca::create_context(Application.creation(), varFile, bMakeVisible, puiParent)));


      return open_document_file(cc);

   }

} // namespace user


