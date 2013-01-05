// _vmskissfftKiss.h: interface for the _vmskissfftKiss class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSKISSFFTKISS_H__868AC56F_4C61_4C94_B4B0_C8C7919AB9C4__INCLUDED_)
#define AFX__VMSKISSFFTKISS_H__868AC56F_4C61_4C94_B4B0_C8C7919AB9C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kiss_fftr.h"

namespace _vmskissfftsh
{

class CLASS_DECL_VMSKISSFFTSH Ffftrd
{
public:
	Ffftrd(int32_t iSize);
	virtual ~Ffftrd();

   void Fft(int16_t * pshIn, int16_t * pshOut);

protected:
   int32_t               m_iSize;
   kiss_fftr_cfg     m_cfg;
   kiss_fft_cpx *    m_freqdata;

};

} // namespace _vmskissfft

#endif // !defined(AFX__VMSKISSFFTKISS_H__868AC56F_4C61_4C94_B4B0_C8C7919AB9C4__INCLUDED_)
