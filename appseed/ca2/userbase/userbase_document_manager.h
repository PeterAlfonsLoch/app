#pragma once


namespace userbase
{

   class document_template;
   class document;

   class CLASS_DECL_ca document_manager : 
      virtual public ::document_manager
   {
   public:
      
      
      document_manager(::ax::application * papp);
      virtual ~document_manager();


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };

} // namespace userbase