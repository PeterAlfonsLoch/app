#pragma once

namespace tarsila
{

   class CLASS_DECL_CA2_TESSERACT document:
      public ::userbase::document
   {
   public:


      document(::ca::application * papp);
      virtual ~document();


      virtual BOOL on_new_document();

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace tarsila 