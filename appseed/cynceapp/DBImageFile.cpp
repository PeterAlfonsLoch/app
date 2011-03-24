
#include "stdafx.h"
#include "resource.h"
#include "DBImageFile.h"

#include "gen/WFileFind.h"




DBImageFileSet::DBImageFileSet()
{
	m_bOffline = false;
	m_strRegistrySection = _T("DBImageFileSet");
}

DBImageFileSet::~DBImageFileSet()
{
	m_cs.Lock();
}


// Adiciona na matriz os nomes dos diretórios de imagens.
void DBImageFileSet::GetStringArray(AStrArray & wstra)
{
/*	if(DB()->IsWorking())
	{
		HRESULT hr;
		WString wstr;
		
        CSingleLock sl(&m_cs, true);
		if(FAILED(hr = MoveFirst()))
			goto End;
		while(TRUE)
		{
			if(FAILED(GetData()))
				goto End;
			CDBComplement::DX_Text(FALSE, wstr, &m_Path, &m_sPath);
			wstra.Add(wstr);
			if(FAILED(hr = MoveNext()))
				goto End;
			if(hr == DB_S_ENDOFROWSET)
				goto End;
		}
		End:;
	}
	else
	{
		wstra.Copy(m_wstra);
	}*/
}


bool DBImageFileSet::GetNextFile(LPCTSTR lpcszCurrentFilePath, CString & wstrNextFilePath)
{
   int i = FindFirstFile(lpcszCurrentFilePath);
	
   if(i < 0)
	{
	   i = 0;
	}
	else
	{
	   i++;
	}
	
   if(i >= GetFileCount())
	   i = 0;
	
   if(i >= GetFileCount())
	   return false;
	
   FileAt(i, wstrNextFilePath);

   return true;
}

/*bool DBImageFileSet::Fill(WStrArray & wstra, WStrArray & wstraExcluded)
{
   RemoveAll();
	WString wstr;
	CSingleLock sl(&m_cs, true); 
   WStrArray wstraFilters;
   wstraFilters.Add(L"\\*.bmp");
   wstraFilters.Add(L"\\*.jpg");
   wstraFilters.Add(L"\\*.png");
	int i, j;
	CWFileFind filefind;
	WString wstrFile;
	CString str;
	for(i = 0; i < wstra.GetSize(); i++)
	{
      for(j = 0; j <wstraFilters.GetSize(); j++)
      {
	      wstr = wstra.ElementAt(i);
		   wstr += wstraFilters.ElementAt(j);
		   if(!filefind.FindFile(wstr))
			   continue;
		   TRACE(_T("Image Directory: %S\n"), wstr);
		   TRACE(_T("MAX_PATH:%d"), MAX_PATH);
		   BOOL ok;
		   ok = TRUE;
		   while(ok)
		   {
			   ok = filefind.FindNextFile();
			   wstrFile = filefind.GetFilePath();
            if(wstraExcluded.FindFirstNoCase(wstrFile) < 0)
            {
      		   m_wstra.Add(wstrFile);
            }
		   }
		   filefind.Close();
      }
   }
	return TRUE;
}*/


HRESULT DBImageFileSet::RemoveAll()
{
   RemoveAllFiles();
   return S_OK;
}

HRESULT DBImageFileSet::Add(const CString &str)
{
	ASSERT(FALSE);
	return S_OK;
}

void DBImageFileSet::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
   if(key == VMSDATAKEY(ImageDirectorySet))
   {
      Fill();
   }
}

void DBImageFileSet::Fill()
{
   TRACE(_T("vmpLight: DBImageFileSet::Fill"));

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(ImageDirectorySet), 0, 0, wstra);

   AStrArray wstraFilters;
   wstraFilters.Add("\\*.bmp");
   wstraFilters.Add("\\*.jpg");
   wstraFilters.Add("\\*.png");


   RemoveAll();

	AddSearch(wstra, wstraFilters);
}
