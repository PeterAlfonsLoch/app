/* (c)Copyright 1996-2000 NTT Cyber Space Laboratories */
/*                Released on 2000.09.06 by N. Iwakami */
/*                Modified on 2000.09.22 by N. Iwakami */
/*                Modified on 2000.10.03 by N. Iwakami, simplified version */

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#include "twinvq.h"
#include "tvqdec.h"
#include "bfile.h"
#include "bstream.h"
#include "HeaderManager.h"

static const int INIT_ERR_DISP_MBOX = 1;

/*--------------------------------------------------------------------------------------*/
/* Name:        TvqGetStandardChunkINfo()                                               */
/* Description: theManager ‚©‚ç•W€ƒ`ƒƒƒ“ƒN‚Ìî•ñ‚ðŽæ“¾‚µAsetupInfo ‚Ìƒƒ“ƒo‚ÉŠi”[‚·‚é */
/* Return:      (int) Žæ“¾‚É¬Œ÷‚·‚ê‚Î 0 Ž¸”s‚µ‚½‚ç 1                                   */
/* Access:      static                                                                  */
/*--------------------------------------------------------------------------------------*/
static
int TvqGetStandardChunkInfo ( CHeaderManager* theManager, headerInfo* setupInfo )
{
	memset( setupInfo, 0, sizeof(headerInfo) );

	// get TwinVQ ID
	sprintf( setupInfo->ID, "%s", theManager->GetID().c_str() );

	// get COMM chunk information
	try {
		CCommChunk commChunk( theManager->GetPrimaryChunk("COMM") );
		setupInfo->channelMode = commChunk.GetChannelMode();
		setupInfo->bitRate = commChunk.GetBitRate();
		setupInfo->samplingRate = commChunk.GetSamplingRate();
		setupInfo->securityLevel = commChunk.GetSecurityLevel();
	}
	catch (CHeaderManager::err_FailGetChunk) {
		std::cerr << "no COMM chunk" << std::endl;
		return 1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*/
/* Name:        frtobuf()                                                     */
/* Description: copy frame data to output buffer                              */
/* Return:      none                                                          */
/* Access:      static                                                        */
/*----------------------------------------------------------------------------*/
static
void frtobuf(float out[],       /* Input  --- input data frame */
			 short  bufout[],    /* Output --- output data buffer array */
			 int    frameSize,   /* Input  --- frame size */
			 int    numChannels) /* Input  --- number of channels */
{
	/*--- Variables ---*/
	int	ismp, ich, uflag, lflag;
	float *ptr;
	register float dtmp;
	
	uflag = lflag = 0;
	
	for ( ich=0; ich<numChannels; ich++ ){
		ptr = out+ich*frameSize;
		for ( ismp=0; ismp<frameSize; ismp++ ){
			dtmp = ptr[ismp];
			if ( dtmp >= 0. ){
				if ( dtmp > 32700. ){
					dtmp = 32700.;
					uflag = 1;
				}
				bufout[ismp*numChannels+ich] = (short)(dtmp+0.5);
			}
			else{
				if ( dtmp < -32700. ){
					dtmp = -32700.;
					lflag = 1;
				}
				bufout[ismp*numChannels+ich] = (short)(dtmp-0.5);
			}
		}
	}
}

/*============================================================================*/
/* Name:        main()                                                        */
/* Description: the main program                                              */
/* Return:      (int) returns 1 when errors or 0                              */
/* Access:      external                                                      */
/*============================================================================*/
int main(int argc, char *argv[])
{

	if (argc < 3) {
		fprintf( stderr, "Usage: %s <input bitstream file> <output PCM file>.\n", argv[0] );
		return 1;
	}

	/*-----------------------------------------------------------------*/
	/* OPEN INPUT BITSTREAM FILE AND OUTPUT AUDIO DATA FILE            */
	/*-----------------------------------------------------------------*/
	BFILE	*bfp=NULL;
	FILE	*fp=NULL;
//	if ( (bfp = bopen( argv[1],"rb")) == NULL ) {
//		fprintf( stderr, "%s: Input bitstream file open error.\n", argv[1] );
//		return 1;
//	}
	if ( (fp = fopen(argv[2], "wb")) == NULL ) {
		fprintf( stderr, "%s: Output audio file open error.\n", argv[1] );
		return 1;
	}

	/*-----------------------------------------------------------------*/
	/* INITIALIZE TwinVQ decoder                                       */
	/*-----------------------------------------------------------------*/
	/* get bitstream header */
	CChunkChunk* twinChunk = TvqGetBsHeaderInfo(bfp);
	if ( twinChunk == NULL ) {
		fprintf( stderr, "Program is stopped due to an error in parsing header.\n" );
		return 1;
	}
	/* parse bitstream header */
	CHeaderManager *theHeaderManager = CHeaderManager::Create( *twinChunk );
	if ( theHeaderManager == NULL) {
		fprintf( stderr, "Failed to read header. Check the bitstream file.\n" );
		return 1;
	}
	headerInfo setupInfo; 
	TvqGetStandardChunkInfo( theHeaderManager, &setupInfo );
	/* initialize TwinVQ */
	INDEX index;
	int errorCode = TvqInitialize( &setupInfo, &index, INIT_ERR_DISP_MBOX );
	if ( errorCode ) {
		return 1;
	}
	/* initialize bitstream reader */
	if ( TvqInitBsReader( &setupInfo ) ) {
		fprintf( stderr, "Program is stopped due to an error in bitstream reader initialization.\n" );
		return 1;
	}
	/* initialize data buffers */
	int        frameSize, numChannels;  // frame configuration parameters
	float      *frame;                  // decoder output data array
	short      *buf;                    // file output buffer
	frameSize = TvqGetFrameSize();
	numChannels = TvqGetNumChannels();
	frame = new float[frameSize * numChannels];
	buf   = new short[frameSize * numChannels];

	/*-----------------------------------------------------------------*/
	/* DECODING PROCESS                                                */
	/*-----------------------------------------------------------------*/
	int wout_flag = 2;
	while ( TvqReadBsFrame(&index, bfp) != 0 ){ // read 1-frame bitstream data
		TvqDecodeFrame(&index, frame);
		frtobuf(frame, buf, frameSize, numChannels);

		if ( wout_flag == 0 ){  // two frames are canceled after starting the decoding
			fwrite(buf, sizeof(short), frameSize*numChannels, fp);
		}
		wout_flag = wout_flag - 1 > 0 ? wout_flag - 1 : 0;
	}

	/*-----------------------------------------------------------------*/
	/* TERMINATE THE DECODER                                           */
	/*-----------------------------------------------------------------*/
	TvqTerminate(&index);
	bclose(bfp);
	fclose(fp);
	delete[] frame;
	delete[] buf;

	return 0;
}

