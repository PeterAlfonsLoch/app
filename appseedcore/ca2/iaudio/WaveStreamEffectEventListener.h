// _vmsaudioiWaveStreamEffectEventListener.h: interface for the WaveStreamEffectEventListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAUDIOIWAVESTREAMEFFECTEVENTLISTENER_H__2E373465_AD23_432F_8586_7FA38942B443__INCLUDED_)
#define AFX__VMSAUDIOIWAVESTREAMEFFECTEVENTLISTENER_H__2E373465_AD23_432F_8586_7FA38942B443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace iaudio
{

   class WaveStreamEffect;

class WaveStreamEffectEventListener
{
public:
   void OnWaveStreamEffectEvent(WaveStreamEffect * peffect, int iEvent);
   WaveStreamEffectEventListener();
   virtual ~WaveStreamEffectEventListener();

};

} // namespace iaudio

#endif // !defined(AFX__VMSAUDIOIWAVESTREAMEFFECTEVENTLISTENER_H__2E373465_AD23_432F_8586_7FA38942B443__INCLUDED_)
