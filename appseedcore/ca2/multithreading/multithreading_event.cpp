#include "StdAfx.h"

CEvent::CEvent(BOOL bInitiallyOwn, BOOL bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES lpsaAttribute)
   : sync_object(pstrName)
{
   m_hObject = ::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, pstrName);
   if (m_hObject == NULL)
      AfxThrowResourceException();
}

CEvent::~CEvent()
{
}

BOOL CEvent::Unlock()
{
   return TRUE;
}
