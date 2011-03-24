// _vmsaiffdecID.cpp: implementation of the CID class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecID.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define AIFF_FORM 0x4D524F46
#define AIFF_AIFF 0x46464941
#define AIFF_COMM 0x4D4D4F43
#define AIFF_SSND 0x444E5353

extern void SwapBytesInWords( short *loc, int words );


namespace _vmsaiffdec
{


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CID::CID()
{

}

CID::~CID()
{

}

bool CID::IsFORM()
{
   return  m_uiId == AIFF_FORM;
}

bool CID::IsAIFF()
{
   return  m_uiId == AIFF_AIFF;
}

bool CID::IsCOMM()
{
   return m_uiId == AIFF_COMM;
}

bool CID::IsSSND()
{
   return m_uiId == AIFF_SSND;
}

bool CID::Initialize()
{
   //SwapBytesInWords((short *) m_szId, 2);
   return true;
}


/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////




