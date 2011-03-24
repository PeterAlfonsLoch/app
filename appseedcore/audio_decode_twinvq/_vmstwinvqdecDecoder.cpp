// _vmstwinvqdecDecoder.cpp: implementation of the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmstwinvqdecDecoder.h"
#include "bstream.h"
#include "tvqdec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern 
int InitializeDecoder(headerInfo *setupInfo,  // Output: setup parameters
					  int *frameSize,         // Output: frame size
					  int *numChannels,       // Output: number of channels
					  INDEX *index,           // Output: code information interface
					  float **out,            // Output: decoder output data array
					  short **bufout,         // Output: data buffer used for file output
					  BFILE *bfp_cw,          // Input:  the bitstream file pointer
					  int   fileType,
					  FILE  *fp_o,
					  char  *namein,          // Input:  input file name (used only for displaying)
					  char  *nameout);        // Input:  output file name (used only for displaying)

extern 
void frtobuf(float out[],       /* Input  --- input data frame */
			 short  bufout[],    /* Output --- output data buffer array */
			 int    frameSize,   /* Input  --- frame size */
			 int    numChannels); /* Input  --- number of channels */

namespace _vmstwinvqdec
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDecoder::CDecoder()
{

}

CDecoder::~CDecoder()
{

}

bool      CDecoder::DecoderInitialize(CFile * pfile)
{
   m_bStop = false;
   m_iReadPointer = 0;
   fileType = 0;
	wout_flag = 2;             // Decoder wave output flag
	flgRewind = 0;
   flgFF = 0;  // FF and REW status
	play_count = 0;            // skip control parameters when FF and REW mode
   m_bEOF = false;
   //-----------------------------------------------------------------
	// OPEN INPUT BITSTREAM FILE
	//-----------------------------------------------------------------
  	// open input bitstream file
	if ( (bfp_cw=bopen(pfile,"rb")) == NULL )
   {
		TRACE("%s: File not found.\n", pfile->GetFilePath());
		return 1;
	}

	/*-----------------------------------------------------------------*/
	/* INITIALIZE TwinVQ decoder                                       */
	/*-----------------------------------------------------------------*/
	if ( InitializeDecoder(
      &setupInfo,
      &frameSize,
      &numChannels,
      &index, 
      &out,
      &bufout,
      bfp_cw, fileType, NULL, (char *) (const char *) pfile->GetFilePath(), NULL ))
   {
		return 1;
	}

   return true;
}
void CDecoder::DecoderMoveNext()
{
   
}
bool      CDecoder::DecoderEOF()
{
   return m_bEOF;
}
LPBYTE    CDecoder::DecoderGetBuffer()
{
   return NULL;
}
int       CDecoder::DecoderGetBufferSize()
{
   return -1;
}
void CDecoder::DecoderRun()
{
}
UINT CDecoder::DecoderGetSamplesPerSec()
{
   return NULL;
}
UINT CDecoder::DecoderGetChannelCount()
{
   return NULL;
}
UINT CDecoder::DecoderGetBitsPerSample()
{
   return NULL;
}

int CDecoder::DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
{
   if(m_bEOF)
      return 0;

   LPBYTE lpbBuffer = (LPBYTE) lpvoidBuffer; 
   UINT uiRemain = uiBufferSize;
   UINT uiPointer = 0;
   UINT uiSize;
   while(uiRemain > 0)
   {
      if(m_bStop || m_bEOF)
         return uiPointer;

      if(m_iReadPointer >= GetMemoryFile().GetStorageSize_())
      {
         ReadFrame();
         m_iReadPointer = 0;
      }
      uiSize = GetMemoryFile().RemoveBegin(&lpbBuffer[uiPointer], uiRemain);
      uiPointer += uiSize;
      m_iReadPointer += uiSize;
      uiRemain -= uiSize;
   }
/*	 if ( NativeByteOrder == order_littleEndian )
    {
	   SwapBytesInWords( (short *) lpbBuffer, uiBufferSize / 2 );
	 }*/
   return uiPointer;
}

void CDecoder::ReadFrame()
{
   if(m_bEOF)
      return;

	if(TvqReadBsFrame(&index, bfp_cw) == 0)
   {
      m_bEOF = true;
      return;
   }

   /* decode frame */
	TvqDecodeFrame(&index, out);

	/* transform decoder output data to audio PCM data */
	frtobuf(out, bufout, frameSize, numChannels);

	// write PCM data to the output audio data file
   if ( wout_flag == 0 )  // two frames are canceled after starting the decoding
   {
	   GetMemoryFile().Write(bufout, sizeof(*bufout) * frameSize*numChannels);
   }
	wout_flag = wout_flag - 1 > 0 ? wout_flag - 1 : 0;

		/* display decoding progress */
#if DISPLAY_PROGRESS
		mark(TvqGetBsFramePoint() -1, flgFF, flgRewind); // mark decoding progression
#endif
		
		/*** FF control ***/
/*		if (FF_DEMO == 1){
			if (TvqGetBsFramePoint() > 150 && flgFF != -1) flgFF = 1; // set FF start point
			if (flgFF == 1){
				if (++play_count == 5){ // frame is skipped by every 5-frame decoding
					play_count = 0;          // reset the decoding counter
					wout_flag = 2;           // reset the wave output flag
					TvqSkipFrame(bfp_cw, 1); // skip one frames (then (1+2)=3 frames are skipped playing
				}
				if (TvqGetBsFramePoint() > 400){  // set FF stop point
					flgFF = -1;
				}
			}
		}
		/*** REW control ***/
/*		else if (REW_DEMO == 1){
			if (TvqGetBsFramePoint() > 450 && flgRewind != -1) flgRewind = 1; // set REW start point
			if (flgRewind == 1){
				if (++play_count == 5){ // frame is skipped by every 5-frame decoding
					play_count = 0;     // reset the decoding counter
					wout_flag = 2;      // reset the wave output flag
					TvqSkipFrame(bfp_cw, -11);  // skip backward 11 frames
				}
				if (TvqGetBsFramePoint() < 200){ // set REW stop point
					flgRewind = -1;
				}
			}
		}*/
}

void CDecoder::DecoderStop()
{
   m_bStop = true;
}
void CDecoder::DecoderSeekBegin()
{
   m_bStop = false;
   m_bEOF = false;
   TvqSeekBegin(bfp_cw);
   GetMemoryFile().Allocate(0);
   GetMemoryFile().SeekToBegin();
   m_iReadPointer = 0;


}

} // namespace _vmstwinvqdec

