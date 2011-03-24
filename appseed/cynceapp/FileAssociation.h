// FileAssociation.h: interface for the FileAssociation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEASSOCIATION_H__236B324C_2E6D_4DC6_8DD8_BE1B22E852D8__INCLUDED_)
#define AFX_FILEASSOCIATION_H__236B324C_2E6D_4DC6_8DD8_BE1B22E852D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gen/FileAssociation.h"
#include "simpledb/DBVmsDataClientInterface.h"


namespace vmplite
{
class FileAssociation : 
	public gen::FileAssociation,
	public CDBVmsDataClientInterface
{
public:

	static LPCTSTR m_lpcszMidExtension;
	static LPCTSTR m_lpcszKarExtension;
	static LPCTSTR m_lpcszSt3Extension;
	static LPCTSTR m_lpcszMidClassId;
	static LPCTSTR m_lpcszKarClassId;
	static LPCTSTR m_lpcszSt3ClassId;
	static LPCTSTR m_lpcszMidOldClassId;
	static LPCTSTR m_lpcszKarOldClassId;
	static LPCTSTR m_lpcszSt3OldClassId;
	static LPCTSTR m_lpcszMidEnsureRegistration;
	static LPCTSTR m_lpcszKarEnsureRegistration;
	static LPCTSTR m_lpcszSt3EnsureRegistration;
	
	FileAssociation();
	virtual ~FileAssociation();


public:
	void UpdateServerRegistration(LPCTSTR lpcszDocString);
	void CheckAssociations();
	virtual bool Initialize();

};

} // namespace _vmsp

#endif // !defined(AFX_FILEASSOCIATION_H__236B324C_2E6D_4DC6_8DD8_BE1B22E852D8__INCLUDED_)
