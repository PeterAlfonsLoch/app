
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
	String			m_strRegistrySection;


public:
	void Fill();
	HRESULT Add(const String &wstr);
	HRESULT RemoveAll();

	CCriticalSection		m_cs;
	void GetStringArray(AStrArray & wstra);
	
	bool GetNextFile(LPCTSTR lpcszCurrentFilePath, String & wstrNextFilePath);

	//bool Fill(WStrArray &wstra, WStrArray &wstraExcluded);

   virtual void VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh);

};

#endif