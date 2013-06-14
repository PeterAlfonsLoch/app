// FilterCoder.h
// from 7-zip on 2010-12-19
#pragma once

/*#include "../../Common/MyCom.h"
#include "../ICoder.h"
#include "../IPassword.h"*/

#define MY_QUERYINTERFACE_ENTRY_AG(i, sub0, sub) if (iid == IID_ ## i) \
{ if (!sub) RINOK(sub0->QueryInterface(IID_ ## i, (void **)&sub)) \
   *outObject = (void *(i *)this; AddRef(); return S_OK; }

namespace libcompress
{

   class CLASS_DECL_ca2 filter_coder:
      public coder_interface,
      public set_input_stream_interface,
      public set_output_stream_interface,
      public ::ca2::byte_stream,
      public ::ca2::output_stream_flush_interface,
      public ::crypto::set_password_interface,
      public ::libcompress::set_coder_properties_interface,
      public ::libcompress::write_coder_properties_interface,
      // public ICryptoResetSalt,
      public ::crypto::reset_init_vector_interface,
      public ::libcompress::set_decoder_properties2_interface
   {
   public:


      byte *                  _buffer;
      ::ca2::reader *         _inStream;
      ::ca2::writer *         _outStream;
      uint32_t                  _bufferPos;
      uint32_t                  _convertedPosBegin;
      uint32_t                  _convertedPosEnd;
      bool                    _outSizeIsDefined;
      uint64_t                  _outSize;
      uint64_t                  _nowPos64;


      HRESULT Init()
      {
         _nowPos64 = 0;
         _outSizeIsDefined = false;
         return Filter->Init();
      }

      ::crypto::set_password_interface *              _setPassword;
      ::libcompress::set_coder_properties_interface *    _SetCoderProperties;
      ::libcompress::write_coder_properties_interface *  _writeCoderProperties;
      // CMyComPtr<ICryptoResetSalt> _CryptoResetSalt;
      ::crypto::reset_init_vector_interface *         _CryptoResetInitVector;
      ::libcompress::set_decoder_properties2_interface * _setDecoderProperties;
      ::libcompress::filter_interface *                  Filter;

      filter_coder();
      ~filter_coder();

      HRESULT WriteWithLimit(::ca2::writer *outStream, uint32_t size);

      /*      MY_QUERYINTERFACE_BEGIN2(::libcompress::coder_interface)
      MY_QUERYINTERFACE_ENTRY(ICompressSetInStream)
      MY_QUERYINTERFACE_ENTRY(::ca2::byte_input_stream)
      MY_QUERYINTERFACE_ENTRY(ICompressSetOutStream)
      MY_QUERYINTERFACE_ENTRY(::ca2::byte_output_stream)
      MY_QUERYINTERFACE_ENTRY(IOutStreamFlush)

      #ifndef _NO_CRYPTO
      MY_QUERYINTERFACE_ENTRY_AG(::crypto::set_password_interface, Filter, _setPassword)
      #endif

      #ifndef EXTRACT_ONLY
      MY_QUERYINTERFACE_ENTRY_AG(ICompressSetCoderProperties, Filter, _SetCoderProperties)
      MY_QUERYINTERFACE_ENTRY_AG(::libcompress::write_coder_properties_interface, Filter, _writeCoderProperties)
      // MY_QUERYINTERFACE_ENTRY_AG(ICryptoResetSalt, Filter, _CryptoResetSalt)
      MY_QUERYINTERFACE_ENTRY_AG(::crypto::reset_init_vector_interface, Filter, _CryptoResetInitVector)
      #endif

      MY_QUERYINTERFACE_ENTRY_AG(ICompressSetDecoderProperties2, Filter, _setDecoderProperties)
      MY_QUERYINTERFACE_END
      MY_ADDREF_RELEASE*/


      ::ca2::HRes Code(::ca2::reader *inStream, ::ca2::writer *outStream, const file_size *inSize, const file_size *outSize, progress_info_interface *progress);
      ::ca2::HRes SetInStream(::ca2::reader *inStream);
      ::ca2::HRes SetOutStream(::ca2::writer *outStream);
      ::ca2::HRes ReleaseInStream();
      ::ca2::HRes ReleaseOutStream();
      ::primitive::memory_size read(void *data, ::primitive::memory_size size);
      void write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize);
      void flush();

      ::ca2::HRes CryptoSetPassword(const byte *data, uint32_t size);
      ::ca2::HRes SetCoderProperties(const int32_t *propIDs, const var *properties, uint32_t numProperties);
      ::ca2::HRes WriteCoderProperties(::ca2::writer *outStream);
      // ::ca2::HRes ResetSalt();
      ::ca2::HRes ResetInitVector();
      ::ca2::HRes SetDecoderProperties2(const byte *data, uint32_t size);
   };

   class input_stream_releaser
   {
   public:
      filter_coder *FilterCoder;
      input_stream_releaser(): FilterCoder(0) {}
      ~input_stream_releaser() { if (FilterCoder) FilterCoder->ReleaseInStream(); }
   };

   class output_stream_releaser
   {
   public:
      filter_coder *FilterCoder;
      output_stream_releaser(): FilterCoder(0) {}
      ~output_stream_releaser() { if (FilterCoder) FilterCoder->ReleaseOutStream(); }
   };

} // namespace libcompress
