#include "StdAfx.h"


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


namespace audio_decode_window_media
{

   decoder::decoder(::ca::application * papp) :
      ca(papp),
      thread(papp),
      ::audio_decode::decoder(papp),
      m_fileFrame(papp)
   {
      if(NativeByteOrder == order_unknown)
      {
         NativeByteOrder = DetermineByteOrder();
      }
      m_bEOF         = false;
      m_dwBufferFrameCount = 26;

      m_pwmstream    = NULL;
      m_psyncreader  = NULL;
      
   }

   #define _DELETE___(ptr)       \
            if(ptr != NULL)      \
            {                    \
               delete ptr;       \
               ptr = NULL;       \
            }

   decoder::~decoder()
   {

   }

   typedef DWORD FOURCC;




   void MSB2DWORD( DWORD *d, BYTE *b )
   {
     DWORD retVal;

     retVal = (DWORD)b[0];
     retVal = (retVal<<8) + (DWORD)b[1];
     retVal = (retVal<<8) + (DWORD)b[2];
     retVal = (retVal<<8) + (DWORD)b[3];

     *d = retVal;
   }

   HRESULT ShowAllAttributes(IWMHeaderInfo3* pHeaderInfo)
   {
       HRESULT hr          = S_OK;
       
       WORD    cAttributes = 0;
       WCHAR*  pwszName    = NULL;
       WORD    cchName     = 0;
       BYTE*   pbValue     = NULL;
       DWORD   cbValue     = 0;
       WORD    langIndex   = 0;
       WORD    attIndex    = 0;

       WMT_ATTR_DATATYPE attType;

       // get the total number of attributes in the spfile->

       hr = pHeaderInfo->GetAttributeCountEx(0xFFFF, &cAttributes);
       if(FAILED(hr))
          goto Exit;

       // Loop through all the attributes, retrieving and displaying each.

       for(attIndex = 0; attIndex < cAttributes; attIndex++)
       {
           // get the required buffer lengths for the name and value.

           hr = pHeaderInfo->GetAttributeByIndexEx(0xFFFF,
                                                   attIndex,
                                                   NULL,
                                                   &cchName,
                                                   NULL,
                                                   NULL,
                                                   NULL,
                                                   &cbValue);
            if(FAILED(hr))
               goto Exit;
           // allocate the buffers.

           pwszName = new WCHAR[cchName];
           if(pwszName == NULL)
           {
               hr = E_OUTOFMEMORY;
               goto Exit;
           }

           pbValue = new BYTE[cbValue];
           if(pbValue == NULL)
           {
               hr = E_OUTOFMEMORY;
               goto Exit;
           }

           // get the attribute.

           hr = pHeaderInfo->GetAttributeByIndexEx(0xFFFF,
                                                   attIndex,
                                                   pwszName,
                                                   &cchName,
                                                   &attType,
                                                   &langIndex,
                                                   pbValue,
                                                   &cbValue);
           if(FAILED(hr))
               goto Exit;

           // Display the attribute global index and name.

//           TRACE("%3d - %S (Language %d):\n\t ", attIndex, pwszName, langIndex);

           // Display the attribute depending upon type.
           string str;

           switch(attType)
           {
           case WMT_TYPE_DWORD:
           case WMT_TYPE_QWORD:
           case WMT_TYPE_WORD:
//               TRACE("%d\n\n", (DWORD) *pbValue);
               break;
           case WMT_TYPE_STRING:
              {
                 str =  pbValue;
                 str = str.Left(500);
//               TRACE("%s\n\n",  str);
              }
               break;
           case WMT_TYPE_BINARY:
               //TRACE("<binary value>\n\n");
               break;
           case WMT_TYPE_BOOL:
               //TRACE("%s\n\n", ((BOOL) *pbValue == TRUE) ? "True" : "False");
               break;
           case WMT_TYPE_GUID:
               //TRACE("<GUID value>\n\n", (DWORD) *pbValue);
               break;
           }

           // Release allocated primitive::memory for the next pass.

           delete (pwszName);
           delete (pbValue);
           cchName = 0;
           cbValue = 0;
       } // End for attIndex.

   Exit:
       return hr;
   }

   HRESULT ShowAllAttributes(IWMHeaderInfo* pHeaderInfo)
   {
       HRESULT hr          = S_OK;
       
       WORD    cAttributes = 0;
       WCHAR*  pwszName    = NULL;
       WORD    cchName     = 0;
       BYTE*   pbValue     = NULL;
       unsigned short cbValue     = 0;
       WORD    langIndex   = 0;
       WORD    attIndex    = 0;
       WORD    wStreamNum  = 0xffff;

       WMT_ATTR_DATATYPE attType;

       // get the total number of attributes in the spfile->

       hr = pHeaderInfo->GetAttributeCount(0xFFFF, &cAttributes);
       if(hr == NS_E_INVALID_REQUEST)
          goto Exit;
       if(FAILED(hr))
          goto Exit;

       // Loop through all the attributes, retrieving and displaying each.

       for(attIndex = 0; attIndex < cAttributes; attIndex++)
       {
           // get the required buffer lengths for the name and value.

           hr = pHeaderInfo->GetAttributeByIndex(attIndex,
                                                   &wStreamNum,
                                                   NULL,
                                                   &cchName,
                                                   NULL,
                                                   NULL,
                                                   &cbValue);
            if(FAILED(hr))
               goto Exit;
           // allocate the buffers.

           pwszName = new WCHAR[cchName];
           if(pwszName == NULL)
           {
               hr = E_OUTOFMEMORY;
               goto Exit;
           }

           pbValue = new BYTE[cbValue];
           if(pbValue == NULL)
           {
               hr = E_OUTOFMEMORY;
               goto Exit;
           }

           // get the attribute.

           hr = pHeaderInfo->GetAttributeByIndex(attIndex,
                                                   &wStreamNum,
                                                   pwszName,
                                                   &cchName,
                                                   &attType,
                                                   pbValue,
                                                   &cbValue);
           if(FAILED(hr))
               goto Exit;

           // Display the attribute global index and name.

//           TRACE("%3d - %S (Language %d):\n\t ", attIndex, pwszName, langIndex);

           // Display the attribute depending upon type.

           switch(attType)
           {
           case WMT_TYPE_DWORD:
           case WMT_TYPE_QWORD:
           case WMT_TYPE_WORD:
//               TRACE("%d\n\n", (DWORD) *pbValue);
               break;
           case WMT_TYPE_STRING:
//               TRACE("%S\n\n", (WCHAR*) pbValue);
               break;
           case WMT_TYPE_BINARY:
//               TRACE("<binary value>\n\n");
               break;
           case WMT_TYPE_BOOL:
//               TRACE("%s\n\n", ((BOOL) *pbValue == TRUE) ? "True" : "False");
               break;
           case WMT_TYPE_GUID:
//               TRACE("<GUID value>\n\n", (DWORD) *pbValue);
               break;
           }

           // Release allocated primitive::memory for the next pass.

           delete (pwszName);
           delete (pbValue);
           cchName = 0;
           cbValue = 0;
       } // End for attIndex.

   Exit:
       return hr;
   }

   bool decoder::_DecoderInitialize(ex1::file *pfile)
   {
      m_uiReadSync = 0;
      m_pfile = pfile;
      m_bStop = false;
      m_bEOF = false;

      if(m_pwmstream != NULL && m_pwmstream->m_pfile == pfile)
         return true;


      m_pwmstream = new stream(get_app());

      pfile->seek_to_begin();

      m_pwmstream->m_pfile = pfile;


      if(m_psyncreader != NULL)
      {
         m_psyncreader->Close();
         m_psyncreader = NULL;
      }



      HRESULT hr;
      if(m_psyncreader == NULL)
      {
         hr = WMCreateSyncReader(
               NULL,
               0,
               &m_psyncreader);
         if(FAILED(hr))
            return false;
      }

      hr = m_psyncreader->OpenStream(m_pwmstream);

    /*  IWMHeaderInfo3 * pinfo3;

      m_psyncreader->QueryInterface(IID_IWMHeaderInfo3, (void **) &pinfo3);

      ShowAllAttributes(pinfo3);

      IWMHeaderInfo * pinfo;

      m_psyncreader->QueryInterface(IID_IWMHeaderInfo, (void **) &pinfo);

      ShowAllAttributes(pinfo);*/

      m_uiSamplesPerSec = 0;
      if(SUCCEEDED(hr))
      {
         HRESULT hr2 = m_psyncreader->GetOutputFormat(
            0,
            0,
            &m_poutputmediaprops);

         if(SUCCEEDED(hr2))
         {
            DWORD dw;
            HRESULT hr3 = m_poutputmediaprops->GetMediaType(
               NULL, &dw);
            if(SUCCEEDED(hr3))
            {
               m_pmediatype = (WM_MEDIA_TYPE *) new BYTE[dw];
               HRESULT hr4 = m_poutputmediaprops->GetMediaType(
                  m_pmediatype,
                  &dw);
               if(SUCCEEDED(hr4))
               {
                  if(m_pmediatype->formattype == WMFORMAT_WaveFormatEx)
                  {
                     WAVEFORMATEX * pex = (WAVEFORMATEX *) m_pmediatype->pbFormat;
                     m_uiSamplesPerSec = pex->nSamplesPerSec;
                  }
               }
            }
         }
      }

      IWMHeaderInfo3 * pheaderinfo3;
      HRESULT hr5 = m_psyncreader->QueryInterface(&pheaderinfo3);
      if(SUCCEEDED(hr5))
      {
         WORD c;
         hr5 = pheaderinfo3->GetAttributeCountEx(
           0,
           &c);
         if(SUCCEEDED(hr5))
         {
            WMT_ATTR_DATATYPE type;
            WORD lang;
            DWORD dwLen;
            WCHAR pwszName[1024];
            WORD wLen;
            for(int i = 0; i < c; i++)
            {
               wLen = 1024;
               hr5 = pheaderinfo3->GetAttributeByIndexEx(
                  0,
                  (WORD) i,
                  pwszName,
                  &wLen,
                  &type,
                  &lang,
                  NULL,
                  &dwLen);
               if(SUCCEEDED(hr5) && wstring(pwszName) == g_wszWMDuration && dwLen == 8)
               {
//                  WORD lLen;
                  QWORD qwDuration;
                  pheaderinfo3->GetAttributeByIndexEx(
                     0,
                     (WORD)i,
                     pwszName,
                     &wLen,
                     &type,
                     &lang,
                     (BYTE *) &qwDuration,
                     &dwLen);
                  m_nSampleCount =  __int64((double) qwDuration * (double) m_uiSamplesPerSec / (double) 10000000);
                  break;
               }
            }
         }

         
      }


      if(FAILED(hr))
         return false;

      return true;
      
   }
   void decoder::DecoderMoveNext()
   {
   }
   bool decoder::_DecoderEOF()
   {
      return m_bEOF;
   }
   LPBYTE decoder::DecoderGetBuffer()
   {
      return NULL;
   }

   int decoder::DecoderGetBufferSize()
   {
      return 0;
   }
   void decoder::DecoderRun()
   {
   }

   UINT decoder::DecoderGetSamplesPerSecond()
   {
      return (UINT) m_uiSamplesPerSec;
   }
   UINT decoder::DecoderGetChannelCount()
   {
      return 2;
   }
   UINT decoder::DecoderGetBitsPerSample()
   {
      return 16;
   }

   int decoder::_DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
   {
      LPBYTE lpbBuffer = (LPBYTE) lpvoidBuffer;
      UINT uiRemain = uiBufferSize;
      UINT uiPointer = 0;
      UINT uiSize;
      while(uiRemain > 0)
      {
         if(m_bStop)
            return uiPointer;

         if(m_fileFrame.get_size() <= 0)
         {
            ReadFrame();
         }

         if(m_fileFrame.get_size() <= 0)
         {
            m_bEOF = true;
            return uiPointer;
         }

         uiSize = m_fileFrame.RemoveBegin(&lpbBuffer[uiPointer], uiRemain);

         uiRemain -= uiSize;
         uiPointer += uiSize;

         if(uiSize <= 0)
            break;

      }
      return uiPointer;
   }

   void decoder::DecoderStop()
   {
      m_bStop = true;
   }

   void decoder::DecoderSeekBegin()
   {
      HRESULT hr = m_psyncreader->SetRange(0, 0);
      if(FAILED(hr))
      {
         TRACE("audio_decode_windows_media decoder::DecoderSeekBegin");
      }

      m_fileFrame.Truncate(0);
      m_dwRemain = m_dwFrameCount;
      m_bStop = false;
   }

   void decoder::ReadFrame()
   {
      HRESULT hr;
//      WORD    wStreamNum = 0;
      INSSBuffer*  pSample = NULL;
      QWORD  cnsSampleTime;
      QWORD  cnsDuration;
      DWORD  dwFlags;
      DWORD  dwOutputNum;


      // Loop through all the samples in the spfile->
      // get the next sample.
      hr = m_psyncreader->GetNextSample(0,
                                   &pSample,
                                   &cnsSampleTime,
                                   &cnsDuration,
                                   &dwFlags,
                                   &dwOutputNum,
                                   &m_wStreamNum);

      if(SUCCEEDED(hr))
      {
         DWORD dwLen;
         LPBYTE lpb;
         hr = pSample->GetLength(&dwLen);
         if(FAILED(hr))
         {
            m_bEOF = true;
            goto continue1;
         }
         hr = pSample->GetBuffer(&lpb);
         if(FAILED(hr))
         {
            m_bEOF = true;
            goto continue1;
         }
         m_fileFrame.write(lpb, dwLen);
         pSample->Release();
         pSample = NULL;
         cnsSampleTime     = 0;
         cnsDuration       = 0;
         dwFlags           = 0;
         dwOutputNum       = 0;
      }
      else
      {
         m_bEOF = true;
      }
   continue1:;

      
   }

   void decoder::OnDecoderEOF()
   {
   }

   bool decoder::DecoderGetAttribute(audio_decode::EAttribute eattribute, string & str)
   {
      string strName = GetAttributeName(eattribute);
      if(strName.is_empty())
         return false;
      
      HRESULT hr;
      WORD wStreamNum = 0xffff;
      WMT_ATTR_DATATYPE Type;
      WORD cbLength;
      IWMHeaderInfo * pinfo;

      m_psyncreader->QueryInterface(IID_IWMHeaderInfo, (void **) &pinfo);
      //
      // First, retrieve the length of the string, and allocate primitive::memory.
      //
      hr = pinfo->GetAttributeByName( &wStreamNum, gen::international::utf8_to_unicode(strName), 
                                      &Type, NULL, &cbLength );
      if( FAILED( hr ) )
      {
          return false;
      }
      wstring wstr;
      WCHAR *pwszTitle = wstr.alloc(cbLength);
      if( !pwszTitle )
      {
          return false;
      }


      //
      // Now, retrieve the string itself.
      //
      hr = pinfo->GetAttributeByName( &wStreamNum,  gen::international::utf8_to_unicode(strName), &Type, (BYTE *) pwszTitle, &cbLength );
      if( FAILED( hr ) )
      {
          return false;
      }


      gen::international::unicode_to_utf8(str, wstr);

      pinfo->Release();
      return true;
   }

   string decoder::GetAttributeName(audio_decode::EAttribute eattribute)
   {
      switch(eattribute)
      {
      case audio_decode::AttributeTitle:
         return "Title";
      case audio_decode::AttributeAuthor:
         return "Author";
      default:
         return "";
      }
   }

   __int64 decoder::DecoderGetSampleCount()
   {
      return m_nSampleCount;
   }


} // namespace audio_decode_window_media

audio_decode::decoder *  __cdecl NewDecoderInterface(::ca::application * papp)
{
   return dynamic_cast < audio_decode::decoder * > (new audio_decode_window_media::decoder(papp));
}

void  DeleteDecoderInterface(audio_decode::decoder * pdecoder)
{
   delete dynamic_cast < audio_decode_window_media::decoder * > (pdecoder);
}

