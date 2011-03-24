#pragma once

namespace mail
{

   class CLASS_DECL_ca main_document :
      public ::document
   {
   public:
      main_document(::ca::application * papp);

   //virtual void Serialize(CArchive& ar);   // overridden for document i/o
   protected:
      virtual BOOL on_new_document();
   public:
      virtual ~main_document();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);

   };

} // namespace mail