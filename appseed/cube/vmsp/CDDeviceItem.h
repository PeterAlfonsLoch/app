// CDDeviceItem.h: interface for the CCDDeviceItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDDEVICEITEM_H__E78E4BDE_F9F9_4A74_B45F_1DE463DED4EC__INCLUDED_)
#define AFX_CDDEVICEITEM_H__E78E4BDE_F9F9_4A74_B45F_1DE463DED4EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "akrip/akrip32.h"

class CCDDeviceItem  
{
public:
   CCDDeviceItem();
   virtual ~CCDDeviceItem();
   GETCDHAND   m_cdhandle;

};

class CCDDeviceItemArray : public base_array < CCDDeviceItem, CCDDeviceItem >
{
};

#endif // !defined(AFX_CDDEVICEITEM_H__E78E4BDE_F9F9_4A74_B45F_1DE463DED4EC__INCLUDED_)
