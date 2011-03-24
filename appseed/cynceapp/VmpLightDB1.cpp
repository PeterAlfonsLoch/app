// VmpLightDB1.cpp: implementation of the VmpLightDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VmpLightDB1.h"

#include "DBImageDirectory.h"
#include "DBImageFile.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VmpLightDB::VmpLightDB()
{
   m_bInitialized = false;
}

VmpLightDB::~VmpLightDB()
{
   Finalize();
}

void VmpLightDB::OnImageDirectorySetChange()
{
   TRACE(_T("VmpLightDB::OnImageDirectorySetChange"));

	m_pimagefileset->Fill();

   TRACE(_T("CDBCentral::OnImagesDirsModified Middle 2"));
	// As soon as the image files list build is finished,
	//    update view background image to show results!!!
   // AfxGetApp()->PostThreadMessage(WM_USER, CDBImageDirectorySet::UserMessageOnImageDirectoryChange, 0);
   //    m_listenerset.OnEvent(_vmsdb::DBEventImageDirectorySetChange);

}

bool VmpLightDB::Initialize()
{
   ASSERT(!m_bInitialized);
   if(m_bInitialized)
      return false;
   m_bInitialized = true;
   m_pimagefileset = new DBImageFileSet();
   m_pimagedirectoryset = new DBImageDirectorySet();

   m_pimagefileset->Fill();

   return true;
}

void VmpLightDB::Finalize()
{
   ASSERT(m_bInitialized);
   if(!m_bInitialized)
      return;
   m_bInitialized = false;
   if(m_pimagefileset != NULL)
      delete m_pimagefileset;
   m_pimagefileset = NULL;
   if(m_pimagedirectoryset != NULL)
      delete m_pimagedirectoryset;
   m_pimagedirectoryset = NULL;
}

CString VmpLightDB::GetNextImagePath(CString &wstrCurrent)
{
   TRACE(_T("CDBCentral::GetNextImagePath current thread %X\n"), GetCurrentThreadId());
	DBImageFileSet *pfileset = GetImageFileSet();
	CString wstr;
	VMSRESULT vmsr;
//	if(pfileset->m_spCommand == NULL)
//	{
//		OpenImagesFilesSet();
//	}
   if(VMS_SUCCEEDED(vmsr = pfileset->GetNextFile(wstrCurrent, wstr)))
   {
   }
   else
	{
      if(VMS_SUCCEEDED(vmsr = pfileset->GetNextFile(NULL, wstr)))
      {
      }
      else
      {
		   UpdateImagePaths();
			if(VMS_SUCCEEDED(pfileset->GetNextFile(wstrCurrent, wstr)))
			{
				TRACE(_T("CDBCentral::GetNextSongPath Fim 4\n"), GetCurrentThreadId());
			}
      }
	}
   return wstr;
}

void VmpLightDB::UpdateImagePaths()
{
/*	DBImageDirectorySet * pdirset = GetImageDirectorySet();
	DBImageFileSet * pfileset = GetImageFileSet();
	CWStrArray wstrArray;
	pdirset->GetData(wstrArray);
	CWStrArray wstrArrayExcluded;*/
	//pfileset->Fill(wstrArray, wstrArrayExcluded);
	DBImageFileSet * pfileset = GetImageFileSet();
   pfileset->Fill();
}

VmpLightDB * VmpLightDB::GetLightDB()
{
   return ((MusicalPlayerLightApp *) AfxGetApp())->GetLightDB();
}
