#pragma once


namespace userbase
{


   class document_template;
   class document;


   class CLASS_DECL_ca2 document_manager : 
      virtual public ::document_manager
   {
   public:
      
      
      document_manager(sp(::ca::application) papp);
      virtual ~document_manager();


   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace userbase

