//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   ::aura::document * server::open_new_document()
   {

      return open_document_file(sp(::create)());

   }


   ::aura::document * server::open_document_file(sp(::create) pcreatecontext)
   {

      sp(::create) cc(canew(::create(Application.creation(), var(var::type_empty), true, NULL)));

      if (pcreatecontext == NULL)
      {
         pcreatecontext = cc;
      }

      request_create(pcreatecontext);

      return pcreatecontext->m_spCommandLine->m_varQuery["document"].cast < ::aura::document >();

   }


   ::aura::document * server::open_document_file(var varFile, bool bMakeVisible, ::user::interaction * puiParent)
   {

      sp(::create) cc(canew(::create(Application.creation(), varFile, bMakeVisible, puiParent)));


      return open_document_file(cc);

   }


} // namespace user



