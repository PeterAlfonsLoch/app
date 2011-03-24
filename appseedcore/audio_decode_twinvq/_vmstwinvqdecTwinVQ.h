// _vmstwinvqdecTwinVQ.h: interface for the CTwinVQ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSTWINVQDECTWINVQ_H__5485608B_E537_4036_9F38_0AAA948BC9C3__INCLUDED_)
#define AFX__VMSTWINVQDECTWINVQ_H__5485608B_E537_4036_9F38_0AAA948BC9C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Chunk.h"
#include "bfile.h"
#include "twinvq.h"


namespace _vmstwinvqdec
{

class  CTwinVQ  
{
public:
	CTwinVQ();
	virtual ~CTwinVQ();
/*----------------------------------------------------------------------------*/
/* bits table for VQ                                                          */
/*----------------------------------------------------------------------------*/
int *bits_0[N_INTR_TYPE], *bits_1[N_INTR_TYPE];

/*----------------------------------------------------------------------------*/
/* lookup parameters                                                          */
/*----------------------------------------------------------------------------*/
tvqConfInfo cf;
int iframe;
int TVQ_VERSION;

// Input:  bitstream file pointer
CChunkChunk* TvqGetBsHeaderInfo(BFILE *bfp);
int TvqInitBsReader( headerInfo *setupInfo );
int GetVqInfo( tvqConfInfoSubBlock *cfg,
			  int bits0[],
			  int bits1[],
			  int variableBits,
			  INDEX *index,
			  BFILE *bfp);
int GetBseInfo( tvqConfInfo *cf, tvqConfInfoSubBlock *cfg, INDEX *index, BFILE *bfp );
int GetGainInfo( tvqConfInfo *cf, tvqConfInfoSubBlock *cfg, INDEX *index, BFILE *bfp );
int GetLspInfo( tvqConfInfo *cf, INDEX *index, BFILE *bfp );
int GetPpcInfo( tvqConfInfo *cf, INDEX *index, BFILE *bfp );
int GetEbcInfo( tvqConfInfo *cf, tvqConfInfoSubBlock *cfg, INDEX *index, BFILE *bfp );
int TvqReadBsFrame(INDEX *index, /* Output: quantization indexes */
				   BFILE *bfp);	 /* Input:  bitstream file pointer */

int TvqSkipFrame(BFILE *bfp, long step);
int TvqGetBsFramePoint();
CChunkChunk* LoadTwinChunk( BFILE *bfp );

};

} // namespace _vmstwinvqdec

#endif // !defined(AFX__VMSTWINVQDECTWINVQ_H__5485608B_E537_4036_9F38_0AAA948BC9C3__INCLUDED_)
