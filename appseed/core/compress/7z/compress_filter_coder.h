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

   class CLASS_DECL_BASEa2 filter_coder:
      public coder_interface,
      public set_input_stream_interface,
      public set_output_stream_interface,
      public ::ca::byte_stream,
      public ::ca::output_stream_flush_interface,
      public ::crypto::set_password_interface,
      public ::libcompress::set_coder_properties_interface,
      public ::libcompress::write_coder_properties_interface,
      // public ICryptoResetSalt,
      public ::crypto::reset_init_vector_interface,
      public ::libcompress::set_decoder_properties2_interface
   {
   public:


      byte *                  _buffer;
      ::ca::reader *         _inStream;
      ::ca::writer *         _outStream;
      uint32                  _bufferPos;
      uint32                  _convertedPosBegin;
      uint32                  _convertedPosEnd;
      bool                    _outSizeIsDefined;
      uint64                  _outSize;
      uint64                  _nowPos64;


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

      HRESULT WriteWithLimit(::ca::writer *outStream, uint32 size);

      /*      MY_QUERYINTERFACE_BEGIN2(::libcompress::coder_interface)
      MY_QUERYINTERFACE_ENTRY(ICompressSetInStream)
      MY_QUERYINTERFACE_ENTRY(::ca::byte_input_stream)
      MY_QUERYINTERFACE_ENTRY(ICompressSetOutStream)
      MY_QUERYINTERFACE_ENTRY(::ca::byte_output_stream)
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


      ::ca::HRes Code(::ca::reader *inStream, ::ca::writer *outStream, const file_size_t *inSize, const file_size_t *outSize, progress_info_interface *progress);
      ::ca::HRes SetInStream(::ca::reader *inStream);
      ::ca::HRes SetOutStream(::ca::writer *outStream);
      ::ca::HRes ReleaseInStream();
      ::ca::HRes ReleaseOutStream();
      memory_size_t read(void *data, memory_size_t size);
      void write(const void *data, memory_size_t size, memory_size_t *processedSize);
      void Flush();

      ::ca::HRes CryptoSetPassword(const byte *data, uint32 size);
      ::ca::HRes SetCoderProperties(const int32_t *propIDs, const var *properties, uint32 numProperties);
      ::ca::HRes WriteCoderProperties(::ca::writer *outStream);
      // ::ca::HRes ResetSalt();
      ::ca::HRes ResetInitVector();
      ::ca::HRes SetDecoderProperties2(const byte *data, uint32 size);
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
