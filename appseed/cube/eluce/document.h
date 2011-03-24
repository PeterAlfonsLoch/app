#pragma once

namespace eluce
{

   class CLASS_DECL_CA2_CUBE document:
      public ::userbase::document
   {
   public:
      document(::ca::application * papp);

      virtual BOOL on_new_document();
   public:
      virtual ~document();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace eluce 