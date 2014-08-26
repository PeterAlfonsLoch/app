#pragma once


namespace filehandler
{


   class CLASS_DECL_sphere document:
      virtual public ::html_document
   {
   public:


      document(sp(::aura::application) papp);
      virtual ~document();


      virtual bool on_new_document();


   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


      virtual bool on_open_document(var varFile);


   };


} // namespace filehandler



