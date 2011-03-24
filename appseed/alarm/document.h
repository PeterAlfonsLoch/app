#pragma once

namespace alarm
{

   class CLASS_DECL_CA2_ALARM document :
      public ::userbase::document
   {
   public:

      
      document(::ca::application * papp);
	   virtual ~document();
	   

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

	   virtual BOOL on_new_document();
      BOOL on_open_document(const char * lpszPathName);

   };


} // namespace alarm