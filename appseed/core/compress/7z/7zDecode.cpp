// 7zDecode.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../Common/LimitedStreams.h"
#include "../../Common/LockedStream.h"
#include "../../Common/ProgressUtils.h"
#include "../../Common/StreamObjects.h"

#include "7zDecode.h"*/


namespace n7z
{

   static void ConvertFolderItemInfoToBindInfo(const CFolder &folder,
      CBindInfoEx &bindInfo)
   {
      bindInfo.remove_all();
      int32_t i;
      for (i = 0; i < folder.BindPairs.get_count(); i++)
      {
         ::libcompress::coder_mixer::CBindPair bindPair;
         bindPair.InIndex = (uint32_t)folder.BindPairs[i].InIndex;
         bindPair.OutIndex = (uint32_t)folder.BindPairs[i].OutIndex;
         bindInfo.BindPairs.add(bindPair);
      }
      uint32_t outStreamIndex = 0;
      for (i = 0; i < folder.Coders.get_count(); i++)
      {
         ::libcompress::coder_mixer::CCoderStreamsInfo coderStreamsInfo;
         const CCoderInfo &coderInfo = folder.Coders[i];
         coderStreamsInfo.NumInStreams = (uint32_t)coderInfo.NumInStreams;
         coderStreamsInfo.NumOutStreams = (uint32_t)coderInfo.NumOutStreams;
         bindInfo.Coders.add(coderStreamsInfo);
         bindInfo.CoderMethodIDs.add(coderInfo.MethodID);
         for (uint32_t j = 0; j < coderStreamsInfo.NumOutStreams; j++, outStreamIndex++)
            if (folder.FindBindPairForOutStream(outStreamIndex) < 0)
               bindInfo.OutStreams.add(outStreamIndex);
      }
      for (i = 0; i < folder.PackStreams.get_count(); i++)
         bindInfo.InStreams.add((uint32_t)folder.PackStreams[i]);
   }

   static bool AreCodersEqual(const ::libcompress::coder_mixer::CCoderStreamsInfo &a1,
      const ::libcompress::coder_mixer::CCoderStreamsInfo &a2)
   {
      return (a1.NumInStreams == a2.NumInStreams) &&
         (a1.NumOutStreams == a2.NumOutStreams);
   }

   static bool AreBindPairsEqual(const ::libcompress::coder_mixer::CBindPair &a1, const ::libcompress::coder_mixer::CBindPair &a2)
   {
      return (a1.InIndex == a2.InIndex) &&
         (a1.OutIndex == a2.OutIndex);
   }

   static bool AreBindInfoExEqual(const CBindInfoEx &a1, const CBindInfoEx &a2)
   {
      if (a1.Coders.get_count() != a2.Coders.get_count())
         return false;
      int32_t i;
      for (i = 0; i < a1.Coders.get_count(); i++)
         if (!AreCodersEqual(a1.Coders[i], a2.Coders[i]))
            return false;
      if (a1.BindPairs.get_count() != a2.BindPairs.get_count())
         return false;
      for (i = 0; i < a1.BindPairs.get_count(); i++)
         if (!AreBindPairsEqual(a1.BindPairs[i], a2.BindPairs[i]))
            return false;
      for (i = 0; i < a1.CoderMethodIDs.get_count(); i++)
         if (a1.CoderMethodIDs[i] != a2.CoderMethodIDs[i])
            return false;
      if (a1.InStreams.get_count() != a2.InStreams.get_count())
         return false;
      if (a1.OutStreams.get_count() != a2.OutStreams.get_count())
         return false;
      return true;
   }

   CDecoder::CDecoder(sp(::base::application) papp, bool multiThread) :
      element(papp)
   {
      multiThread = true;
      _multiThread = multiThread;
      _bindInfoExPrevIsDefined = false;
   }

   CDecoder::~CDecoder()
   {
   }

   HRESULT CDecoder::Decode(
      ::libcompress::codecs_info_interface * codecsInfo,
      const array < ::libcompress::codec_info_ex > * externalCodecs,
      ::file::input_stream *inStream,
      file_position startPos,
      const file_size * packSizes,
      const CFolder &folderInfo,
      ::file::writer *outStream,
      ::libcompress::progress_info_interface *compressProgress,
      ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined,
      bool mtMode, uint32_t numThreads
      )
   {
      HRes hr;
      if (!folderInfo.CheckStructure())
         return E_NOTIMPL;
      passwordIsDefined = false;
      smart_pointer_array < ::file::reader > inStreams;

      ::file::locked_in_stream lockedInStream;
      lockedInStream.Init(inStream);

      for (int32_t j = 0; j < folderInfo.PackStreams.get_count(); j++)
      {
         ::file::locked_reader *lockedStreamImpSpec = new ::file::locked_reader;
         smart_pointer < ::file::reader > lockedStreamImp = lockedStreamImpSpec;
         lockedStreamImpSpec->Init(&lockedInStream, (file_size) startPos);
         startPos += packSizes[j];

         ::file::limited_reader *streamSpec = new ::file::limited_reader;
         streamSpec->SetStream(lockedStreamImp);
         streamSpec->Init(packSizes[j]);
         inStreams.add((::file::reader *) streamSpec);
      }

      ::count numCoders = folderInfo.Coders.get_count();

      CBindInfoEx bindInfo;
      ConvertFolderItemInfoToBindInfo(folderInfo, bindInfo);
      bool createNewCoders;
      if (!_bindInfoExPrevIsDefined)
         createNewCoders = true;
      else
         createNewCoders = !AreBindInfoExEqual(bindInfo, _bindInfoExPrev);
      if (createNewCoders)
      {
         int32_t i;
         _decoders.remove_all();
         // _decoders2.clear();

         ::release(_mixerCoder.m_p);

         if (_multiThread)
         {
            _mixerCoderMTSpec = new ::libcompress::coder_mixer::CCoderMixer2MT(get_app());
            _mixerCoder = _mixerCoderMTSpec;
            _mixerCoderCommon = _mixerCoderMTSpec;
         }
         else
         {
#ifdef _ST_MODE
            _mixerCoderSTSpec = new ::libcompress::coder_mixer::CCoderMixer2ST(get_app());
            _mixerCoder = _mixerCoderSTSpec;
            _mixerCoderCommon = _mixerCoderSTSpec;
#endif
         }
         RINOK(_mixerCoderCommon->SetBindInfo(bindInfo));

         for (i = 0; i < numCoders; i++)
         {
            const CCoderInfo &coderInfo = folderInfo.Coders[i];


            smart_pointer < ::libcompress::coder_interface > decoder;
            smart_pointer < ::libcompress::coder2_interface > decoder2;

            if(FAILED(hr = ::libcompress::CreateCoder(
               codecsInfo, externalCodecs,
               coderInfo.MethodID, spquery(decoder), spquery(decoder2), false)))
            {
               return  hr;
            }
            smart_pointer < object > decoderUnknown;
            if (coderInfo.IsSimpleCoder())
            {
               if (decoder == NULL)
                  return E_NOTIMPL;

               decoderUnknown = (object *)decoder;

               if (_multiThread)
                  _mixerCoderMTSpec->AddCoder(decoder);
#ifdef _ST_MODE
               else
                  _mixerCoderSTSpec->AddCoder(decoder, false);
#endif
            }
            else
            {
               if (decoder2.is_null())
                  return E_NOTIMPL;
               decoderUnknown = (object *)decoder2;
               if (_multiThread)
                  _mixerCoderMTSpec->AddCoder2(decoder2);
#ifdef _ST_MODE
               else
                  _mixerCoderSTSpec->AddCoder2(decoder2, false);
#endif
            }
            _decoders.add(decoderUnknown.m_p);
            smart_pointer < ::libcompress::set_codecs_info_interface > setCompressCodecsInfo;
            setCompressCodecsInfo = dynamic_cast < ::libcompress::set_codecs_info_interface * > (setCompressCodecsInfo.m_p);
            if (setCompressCodecsInfo)
            {
               RINOK(setCompressCodecsInfo->SetCompressCodecsInfo(codecsInfo));
            }
         }
         _bindInfoExPrev = bindInfo;
         _bindInfoExPrevIsDefined = true;
      }
      int32_t i;
      _mixerCoderCommon->ReInit();

      uint32_t packStreamIndex = 0, unpackStreamIndex = 0;
      uint32_t coderIndex = 0;
      // uint32_t coder2Index = 0;

      for (i = 0; i < numCoders; i++)
      {
         const CCoderInfo &coderInfo = folderInfo.Coders[i];
//         smart_pointer<element> &decoder = _decoders[coderIndex];

         {
            smart_pointer < ::libcompress::set_decoder_properties2_interface > setDecoderProperties;
            setDecoderProperties = dynamic_cast < ::libcompress::set_decoder_properties2_interface * > (setDecoderProperties.m_p);
            if (setDecoderProperties)
            {
               const ::file::byte_buffer &props = coderInfo.Props;
               size_t size = props.GetCapacity();
               if (size > 0xFFFFFFFF)
                  return E_NOTIMPL;
               // if (size > 0)
               {
                  RINOK(setDecoderProperties->SetDecoderProperties2((const byte *)props, (uint32_t)size));
               }
            }
         }

         if (mtMode)
         {
            smart_pointer < ::libcompress::set_coder_mt_interface > setCoderMt;
            setCoderMt = dynamic_cast < ::libcompress::set_coder_mt_interface * > (setCoderMt.m_p);
            if (setCoderMt)
            {
               RINOK(setCoderMt->SetNumberOfThreads(numThreads));
            }
         }

         {
            smart_pointer < ::crypto::set_password_interface > cryptoSetPassword;
            cryptoSetPassword = dynamic_cast < ::crypto::set_password_interface * > (cryptoSetPassword.m_p);
            if (cryptoSetPassword)
            {
               if (getTextPassword == 0)
                  return E_FAIL;
               string passwordBSTR;
               if(FAILED(hr = getTextPassword->CryptoGetTextPassword(passwordBSTR)))
               {
                  return hr;
               }
               ::file::byte_buffer buffer;
               passwordIsDefined = true;
               wstring password(::str::international::utf8_to_unicode(passwordBSTR));
               const uint32_t sizeInBytes = (const uint32_t ) (password.get_length() * 2);
               buffer.SetCapacity(sizeInBytes);
               for (int32_t i = 0; i < password.get_length(); i++)
               {
                  wchar_t ca = password[i];
                  ((byte *)buffer)[i * 2] = (byte)ca;
                  ((byte *)buffer)[i * 2 + 1] = (byte)(ca >> 8);
               }
               RINOK(cryptoSetPassword->CryptoSetPassword((const byte *)buffer, sizeInBytes));
            }
         }

         coderIndex++;

         uint32_t numInStreams = (uint32_t)coderInfo.NumInStreams;
         uint32_t numOutStreams = (uint32_t)coderInfo.NumOutStreams;
         array<const file_size *> packSizesPointers;
         array<const file_size *> unpackSizesPointers;
         packSizesPointers.allocate(0, numInStreams);
         unpackSizesPointers.allocate(0, numOutStreams);
         uint32_t j;
         for (j = 0; j < numOutStreams; j++, unpackStreamIndex++)
            unpackSizesPointers.add(&folderInfo.UnpackSizes[unpackStreamIndex]);

         for (j = 0; j < numInStreams; j++, packStreamIndex++)
         {
            int32_t bindPairIndex = folderInfo.FindBindPairForInStream(packStreamIndex);
            if (bindPairIndex >= 0)
               packSizesPointers.add(
               &folderInfo.UnpackSizes[(uint32_t)folderInfo.BindPairs[bindPairIndex].OutIndex]);
            else
            {
               int32_t index = folderInfo.FindPackStreamArrayIndex(packStreamIndex);
               if (index < 0)
                  return E_FAIL;
               packSizesPointers.add(&packSizes[index]);
            }
         }

         _mixerCoderCommon->SetCoderInfo(i,
            &packSizesPointers.first_element(),
            &unpackSizesPointers.first_element());
      }
      uint32_t mainCoder, temp;
      bindInfo.FindOutStream(bindInfo.OutStreams[0], mainCoder, temp);

      if (_multiThread)
         _mixerCoderMTSpec->SetProgressCoderIndex(mainCoder);
      /*
      else
      _mixerCoderSTSpec->SetProgressCoderIndex(mainCoder);;
      */

      if (numCoders == 0)
         return 0;
      spa(::file::reader) inStreamPointers;
      inStreamPointers.set_size(0, inStreams.get_count());
      for (i = 0; i < inStreams.get_count(); i++)
         inStreamPointers.add(inStreams(i));
      spa(::file::writer) outStreamPointers;
      outStreamPointers.add(outStream);
      return _mixerCoder->Code(inStreamPointers, NULL, outStreamPointers, NULL, compressProgress);
   }

} // namespace n7z
