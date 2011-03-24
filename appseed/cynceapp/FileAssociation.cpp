// FileAssociation.cpp: implementation of the FileAssociation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileAssociation.h"
#include "_vmspConfiguration.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


namespace vmplite
{

LPCTSTR FileAssociation::m_lpcszMidExtension = ".mid";
LPCTSTR FileAssociation::m_lpcszKarExtension = ".kar";
LPCTSTR FileAssociation::m_lpcszSt3Extension = ".st3";
LPCTSTR FileAssociation::m_lpcszMidClassId = "VeriwellMusicalStudio.Mid.Document";
LPCTSTR FileAssociation::m_lpcszKarClassId = "VeriwellMusicalStudio.Kar.Document";
LPCTSTR FileAssociation::m_lpcszSt3ClassId = "VeriwellMusicalStudio.St3.Document";
LPCTSTR FileAssociation::m_lpcszMidOldClassId = "VeriwellMusicalStudio.Mid.Document.Old";
LPCTSTR FileAssociation::m_lpcszKarOldClassId = "VeriwellMusicalStudio.Kar.Document.Old";
LPCTSTR FileAssociation::m_lpcszSt3OldClassId = "VeriwellMusicalStudio.St3.Document.Old";
LPCTSTR FileAssociation::m_lpcszMidEnsureRegistration = "ensure .mid registration";
LPCTSTR FileAssociation::m_lpcszKarEnsureRegistration = "ensure .kar registration";
LPCTSTR FileAssociation::m_lpcszSt3EnsureRegistration = "ensure .st3 registration";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FileAssociation::FileAssociation()
{

}

FileAssociation::~FileAssociation()
{

}

bool FileAssociation::Initialize()
{
	
	if(!((gen::FileAssociation *) this)->FileAssociation::Initialize())
	{
		return false;
	}

//	DISetSection("FileAssociation");

	return true;
}

void FileAssociation::CheckAssociations()
{
	if(!Initialize())
	{
		AfxMessageBox("Could not access the registry!.");
		return;
	}

	Key keyMid(GetHKEYClassesRoot(), m_lpcszMidExtension);

	CString str;
	keyMid.QueryValue("", str);

	int i;
	if(str != m_lpcszMidClassId)
	{
      if(VmsDataGet(VMSDATAKEY(ForceMidRegistration), 0, 0, i))
		{
			VmsDataSet(VMSDATAKEY(MidOldRegistration), 0, 0, str);
			if(i != 0)
			{
				keyMid.SetValue("", m_lpcszMidClassId);
			}
		}
	}

	Key keyKar(GetHKEYClassesRoot(), m_lpcszKarExtension);

	keyKar.QueryValue("", str);

	if(str != m_lpcszKarClassId)
	{
		if(VmsDataGet(VMSDATAKEY(ForceKarRegistration), 0, 0, i))
		{
			VmsDataSet(VMSDATAKEY(KarOldRegistration), 0, 0, str);
			if(i != 0)
			{
				keyKar.SetValue("", m_lpcszKarClassId);
			}
		}
	}


	Key keySt3(GetHKEYClassesRoot(), m_lpcszSt3Extension);

	keySt3.QueryValue("", str);

	if(str != m_lpcszSt3ClassId)
	{
		if(VmsDataGet(VMSDATAKEY(ForceSt3Registration), 0, 0, i))
		{
			VmsDataSet(VMSDATAKEY(St3OldRegistration), 0, 0, str);
			if(i != 0)
			{
				keySt3.SetValue("", m_lpcszSt3ClassId);
			}
		}
	}




}

void FileAssociation::UpdateServerRegistration(LPCTSTR lpcszDocString)
{


}


} // namespace _vmsp
