#include "framework.h"


namespace user
{

   ::user::document_interface * document_request_interface::open_document_file(::ca::create_context * pcreatecontext)
   {

      ::ca::create_context_sp cc(&Application.creation(), var(var::type_empty), true, NULL);

      if(pcreatecontext == NULL)
      {
         pcreatecontext = cc;
      }

      request(pcreatecontext);

      return pcreatecontext->m_spCommandLine->m_varQuery["document"].ca2 < ::user::document_interface > ();

   }

   ::user::document_interface * document_request_interface::open_document_file(var varFile, bool bMakeVisible, ::user::interaction * puiParent)
   {

      ::ca::create_context_sp cc(&Application.creation(), varFile, bMakeVisible, puiParent);


      return open_document_file(cc);

   }

} // namespace user


