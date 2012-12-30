// FilterCoder.h
// from 7-zip on 2010-12-19
#pragma once

/*#include "../../Common/MyCom.h"
#include "../ICoder.h"
#include "../IPassword.h"*/

#define MY_QUERYINTERFACE_ENTRY_AG(i, sub0, sub) if (iid == IID_ ## i) \
{ if (!sub) RINOK(sub0->QueryInterface(IID_ ## i, (void **)&sub)) \
   *outObject = (void *(i *)this; AddRef(); return S_OK; }

namespace compress
{

   class CLASS_DECL_ca filter_coder:
      public coder_interface,
      public set_input_stream_interface,
      public set_output_stream_interface,
      public ::ex1::byte_stream,
      public ::ex1::output_stream_flush_interface,
      public ::crypto::set_password_interface,
      public ::compress::set_coder_properties_interface,
      public ::compress::write_coder_properties_interface,
      // public ICryptoResetSalt,
      public ::crypto::reset_init_vector_interface,
      public ::compress::set_decoder_properties2_interface
   {
   public:


      byte *                  _buffer;
      ::ex1::reader *         _inStream;
      ::ex1::writer *         _outStream;
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
      ::compress::set_coder_properties_interface *    _SetCoderProperties;
      ::compress::write_coder_properties_interface *  _writeCoderProperties;
      // CMyComPtr<ICryptoResetSalt> _CryptoResetSalt;
      ::crypto::reset_init_vector_interface *         _CryptoResetInitVector;
      ::compress::set_decoder_properties2_interface * _setDecoderProperties;
      ::compress::filter_interface *                  Filter;

      filter_coder();
      ~filter_coder();

      HRESULT WriteWithLimit(::ex1::writer *outStream, uint32 size);

      /*      MY_QUERYINTERFACE_BEGIN2(::compress::coder_interface)
      MY_QUERYINTERFACE_ENTRY(ICompressSetInStream)
      MY_QUERYINTERFACE_ENTRY(::ex1::byte_input_stream)
      MY_QUERYINTERFACE_ENTRY(ICompressSetOutStream)
      MY_QUERYINTERFACE_ENTRY(::ex1::byte_output_stream)
      MY_QUERYINTERFACE_ENTRY(IOutStreamFlush)

      #ifndef _NO_CRYPTO
      MY_QUERYINTERFACE_ENTRY_AG(::crypto::set_password_interface, Filter, _setPassword)
      #endif

      #ifndef EXTRACT_ONLY
      MY_QUERYINTERFACE_ENTRY_AG(ICompressSetCoderProperties, Filter, _SetCoderProperties)
      MY_QUERYINTERFACE_ENTRY_AG(::compress::write_coder_properties_interface, Filter, _writeCoderProperties)
      // MY_QUERYINTERFACE_ENTRY_AG(ICryptoResetSalt, Filter, _CryptoResetSalt)
      MY_QUERYINTERFACE_ENTRY_AG(::crypto::reset_init_vector_interface, Filter, _CryptoResetInitVector)
      #endif

      MY_QUERYINTERFACE_ENTRY_AG(ICompressSetDecoderProperties2, Filter, _setDecoderProperties)
      MY_QUERYINTERFACE_END
      MY_ADDREF_RELEASE*/


      ex1::HRes Code(::ex1::reader *inStream, ::ex1::writer *outStream, const file_size *inSize, const file_size *outSize, progress_info_interface *progress);
      ex1::HRes SetInStream(::ex1::reader *inStream);
      ex1::HRes SetOutStream(::ex1::writer *outStream);
      ex1::HRes ReleaseInStream();
      ex1::HRes ReleaseOutStream();
      ::primitive::memory_size read(void *data, ::primitive::memory_size size);
      void write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize);
      void Flush();

      ex1::HRes CryptoSetPassword(const byte *data, uint32 size);
      ex1::HRes SetCoderProperties(const int32_t *propIDs, const var *properties, uint32 numProperties);
      ex1::HRes WriteCoderProperties(::ex1::writer *outStream);
      // ex1::HRes ResetSalt();
      ex1::HRes ResetInitVector();
      ex1::HRes SetDecoderProperties2(const byte *data, uint32 size);
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

} // namespace compress
