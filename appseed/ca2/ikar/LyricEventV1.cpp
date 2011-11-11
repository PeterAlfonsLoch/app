#include "StdAfx.h"


#define EVENT_ID_LYRIC_V1 5

LyricEventV1::LyricEventV1():
m_iID(EVENT_ID_LYRIC_V1)
{
}

LyricEventV1::LyricEventV1(LyricEventV1 & src)
{
   operator=(src);
}

LyricEventV1::~LyricEventV1()
{

}

void LyricEventV1::ToData_(LPDWORD lpdwData, DWORD cbLeft)
{
   UNREFERENCED_PARAMETER(lpdwData);
   UNREFERENCED_PARAMETER(cbLeft);
   if(cbLeft <= 0)
      return;
//   if(cbLeft != sizeof(m_pbData))
   {
      TRACE("BAD EVENT");
   }
   m_iClassOrder = GetClassOrder();
//   TRACE(
//      "ToData %05d   %05d   %05d\n",
//      m_Event.m_nType,
//      m_Event.m_nTrack,
//      m_Event.m_nCurrentIndex);
//   void * pVoid = (void *) ((m_pbData + (sizeof(m_pbData))) - cbLeft) ;
//   memcpy((void *) lpdwData, pVoid, cbLeft);

}

void LyricEventV1::FromData_(LPDWORD lpdwData)
{
   UNREFERENCED_PARAMETER(lpdwData);
//   memcpy((void *) m_pbData, lpdwData, sizeof(m_pbData));
//   TRACE(
//      "LyricEventV1::FromData %05d   %05d   %05d\n",
//      m_iType,
//      m_iTrack,
//      m_iCurrentToken);

}

int LyricEventV1::GetClassOrder()
{
   return 0;
}

/*
void LyricEventV1::Serialize(CArchive &ar)
{
   if(ar.IsLoading())
   {
      ar >> m_iID; 
      ar >> m_iClassOrder;
      ar >> m_iOrder;
      ar >> m_iType;
      ar >> m_iCurrentNote;
      ar >> m_iCurrentToken;
      ar >> m_iTrack;
      ar >> (DWORD &) m_tkDelta;
   }
   else if(ar.IsStoring())
   {
      ar << m_iID; 
      ar << m_iClassOrder;
      ar << m_iOrder;
      ar << m_iType;
      ar << m_iCurrentNote;
      ar << m_iCurrentToken;
      ar << m_iTrack;
      ar << (DWORD) m_tkDelta;
   }

}

void CLASS_DECL_ca SerializeElements(CArchive& ar, LyricEventV1* pElements, int nCount)
{
   ASSERT(nCount == 0 ||
      fx_is_valid_address(pElements, nCount * sizeof(LyricEventV1)));
    
    for(int i = 0; i < nCount; i++)
    {
        pElements[i].Serialize(ar);
    }
}
*/


LyricEventV1 & LyricEventV1::operator=(const LyricEventV1 & src)
{
   m_iID               = src.m_iID;
   m_iClassOrder      = src.m_iClassOrder;
   m_iOrder            = src.m_iOrder;
   m_iType            = src.m_iType;
   m_iCurrentNote      = src.m_iCurrentNote;
   m_iCurrentToken   = src.m_iCurrentToken;
   m_iTrack          = src.m_iTrack;
   m_tkDelta         = src.m_tkDelta;

   return *this;

}