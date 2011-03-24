// _vmsriffdecMicrosoftPCMFormatField.h: interface for the CMicrosoftPCMFormatField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSRIFFDECMICROSOFTPCMFORMATFIELD_H__AAF9D0D8_BEE6_4B30_8FFF_BC0ABD8C14E4__INCLUDED_)
#define AFX__VMSRIFFDECMICROSOFTPCMFORMATFIELD_H__AAF9D0D8_BEE6_4B30_8FFF_BC0ABD8C14E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsriffdec
{

class CMicrosoftPCMFormatField  
{
public:
		WORD m_wBitsPerSample;	// Sample size
public:
	CMicrosoftPCMFormatField();
	virtual ~CMicrosoftPCMFormatField();

};

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////

#endif // !defined(AFX__VMSRIFFDECMICROSOFTPCMFORMATFIELD_H__AAF9D0D8_BEE6_4B30_8FFF_BC0ABD8C14E4__INCLUDED_)

