#pragma once

class CLASS_DECL_CA2_WINSERVICE_1 winservice_1_document :
   public BaseDocument
{
public:
	winservice_1_document();  
   
   DECL_GEN_VSIGNAL(data_on_after_change)

	virtual BOOL OnNewDocument();
public:
	virtual ~winservice_1_document();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

   BOOL OnOpenDocument(LPCTSTR lpszPathName);

};

