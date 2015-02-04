#pragma once


namespace user
{


   class CLASS_DECL_BASE server :
      virtual public ::object
   {
   public:


      virtual ::aura::document * open_new_document();
      virtual ::aura::document * open_document_file(sp(::create) pcreatecontext);
      virtual ::aura::document * open_document_file(var varFile = ::var(), bool bMakeVisible = true, ::user::interaction * puiParent = NULL);


   };


} // namespace user




