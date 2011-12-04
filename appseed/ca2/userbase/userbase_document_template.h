#pragma once


namespace userbase
{

   class document;
   class frame_window;

   class CLASS_DECL_ca2 document_template :
      virtual public ::document_template,
      virtual public ::user::document_template_interface
   {
   public:
      document_template(::ca::application * papp, const char * pszMatter, ::ca::type_info & DocClass, ::ca::type_info & pFrameClass, ::ca::type_info & pViewClass);

      virtual ~document_template();


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
      virtual void assert_valid() const;
   #endif
         

   };


} // namespace userbase