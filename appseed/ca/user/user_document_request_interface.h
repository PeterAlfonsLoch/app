#pragma once


namespace user
{

   class CLASS_DECL_ca document_request_interface :
      virtual public ::ca::object
   {
   public:

     
      virtual sp(::user::document_interface) open_document_file(sp(::ca::create_context) pcreatecontext);
      virtual sp(::user::document_interface) open_document_file(var varFile = ::var(), bool bMakeVisible = true, sp(::user::interaction) puiParent = ::null());


   };

} // namespace user


