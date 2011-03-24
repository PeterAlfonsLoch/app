// VmpLightDB1.h: interface for the VmpLightDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMPLIGHTDB1_H__143C8D76_F1B6_4CE2_9FF9_669EA7A31EBD__INCLUDED_)
#define AFX_VMPLIGHTDB1_H__143C8D76_F1B6_4CE2_9FF9_669EA7A31EBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DBImageFileSet;
class DBImageDirectorySet;

class VmpLightDB
{
public:
	VmpLightDB();
	virtual ~VmpLightDB();

protected:
   bool                    m_bInitialized;
   DBImageFileSet *        m_pimagefileset;
   DBImageDirectorySet *   m_pimagedirectoryset;

public:
	static VmpLightDB * GetLightDB();
	void Finalize();
	bool Initialize();
   DBImageFileSet * GetImageFileSet();
   DBImageDirectorySet *  GetImageDirectorySet();
   CString GetNextImagePath(CString &wstrCurrent);
   void UpdateImagePaths();

   void OnImageDirectorySetChange();

};

inline DBImageFileSet * VmpLightDB::GetImageFileSet()
{
   return m_pimagefileset;
}
inline DBImageDirectorySet *  VmpLightDB::GetImageDirectorySet()
{
   return m_pimagedirectoryset;
}

#endif // !defined(AFX_VMPLIGHTDB1_H__143C8D76_F1B6_4CE2_9FF9_669EA7A31EBD__INCLUDED_)
