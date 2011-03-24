// _vmsaudioiWaveChunkEffect.h: interface for the _vmsaudioiWaveChunkEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAUDIOIWAVECHUNKEFFECT_H__E4949F86_B28A_47F3_8207_0DB447DEC59E__INCLUDED_)
#define AFX__VMSAUDIOIWAVECHUNKEFFECT_H__E4949F86_B28A_47F3_8207_0DB447DEC59E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsaudioi
{

   class WaveChunk;

class WaveChunkEffect  
{
public:
   virtual bool WriteChunk(WaveChunk * pchunk) = 0;
   virtual bool ReadChunk(WaveChunk * pchunk) = 0;


	WaveChunkEffect();
	virtual ~WaveChunkEffect();

};

}

#endif // !defined(AFX__VMSAUDIOIWAVECHUNKEFFECT_H__E4949F86_B28A_47F3_8207_0DB447DEC59E__INCLUDED_)
