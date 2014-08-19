#pragma once


namespace user
{


   class CLASS_DECL_BASE server :
      virtual public ::object
   {
   public:


      virtual sp(::user::document) open_new_document();
      virtual sp(::user::document) open_document_file(sp(::create_context) pcreatecontext);
      virtual sp(::user::document) open_document_file(var varFile = ::var(), bool bMakeVisible = true, sp(::user::interaction) puiParent = NULL);


   };


} // namespace user




