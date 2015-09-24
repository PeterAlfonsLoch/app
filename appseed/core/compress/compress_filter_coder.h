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

   class CLASS_DECL_CORE filter_coder:
      public coder_interface,
      public set_input_stream_interface,
      public set_output_stream_interface,
      public ::file::byte_stream,
      public ::file::output_stream_flush,
      public ::crypto::set_password_interface,
      public ::libcompress::set_coder_properties_interface,
      public ::libcompress::write_coder_properties_interface,
      // public ICryptoResetSalt,
      public ::crypto::reset_init_vector_interface,
      public ::libcompress::set_decoder_properties2_interface
   {
   public:


      byte *                  _buffer;
      ::file::reader *         _inStream;
      ::file::writer *         _outStream;
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

      HRESULT WriteWithLimit(::file::writer *outStream, uint32_t size);

      /*      MY_QUERYINTERFACE_BEGIN2(::libcompress::coder_interface)
      MY_QUERYINTERFACE_ENTRY(ICompressSetInStream)
      MY_QUERYINTERFACE_ENTRY(::file::input_stream)
      MY_QUERYINTERFACE_ENTRY(ICompressSetOutStream)
      MY_QUERYINTERFACE_ENTRY(::file::output_stream)
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


      HRes Code(::file::reader *inStream, ::file::writer *outStream, const file_size *inSize, const file_size *outSize, progress_info_interface *progress);
      HRes SetInStream(::file::reader *inStream);
      HRes SetOutStream(::file::writer *outStream);
      HRes ReleaseInStream();
      HRes ReleaseOutStream();
      memory_size_t read(void *data, memory_size_t size);
      void write(const void *data, memory_size_t size, memory_size_t *processedSize);
      void flush();

      HRes CryptoSetPassword(const byte *data, uint32_t size);
      HRes SetCoderProperties(const int32_t *propIDs, const var *properties, uint32_t numProperties);
      HRes WriteCoderProperties(::file::writer *outStream);
      // HRes ResetSalt();
      HRes ResetInitVector();
      HRes SetDecoderProperties2(const byte *data, uint32_t size);
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
