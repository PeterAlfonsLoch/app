#pragma once

namespace mplite
{

   class CLASS_DECL_CA2_CUBE command_document :
      public form_document
   {
   public:

      command_document(::ca::application * papp);
      virtual ~command_document();

      
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace mplite