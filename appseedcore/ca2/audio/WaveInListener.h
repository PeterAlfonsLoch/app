// audWaveInListener.h: interface for the audWaveInListener class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEINLISTENER_H__F24A0B26_F854_4B8F_8CA5_5B02660024BF__INCLUDED_)
#define AFX_WAVEINLISTENER_H__F24A0B26_F854_4B8F_8CA5_5B02660024BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class audWaveIn;


class CLASS_DECL_ca audWaveInListener  
{
   friend class audWaveIn;
public:
   
   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
   audWaveInListener();
   virtual ~audWaveInListener();

protected:
   void HookWaveIn(audWaveIn * pwavein);
   void UnhookWaveIn(audWaveIn * pwavein);
   comparable_array < audWaveIn *, audWaveIn * > m_waveinptra;
};

#endif // !defined(AFX_WAVEINLISTENER_H__F24A0B26_F854_4B8F_8CA5_5B02660024BF__INCLUDED_)
