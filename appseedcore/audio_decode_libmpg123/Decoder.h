#pragma once


#include "id3lib/tag.h"
#include "ID3_Reader.h"


namespace audio_decode_libmpg123
{

   class CLASS_DECL_AUDDEC_LIBMPG123_BRIDGE decoder :
      public audio_decode::decoder
   {

   protected:
      class ReadFrame
      {
      public:
         ex1::file *       m_pfileIn;
         ex1::file *       m_pfileOut;
         primitive::memory            m_memoryIn;
         primitive::memory            m_memoryOut;
         int               m_iChannels;
         int               m_iEncoding;
         long              m_lSamplesPerSecond;

         int               m_iRet;

      protected:
         bool              m_bFileInEof;
         bool              m_bDecEof;
         DWORD             m_dwPos;

         
      public:
         bool                 m_bSeekable;
         mpg123_handle *     m_phandle;
         bool m_bInit;
         ReadFrame();
         ~ReadFrame();
         bool Initialize(ex1::file * pfileIn, ex1::file * pfileOut);

         bool _ReadFrame();
         bool _seekable_read_frame();
         bool _non_seekable_read_frame();

      public:
         bool IsEof(void);
      };
   protected:
      int                  m_iSamMul;
      int                  m_iSamDiv;

      int                  m_iReadPointer;
      gen::memory_file   m_memfile;
      bool                 m_bStop;
      ID3_Tag              m_id3tag;
      ID3_Reader           m_id3reader;
      //ex1::filesp         m_fileId3;
      ReadFrame            m_readframe;
      char *               m_szId3[0x410];
      __int64              m_nSampleCount;
      
   public:
	   void GuessParameters();
	   void DecoderStop();
	   void ReadFrame();

      
      gen::memory_file & GetMemoryFile();
	   decoder(::ca::application * papp);
	   virtual ~decoder();

      

      virtual bool      _DecoderInitialize(ex1::file *pfile);
      virtual bool      _DecoderEOF();
      virtual int       _DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize);
      
      virtual void      DecoderMoveNext();
      virtual LPBYTE    DecoderGetBuffer();
      virtual int       DecoderGetBufferSize();
      virtual void      DecoderRun();
      virtual __int64   DecoderGetSampleCount();
      virtual UINT      DecoderGetSamplesPerSecond();
      virtual UINT      DecoderGetChannelCount();
      virtual UINT      DecoderGetBitsPerSample();
      virtual void      DecoderSeekBegin();
      virtual bool      DecoderGetAttribute(audio_decode::EAttribute eattribute, string & str);
      ID3_FrameID       GetAttributeId(audio_decode::EAttribute eattribute);
      virtual bool      DecoderSetSeekable(bool bSet);
      virtual bool      DecoderGetSeekable();
      virtual int       DecoderSetReadBlockSize(int iSize);
   };




} // namespace _vmsmpegdec

