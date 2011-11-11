// _vmsaudioWaveStreamEffectOrder.h: interface for the _vmsaudioWaveStreamEffectOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAUDIOWAVESTREAMEFFECTORDER_H__D0872844_70B7_40C4_BD67_3633CD68F4D9__INCLUDED_)
#define AFX__VMSAUDIOWAVESTREAMEFFECTORDER_H__D0872844_70B7_40C4_BD67_3633CD68F4D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace _vmsaudioi
{

class CLASS_DECL_VMSAUDIOI WaveStreamEffectOrder :
   public BaseIntArray
{
public:
	int CompareSubOrder(const WaveStreamEffectOrder &  order) const;
	WaveStreamEffectOrder();
	virtual ~WaveStreamEffectOrder();

};

} // namespace _vmsaudioi

#endif // !defined(AFX__VMSAUDIOWAVESTREAMEFFECTORDER_H__D0872844_70B7_40C4_BD67_3633CD68F4D9__INCLUDED_)
