#pragma once


namespace user
{

   class CLASS_DECL_ca document_request_interface :
      virtual public ::gen::object
   {
   public:

     
      virtual ::user::document_interface * open_document_file(::ca::create_context * pcreatecontext);
      virtual ::user::document_interface * open_document_file(var varFile = ::var(), bool bMakeVisible = true, ::user::interaction * puiParent = NULL);


   };

} // namespace user


