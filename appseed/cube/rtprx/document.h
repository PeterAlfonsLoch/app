#pragma once

namespace rtprx
{

   class CLASS_DECL_CA2_CUBE document:
      virtual public ::userbase::document,
      virtual public mediaplay::document 
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

      virtual bool on_open_document(var varFile);

   };

} // namespace rtprx 