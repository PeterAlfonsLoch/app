#pragma once

namespace userbase
{

   class CLASS_DECL_ca multiple_document_template :
      virtual public document_template,
      virtual public ::multiple_document_template
   {
   public:
      multiple_document_template(::ax::application * papp, const char * pszMatter, ::ax::type_info pDocClass, ::ax::type_info pFrameClass, ::ax::type_info pViewClass);
      virtual ~multiple_document_template();

      void reload_template();


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
      virtual void assert_valid() const;
   #endif


   };

} // namespace userbase

