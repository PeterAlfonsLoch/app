#pragma once

class CLASS_DECL_CA2_WINSHELLLINK winshelllink_document :
   public ::userbase::document
{
public:
	winshelllink_document(::ca::application * papp);  
   
   DECL_GEN_VSIGNAL(data_on_after_change)

	virtual BOOL on_new_document();
public:
	virtual ~winshelllink_document();
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

   BOOL on_open_document(const char * lpszPathName);

};

