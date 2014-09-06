#include "axis/user/user.h"


namespace user
{


   sp(::user::document) server::open_new_document()
   {
      return open_document_file(sp(::create_context)());
   }

   sp(::user::document) server::open_document_file(sp(::create_context) pcreatecontext)
   {

      sp(::create_context) cc(canew(::create_context(Application.creation(), var(var::type_empty), true, NULL)));

      if (pcreatecontext == NULL)
      {
         pcreatecontext = cc;
      }

      request_create(pcreatecontext);

      return pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < ::user::document >();

   }

   sp(::user::document) server::open_document_file(var varFile, bool bMakeVisible, sp(::user::interaction) puiParent)
   {

      sp(::create_context) cc(canew(::create_context(Application.creation(), varFile, bMakeVisible, puiParent)));


      return open_document_file(cc);

   }


} // namespace user



