#pragma once

class CLASS_DECL_CA2_LOGINSTARTUP loginstartup_document :
   public BaseDocument
{
public:
   loginstartup_document(::ca::application * papp);   
   
   DECL_GEN_VSIGNAL(data_on_after_change)

	virtual BOOL OnNewDocument();
public:
	virtual ~loginstartup_document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif

   BOOL on_open_document(const char * lpszPathName);

};

