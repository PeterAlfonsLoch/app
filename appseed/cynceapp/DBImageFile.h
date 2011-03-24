
#ifndef _ImageFile_____
#define _ImageFile_____

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "idb/DBExcept.h"



class DBImageFileSet :
   public Ex1FileSet,
	public VmsDataClientInterface
{

public:
	DBImageFileSet();
	~DBImageFileSet();

public:
	bool			   m_bOffline;
	//WStrArray		m_wstra;
   WStrArray		m_wstraExcluded;
	CString			m_strRegistrySection;


public:
	void Fill();
	HRESULT Add(const CString &wstr);
	HRESULT RemoveAll();

	CCriticalSection		m_cs;
	void GetStringArray(AStrArray & wstra);
	
	bool GetNextFile(LPCTSTR lpcszCurrentFilePath, CString & wstrNextFilePath);

	//bool Fill(WStrArray &wstra, WStrArray &wstraExcluded);

   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

};

#endif