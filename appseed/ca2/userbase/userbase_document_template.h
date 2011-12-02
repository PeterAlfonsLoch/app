#pragma once


namespace userbase
{

   class document;
   class frame_window;

   class CLASS_DECL_ca document_template :
      virtual public ::document_template,
      virtual public ::user::document_template_interface
   {
   public:
      document_template(::ax::application * papp, const char * pszMatter, ::ax::type_info & DocClass, ::ax::type_info & pFrameClass, ::ax::type_info & pViewClass);

      virtual ~document_template();


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
      virtual void assert_valid() const;
   #endif
         

   };


} // namespace userbase