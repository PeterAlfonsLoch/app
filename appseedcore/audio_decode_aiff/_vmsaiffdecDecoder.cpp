// _vmsaiffdecDecoder.cpp: implementation of the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecDecoder.h"
#include "_vmsaiffdecFormChunk.h"
#include "_vmsaiffdecCommonChunk.h"
#include "_vmsaiffdecSoundDataChunk.h"
#include "MemoryFile.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

enum byte_order { order_unknown, order_bigEndian, order_littleEndian };

enum byte_order NativeByteOrder = order_unknown;

enum byte_order DetermineByteOrder()
{
    char s[ sizeof(long) + 1 ];
    union
    {
        long longval;
        char charval[ sizeof(long) ];
    } probe;
    probe.longval = 0x41424344L;  /* ABCD in ASCII */
    strncpy( s, probe.charval, sizeof(long) );
    s[ sizeof(long) ] = '\0';
    /* fprintf( stderr, "byte order is %s\n", s ); */
    if ( strcmp(s, "ABCD") == 0 )
        return order_bigEndian;
    else
        if ( strcmp(s, "DCBA") == 0 )
            return order_littleEndian;
        else
            return order_unknown;
}

void SwapBytesInWords( short *loc, int words )
{
    int i;
    short thisval;
    char *dst, *src;
    src = (char *) &thisval;
    for ( i = 0; i < words; i++ )
    {
        thisval = *loc;
        dst = (char *) loc++;
        dst[0] = src[1];
        dst[1] = src[0];
    }
}


namespace _vmsaiffdec
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDecoder::CDecoder()
{
   if(NativeByteOrder == order_unknown)
   {
      NativeByteOrder = DetermineByteOrder();
   }
   m_pformchunkhdr = NULL;
   m_pcommonchunk = NULL;
   m_psounddatachunk = NULL;
   m_uiFrameSize = 3200;
   m_lpbFrame = new BYTE[m_uiFrameSize];
}

#define _DELETE___(ptr)       \
         if(ptr != NULL)      \
         {                    \
            delete ptr;       \
            ptr = NULL;       \
         }

CDecoder::~CDecoder()
{
   _DELETE___(m_pformchunkhdr);
   _DELETE___(m_pcommonchunk);
   _DELETE___(m_psounddatachunk);
   _DELETE___(m_lpbFrame);

}

bool CDecoder::DecoderInitialize(CFile * pfile)
{
   m_uiReadSync = 0;
   m_bEOD = true;
   m_pfile = pfile;
   m_bStop = false;

   if(m_pformchunkhdr == NULL)
      m_pformchunkhdr = new CFormChunkHeader;

   pfile->SeekToBegin();
   if(sizeof(CFormChunkHeader) !=
      pfile->Read(m_pformchunkhdr, sizeof(CFormChunkHeader)))
   {
      return false;
   }

   m_pformchunkhdr->Initialize();

   if(!m_pformchunkhdr->m_chunkheader.m_id.IsFORM())
   {
      return false;
   }

   if(!m_pformchunkhdr->m_idType.IsAIFF())
   {
      return false;
   }

   CChunkHeader chunkhdr;
   if(sizeof(CChunkHeader) !=
      pfile->Read(&chunkhdr, sizeof(CChunkHeader)))
   {
      return false;
   }

   chunkhdr.Initialize();

   if(!chunkhdr.m_id.IsCOMM()
      || chunkhdr.GetSize() != 18)
   {
      return false;
   }

   if(m_pcommonchunk == NULL)
      m_pcommonchunk = new CCommonChunk;

   
   pfile->Seek(-(int)sizeof(CChunkHeader), CFile::current);
   if(sizeof(CCommonChunk) !=
      pfile->Read(m_pcommonchunk, sizeof(CCommonChunk)))
   {
      return false;
   }

   m_pcommonchunk->Initialize();

   if(!m_pcommonchunk->m_chunkheader.m_id.IsCOMM()
      || m_pcommonchunk->m_chunkheader.GetSize() != 18)
   {
      return false;
   }

   if(m_psounddatachunk == NULL)
      m_psounddatachunk = new CSoundDataChunk;

   if(sizeof(CSoundDataChunk) !=
      pfile->Read(m_psounddatachunk, sizeof(CSoundDataChunk)))
   {
      return false;
   }

   m_psounddatachunk->Initialize();

   m_bEOD = false;


}
void CDecoder::DecoderMoveNext()
{
}
bool CDecoder::DecoderEOF()
{
   return m_bEOD;
}
LPBYTE CDecoder::DecoderGetBuffer()
{
   return NULL;
}

int CDecoder::DecoderGetBufferSize()
{
   return 0;
}
void CDecoder::DecoderRun()
{
}

UINT CDecoder::DecoderGetSamplesPerSec()
{
   return (UINT) m_pcommonchunk->m_extSampleRate.GetValue();
}
UINT CDecoder::DecoderGetChannelCount()
{
   return m_pcommonchunk->m_shChannelCount;
}
UINT CDecoder::DecoderGetBitsPerSample()
{
   return m_pcommonchunk->m_shSampleSize;
}

int CDecoder::DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
{
   LPBYTE lpbBuffer = (LPBYTE) lpvoidBuffer;
   UINT uiRemain = uiBufferSize;
   UINT uiPointer = 0;
   UINT uiSize;
   while(uiRemain > 0)
   {
      if(m_bStop)
         return uiPointer;
      if(m_fileFrame.GetStorageSize_() <= 0)
      {
         ReadFrame();
      }
      if(m_fileFrame.GetStorageSize_() <= 0)
      {
         m_bEOD = true;
         return uiPointer;
      }
      uiSize = m_fileFrame.RemoveBegin(&lpbBuffer[uiPointer], uiRemain);
      uiRemain -= uiSize;
      uiPointer += uiSize;
   }
   return uiPointer;
}

void CDecoder::DecoderStop()
{
   m_bStop = true;
}

void CDecoder::DecoderSeekBegin()
{
   m_bStop = false;
}

void CDecoder::ReadFrame()
{
   UINT uiSize = m_pfile->Read(&m_lpbFrame[m_uiReadSync], m_uiFrameSize - m_uiReadSync);

   if(NativeByteOrder == order_littleEndian)
   {
      SwapBytesInWords((short *) m_lpbFrame, uiSize / 2);
   }

   m_uiReadSync = uiSize % 2;
   m_fileFrame.Write(m_lpbFrame, uiSize - m_uiReadSync);
   if(m_uiReadSync > 0)
   {
      memcpy(m_lpbFrame, &m_lpbFrame[uiSize - m_uiReadSync + 1], m_uiReadSync);
   }
   
}


/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

