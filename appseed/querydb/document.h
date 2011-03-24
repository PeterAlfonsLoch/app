#pragma once

namespace querydb
{

   class CLASS_DECL_CA2_QUERYDB document :
      public ::userbase::document
   {
   public:


      document(::ca::application * papp);
	   virtual ~document();

      
      DECL_GEN_VSIGNAL(data_on_after_change)

	   virtual BOOL on_new_document();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      BOOL on_open_document(const char * lpszPathName);

   };

} // namespace querydb