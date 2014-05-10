// 7zEncode.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../Common/CreateCoder.h"
#include "../../Common/FilterCoder.h"
#include "../../Common/LimitedStreams.h"
#include "../../Common/InOutTempBuffer.h"
#include "../../Common/ProgressUtils.h"
#include "../../Common/StreamObjects.h"

#include "7zEncode.h"
#include "7zSpecStream.h"*/

static const uint64_t k_Delta = 0x03;
static const uint64_t k_BCJ = 0x03030103;
static const uint64_t k_BCJ2 = 0x0303011B;


namespace n7z
{

   static void ConvertBindInfoToFolderItemInfo(const ::libcompress::coder_mixer::CBindInfo &bindInfo,
      const array < ::libcompress::method_id > decompressionMethods,
      CFolder &folder)
   {
      folder.Coders.remove_all();
      // bindInfo.CoderMethodIDs.clear();
      // folder.OutStreams.clear();
      folder.PackStreams.remove_all();
      folder.BindPairs.remove_all();
      int32_t i;
      for (i = 0; i < bindInfo.BindPairs.get_count(); i++)
      {
         CBindPair bindPair;
         bindPair.InIndex = bindInfo.BindPairs[i].InIndex;
         bindPair.OutIndex = bindInfo.BindPairs[i].OutIndex;
         folder.BindPairs.add(bindPair);
      }
      for (i = 0; i < bindInfo.Coders.get_count(); i++)
      {
         CCoderInfo & coderInfo = * folder.Coders.add_new();
         const ::libcompress::coder_mixer::CCoderStreamsInfo &coderStreamsInfo = bindInfo.Coders[i];
         coderInfo.NumInStreams = coderStreamsInfo.NumInStreams;
         coderInfo.NumOutStreams = coderStreamsInfo.NumOutStreams;
         coderInfo.MethodID = decompressionMethods[i];
         
      }
      for (i = 0; i < bindInfo.InStreams.get_count(); i++)
         folder.PackStreams.add(bindInfo.InStreams[i]);
   }

   HRESULT CEncoder::CreateMixerCoder(
      ::libcompress::codecs_info_interface *codecsInfo,
      const array < ::libcompress::codec_info_ex > *externalCodecs,
      const file_size *inSizeForReduce)
   {
      HRes hr;
      _mixerCoderSpec = new ::libcompress::coder_mixer::CCoderMixer2MT(get_app());
      _mixerCoder = _mixerCoderSpec;
      RINOK(_mixerCoderSpec->SetBindInfo(_bindInfo));
      for (int32_t i = 0; i < _options.Methods.get_count(); i++)
      {
         const CMethodFull &methodFull = _options.Methods[i];
         CCoderInfo &encodingInfo = *_codersInfo.add_new();
         encodingInfo.MethodID = methodFull.Id;
         smart_pointer < ::libcompress::coder_interface > encoder;
         smart_pointer < ::libcompress::coder2_interface > encoder2;


         if(FAILED(hr = CreateCoder(
            codecsInfo, externalCodecs,
            methodFull.Id, spquery(encoder), spquery(encoder2), true)))
         {
            return hr;
         }

         if (!encoder && !encoder2)
            return E_FAIL;

         smart_pointer < object > encoderCommon = encoder ? (object *)encoder : (object *)encoder2;

         {
            smart_pointer < ::libcompress::set_coder_mt_interface > setCoderMt;
            setCoderMt =   dynamic_cast < ::libcompress::set_coder_mt_interface * > (encoderCommon.m_p);
            if (setCoderMt)
            {
               if(FAILED(hr = setCoderMt->SetNumberOfThreads(_options.NumThreads)))
                  return hr;
            }
         }


         if(FAILED(hr = SetMethodProperties(methodFull, inSizeForReduce, encoderCommon)))
            return hr;

         /*
         smart_pointer<ICryptoResetSalt> resetSalt;
         encoderCommon.QueryInterface(IID_ICryptoResetSalt, (void **)&resetSalt);
         if (resetSalt != NULL)
         {
         resetSalt->ResetSalt();
         }
         */

#ifdef EXTERNAL_CODECS
         smart_pointer<ISetCompressCodecsInfo> setCompressCodecsInfo;
         encoderCommon.QueryInterface(IID_ISetCompressCodecsInfo, (void **)&setCompressCodecsInfo);
         if (setCompressCodecsInfo)
         {
            RINOK(setCompressCodecsInfo->SetCompressCodecsInfo(codecsInfo));
         }
#endif

         smart_pointer < ::crypto::set_password_interface > cryptoSetPassword;
         cryptoSetPassword = dynamic_cast < ::crypto::set_password_interface * > (encoderCommon.m_p);

         if (cryptoSetPassword)
         {
            ::file::byte_buffer buffer;
            wstring password = ::str::international::utf8_to_unicode(_options.Password);
            const uint32_t sizeInBytes = (const uint32_t) (password.get_length() * 2);
            buffer.SetCapacity(sizeInBytes);
            for (int32_t i = 0; i < password.get_length(); i++)
            {
               wchar_t ca = password[i];
               ((byte *)buffer)[i * 2] = (byte)ca;
               ((byte *)buffer)[i * 2 + 1] = (byte)(ca >> 8);
            }
            RINOK(cryptoSetPassword->CryptoSetPassword((const byte *)buffer, sizeInBytes));
         }

         if (encoder)
            _mixerCoderSpec->AddCoder(encoder);
         else
            _mixerCoderSpec->AddCoder2(encoder2);
      }
      return S_OK;
   }

   HRESULT CEncoder::Encode(
      ::libcompress::codecs_info_interface *codecsInfo,
      const array < ::libcompress::codec_info_ex > *externalCodecs,
      ::file::reader *inStream,
      const file_size *inStreamSize, const file_size *inSizeForReduce,
      CFolder &folderItem,
      ::file::writer *outStream,
      array<file_size> &packSizes,
      ::libcompress::progress_info_interface *compressProgress)
   {
      HRes hr;
      RINOK(EncoderConstr());

      if (_mixerCoderSpec == NULL)
      {
         if(FAILED(hr = CreateMixerCoder(codecsInfo, externalCodecs, inSizeForReduce)))
            return hr;
      }
      _mixerCoderSpec->ReInit();
      // _mixerCoderSpec->SetCoderInfo(0, NULL, NULL, progress);

      smart_pointer_array < ::file::temp_io_buffer > inOutTempBuffers;
      smart_pointer_array < ::file::temp_io_writer > tempBufferSpecs;
      smart_pointer_array < ::file::writer > tempBuffers;
      ::count numMethods = _bindInfo.Coders.get_count();
      index i;
      for (i = 1; i < _bindInfo.OutStreams.get_count(); i++)
      {
         inOutTempBuffers.add(new ::file::temp_io_buffer());
         inOutTempBuffers.last_element()->create();
         inOutTempBuffers.last_element()->InitWriting();
      }
      for (i = 1; i < _bindInfo.OutStreams.get_count(); i++)
      {
         ::file::temp_io_writer *tempBufferSpec = new ::file::temp_io_writer;
         smart_pointer < ::file::writer > tempBuffer = tempBufferSpec;
         tempBufferSpec->Init(inOutTempBuffers(i - 1));
         tempBuffers.add(tempBuffer);
         tempBufferSpecs.add(tempBufferSpec);
      }

      for (i = 0; i < numMethods; i++)
         _mixerCoderSpec->SetCoderInfo((uint32_t) i, NULL, NULL);

      if (_bindInfo.InStreams.is_empty())
         return E_FAIL;
      uint32_t mainCoderIndex, mainStreamIndex;
      _bindInfo.FindInStream(_bindInfo.InStreams[0], mainCoderIndex, mainStreamIndex);

      if (inStreamSize != NULL)
      {
         array<const file_size *> sizePointers;
         for (uint32_t i = 0; i < _bindInfo.Coders[mainCoderIndex].NumInStreams; i++)
            if (i == mainStreamIndex)
               sizePointers.add(inStreamSize);
            else
               sizePointers.add(NULL);
         _mixerCoderSpec->SetCoderInfo(mainCoderIndex, &sizePointers.first_element(), NULL);
      }


      // uint64_t outStreamStartPos;
      // RINOK(stream->Seek(0, STREAM_SEEK_CUR, &outStreamStartPos));

      ::libcompress::size_count_reader2 * inStreamSizeCountSpec = new ::libcompress::size_count_reader2;
      sp(::file::reader) inStreamSizeCount = inStreamSizeCountSpec;
      ::file::size_count_writer * outStreamSizeCountSpec = new ::file::size_count_writer;
      sp(::file::writer) outStreamSizeCount = outStreamSizeCountSpec;

      inStreamSizeCountSpec->Init(inStream);
      outStreamSizeCountSpec->SetStream(outStream);
      outStreamSizeCountSpec->Init();

      spa(::file::reader) inStreamPointers;
      spa(::file::writer) outStreamPointers;
      inStreamPointers.add(inStreamSizeCount);
      outStreamPointers.add(outStreamSizeCount);
      for (i = 1; i < _bindInfo.OutStreams.get_count(); i++)
         outStreamPointers.add(tempBuffers(i - 1));

      for (i = 0; i < _codersInfo.get_count(); i++)
      {
         CCoderInfo &encodingInfo = _codersInfo[i];

         smart_pointer < ::crypto::reset_init_vector_interface > resetInitVector;
         resetInitVector = dynamic_cast < ::crypto::reset_init_vector_interface * > (&_mixerCoderSpec->_coders[i]);
         if (resetInitVector != NULL)
         {
            resetInitVector->ResetInitVector();
         }

         smart_pointer < ::libcompress::write_coder_properties_interface >  writeCoderProperties;
         writeCoderProperties = dynamic_cast < ::libcompress::write_coder_properties_interface * >(&_mixerCoderSpec->_coders[i]);
         if (writeCoderProperties != NULL)
         {
            ::file::dynamic_buffered_writer *outStreamSpec = new ::file::dynamic_buffered_writer;
            smart_pointer < ::file::writer > outStream(outStreamSpec);
            outStreamSpec->Init();
            writeCoderProperties->WriteCoderProperties(outStream);
            outStreamSpec->CopyToBuffer(encodingInfo.Props);
         }
      }

      uint32_t progressIndex = mainCoderIndex;

      for (i = 0; i + 1 < _codersInfo.get_count(); i++)
      {
         uint64_t m = _codersInfo[i].MethodID;
         if (m == k_Delta || m == k_BCJ || m == k_BCJ2)
            progressIndex = (uint32_t) (i + 1);
      }

      _mixerCoderSpec->SetProgressCoderIndex(progressIndex);

      spa(::file::reader) inStreamPointersCode;

      inStreamPointersCode.add(inStreamPointers(0));

      RINOK(_mixerCoder->Code(inStreamPointersCode, NULL, outStreamPointers, NULL, compressProgress));

      ConvertBindInfoToFolderItemInfo(_decompressBindInfo, _decompressionMethods, folderItem);

      packSizes.add(outStreamSizeCountSpec->get_size());

      for (i = 1; i < _bindInfo.OutStreams.get_count(); i++)
      {
         ::file::temp_io_buffer &inOutTempBuffer = inOutTempBuffers[i - 1];
         RINOK(inOutTempBuffer.write_to_stream(outStream));
         packSizes.add((file_size) inOutTempBuffer.GetDataSize());
      }

      for (i = 0; i < (int32_t)_bindReverseConverter->NumSrcInStreams; i++)
      {
         int32_t binder = _bindInfo.FindBinderForInStream(
            _bindReverseConverter->DestOutToSrcInMap[i]);
         file_size streamSize;
         if (binder < 0)
            streamSize = inStreamSizeCountSpec->GetSize();
         else
            streamSize = _mixerCoderSpec->GetWriteProcessedSize(binder);
         folderItem.UnpackSizes.add(streamSize);
      }
      for (i = numMethods - 1; i >= 0; i--)
         folderItem.Coders[numMethods - 1 - i].Props = _codersInfo[i].Props;
      return S_OK;
   }


   CEncoder::CEncoder(sp(::base::application) papp, const CCompressionMethodMode &options):
      element(papp),
      _bindReverseConverter(0),
      _constructed(false)
   {
      if (options.is_empty())
         throw 1;

      _options = options;
      _mixerCoderSpec = NULL;
   }

   HRESULT CEncoder::EncoderConstr()
   {
      if (_constructed)
         return S_OK;
      if (_options.Methods.is_empty())
      {
         // it has only password method;
         if (!_options.PasswordIsDefined)
            throw 1;
         if (!_options.Binds.is_empty())
            throw 1;
         ::libcompress::coder_mixer::CCoderStreamsInfo coderStreamsInfo;
         CMethodFull method;

         method.NumInStreams = 1;
         method.NumOutStreams = 1;
         coderStreamsInfo.NumInStreams = 1;
         coderStreamsInfo.NumOutStreams = 1;
         method.Id = k_AES;

         _options.Methods.add(new CMethodFull(method));
         _bindInfo.Coders.add(coderStreamsInfo);

         _bindInfo.InStreams.add(0);
         _bindInfo.OutStreams.add(0);
      }
      else
      {

         uint32_t numInStreams = 0, numOutStreams = 0;
         int32_t i;
         for (i = 0; i < _options.Methods.get_count(); i++)
         {
            const CMethodFull &methodFull = _options.Methods[i];
            ::libcompress::coder_mixer::CCoderStreamsInfo coderStreamsInfo;
            coderStreamsInfo.NumInStreams = methodFull.NumOutStreams;
            coderStreamsInfo.NumOutStreams = methodFull.NumInStreams;
            if (_options.Binds.is_empty())
            {
               if (i < _options.Methods.get_count() - 1)
               {
                  ::libcompress::coder_mixer::CBindPair bindPair;
                  bindPair.InIndex = numInStreams + coderStreamsInfo.NumInStreams;
                  bindPair.OutIndex = numOutStreams;
                  _bindInfo.BindPairs.add(bindPair);
               }
               else
                  _bindInfo.OutStreams.insert_at(0, numOutStreams);
               for (uint32_t j = 1; j < coderStreamsInfo.NumOutStreams; j++)
                  _bindInfo.OutStreams.add(numOutStreams + j);
            }

            numInStreams += coderStreamsInfo.NumInStreams;
            numOutStreams += coderStreamsInfo.NumOutStreams;

            _bindInfo.Coders.add(coderStreamsInfo);
         }

         if (!_options.Binds.is_empty())
         {
            for (i = 0; i < _options.Binds.get_count(); i++)
            {
               ::libcompress::coder_mixer::CBindPair bindPair;
               const CBind &bind = _options.Binds[i];
               bindPair.InIndex = _bindInfo.GetCoderInStreamIndex(bind.InCoder) + bind.InStream;
               bindPair.OutIndex = _bindInfo.GetCoderOutStreamIndex(bind.OutCoder) + bind.OutStream;
               _bindInfo.BindPairs.add(bindPair);
            }
            for (i = 0; i < (int32_t)numOutStreams; i++)
               if (_bindInfo.FindBinderForOutStream(i) == -1)
                  _bindInfo.OutStreams.add(i);
         }

         for (i = 0; i < (int32_t)numInStreams; i++)
            if (_bindInfo.FindBinderForInStream(i) == -1)
               _bindInfo.InStreams.add(i);

         if (_bindInfo.InStreams.is_empty())
            throw 1; // this is error

         // Make main stream first in list
         int32_t inIndex = _bindInfo.InStreams[0];
         for (;;)
         {
            uint32_t coderIndex, coderStreamIndex;
            _bindInfo.FindInStream(inIndex, coderIndex, coderStreamIndex);
            uint32_t outIndex = _bindInfo.GetCoderOutStreamIndex(coderIndex);
            int32_t binder = _bindInfo.FindBinderForOutStream(outIndex);
            if (binder >= 0)
            {
               inIndex = _bindInfo.BindPairs[binder].InIndex;
               continue;
            }
            for (i = 0; i < _bindInfo.OutStreams.get_count(); i++)
               if (_bindInfo.OutStreams[i] == outIndex)
               {
                  _bindInfo.OutStreams.remove_at(i);
                  _bindInfo.OutStreams.insert_at(0, outIndex);
                  break;
               }
               break;
         }

         if (_options.PasswordIsDefined)
         {

            ::count numCryptoStreams = _bindInfo.OutStreams.get_count();

            for (i = 0; i < numCryptoStreams; i++)
            {
               ::libcompress::coder_mixer::CBindPair bindPair;
               bindPair.InIndex = numInStreams + i;
               bindPair.OutIndex = _bindInfo.OutStreams[i];
               _bindInfo.BindPairs.add(bindPair);
            }
            _bindInfo.OutStreams.remove_all();

            /*
            if (numCryptoStreams == 0)
            numCryptoStreams = 1;
            */

            for (i = 0; i < numCryptoStreams; i++)
            {
               ::libcompress::coder_mixer::CCoderStreamsInfo coderStreamsInfo;
               CMethodFull method;
               method.NumInStreams = 1;
               method.NumOutStreams = 1;
               coderStreamsInfo.NumInStreams = method.NumOutStreams;
               coderStreamsInfo.NumOutStreams = method.NumInStreams;
               method.Id = k_AES;

               _options.Methods.add(new CMethodFull(method));
               _bindInfo.Coders.add(coderStreamsInfo);
               _bindInfo.OutStreams.add(numOutStreams + i);
            }
         }

      }

      for (index i = _options.Methods.get_count() - 1; i >= 0; i--)
      {
         const CMethodFull &methodFull = _options.Methods[i];
         _decompressionMethods.add(methodFull.Id);
      }

      _bindReverseConverter = new ::libcompress::coder_mixer::CBindReverseConverter(_bindInfo);
      _bindReverseConverter->CreateReverseBindInfo(_decompressBindInfo);
      _constructed = true;
      return S_OK;
   }

   CEncoder::~CEncoder()
   {
      delete _bindReverseConverter;
   }

} // namespace n7z
