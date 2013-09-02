#pragma once


namespace user
{

   class CLASS_DECL_ca2 document_request_interface :
      virtual public object
   {
   public:

     
      virtual sp(::user::document_interface) open_new_document();
      virtual sp(::user::document_interface) open_document_file(sp(::ca2::create_context) pcreatecontext);
      virtual sp(::user::document_interface) open_document_file(var varFile = ::var(), bool bMakeVisible = true, sp(::user::interaction) puiParent = NULL);


   };

} // namespace user


