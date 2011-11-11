#pragma once

namespace audio_decode
{

   class CLASS_DECL_ca encoder :
      virtual public ::radix::object
   {
   public:


      encoder(::ca::application * papp);
      virtual ~encoder(void);

      virtual void      EncoderSetSamplesPerSec(UINT user) = 0;
      virtual void      EncoderSetChannelCount(UINT user) = 0;
      virtual void      EncoderSetBitsPerSample(UINT user) = 0;
      virtual bool      EncoderSetFile(ex1::file * pfile) = 0;
      virtual bool      EncoderInitialize() = 0;
      //virtual bool      EncoderGetAttribute(EAttribute attribute, LPTSTR lpcszUTF8, int iSize);

      // return number of bytes written
      virtual void      EncoderWriteBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize) = 0;

      virtual bool      EncoderFinalize() = 0;
   };

} // namespace audio_decode

