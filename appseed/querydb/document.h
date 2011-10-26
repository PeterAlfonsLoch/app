#pragma once

namespace querydb
{

   class CLASS_DECL_CA2_QUERYDB document :
      public ::userbase::document
   {
   public:


      string               m_strQuery;
      simpledb::server     m_server;
      var                  m_var;

      document(::ca::application * papp);
	   virtual ~document();

      
      DECL_GEN_VSIGNAL(data_on_after_change)

	   virtual BOOL on_new_document();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool on_open_document(var varFile);


      bool query(const char * pszQuery);
      string get_query_string();

   };

} // namespace querydb