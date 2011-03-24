// _vmsriffdecDecoder.h: interface for the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSRIFFDECDECODER_H__0D17B341_424F_42CE_AE25_47F3965A7D5C__INCLUDED_)
#define AFX__VMSRIFFDECDECODER_H__0D17B341_424F_42CE_AE25_47F3965A7D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaudioiDecoderInterface.h"


namespace _vmsriffdec
{

class CDecoder
   :  
   _vmsaudioi::CDecoderInterface
{
public:
	CDecoder();
	virtual ~CDecoder();

   virtual void      DecoderInitialize(CFile * pfile) = 0;

};

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////

#endif // !defined(AFX__VMSRIFFDECDECODER_H__0D17B341_424F_42CE_AE25_47F3965A7D5C__INCLUDED_)
