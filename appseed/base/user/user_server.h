#pragma once


namespace user
{


   class interaction;


   class CLASS_DECL_BASE server :
      virtual public ::object
   {
   public:


      virtual sp(::user::object) open_new_document();
      virtual sp(::user::object) open_document_file(sp(::create_context) pcreatecontext);
      virtual sp(::user::object) open_document_file(var varFile = ::var(), bool bMakeVisible = true, sp(::user::interaction) puiParent = NULL);


   };


} // namespace user




