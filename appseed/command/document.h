#pragma once

class CLASS_DECL_CA2_COMMAND command_document :
   public ::userbase::document
{
public:


   command_document(::ca::application * papp);
	virtual ~command_document();

   
   DECL_GEN_VSIGNAL(data_on_after_change);

	virtual BOOL on_new_document();

#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif

   BOOL on_open_document(const char * lpszPathName);

};

