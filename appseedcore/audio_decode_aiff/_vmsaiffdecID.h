// _vmsaiffdecID.h: interface for the CID class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECID_H__F9B16338_7879_4D66_9403_D4D5BDE39C7B__INCLUDED_)
#define AFX__VMSAIFFDECID_H__F9B16338_7879_4D66_9403_D4D5BDE39C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsaiffdec
{

class CID  
{
public:
   union
   {
      char           m_szId[4];
      unsigned int   m_uiId;
   };
public:
	bool Initialize();
	bool IsSSND();
	bool IsCOMM();
	bool IsAIFF();
	bool IsFORM();
	CID();
	~CID();

};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECID_H__F9B16338_7879_4D66_9403_D4D5BDE39C7B__INCLUDED_)
