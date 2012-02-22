// 7zDecode.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "StdAfx.h"

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
      int i;
      for (i = 0; i < folder.BindPairs.get_count(); i++)
      {
         ::compress::coder_mixer::CBindPair bindPair;
         bindPair.InIndex = (uint32)folder.BindPairs[i].InIndex;
         bindPair.OutIndex = (uint32)folder.BindPairs[i].OutIndex;
         bindInfo.BindPairs.add(bindPair);
      }
      uint32 outStreamIndex = 0;
      for (i = 0; i < folder.Coders.get_count(); i++)
      {
         ::compress::coder_mixer::CCoderStreamsInfo coderStreamsInfo;
         const CCoderInfo &coderInfo = folder.Coders[i];
         coderStreamsInfo.NumInStreams = (uint32)coderInfo.NumInStreams;
         coderStreamsInfo.NumOutStreams = (uint32)coderInfo.NumOutStreams;
         bindInfo.Coders.add(coderStreamsInfo);
         bindInfo.CoderMethodIDs.add(coderInfo.MethodID);
         for (uint32 j = 0; j < coderStreamsInfo.NumOutStreams; j++, outStreamIndex++)
            if (folder.FindBindPairForOutStream(outStreamIndex) < 0)
               bindInfo.OutStreams.add(outStreamIndex);
      }
      for (i = 0; i < folder.PackStreams.get_count(); i++)
         bindInfo.InStreams.add((uint32)folder.PackStreams[i]);
   }

   static bool AreCodersEqual(const ::compress::coder_mixer::CCoderStreamsInfo &a1,
      const ::compress::coder_mixer::CCoderStreamsInfo &a2)
   {
      return (a1.NumInStreams == a2.NumInStreams) &&
         (a1.NumOutStreams == a2.NumOutStreams);
   }

   static bool AreBindPairsEqual(const ::compress::coder_mixer::CBindPair &a1, const ::compress::coder_mixer::CBindPair &a2)
   {
      return (a1.InIndex == a2.InIndex) &&
         (a1.OutIndex == a2.OutIndex);
   }

   static bool AreBindInfoExEqual(const CBindInfoEx &a1, const CBindInfoEx &a2)
   {
      if (a1.Coders.get_count() != a2.Coders.get_count())
         return false;
      int i;
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

   CDecoder::CDecoder(bool multiThread)
   {
      multiThread = true;
      _multiThread = multiThread;
      _bindInfoExPrevIsDefined = false;
   }

   HRESULT CDecoder::Decode(
      ::compress::codecs_info_interface * codecsInfo, const base_array<::compress::codec_info_ex> * externalCodecs,
      ::ex1::byte_input_stream *inStream,
      file_position startPos,
      const file_size * packSizes,
      const CFolder &folderInfo,
      ::ex1::writer *outStream,
      ::compress::progress_info_interface *compressProgress,
      ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined,
      bool mtMode, uint32 numThreads
      )
   {
      ex1::HRes hr;
      if (!folderInfo.CheckStructure())
         return E_NOTIMPL;
      passwordIsDefined = false;
      array_ptr_alloc< ::ca::smart_pointer<::ex1::reader> > inStreams;

      ::ex1::locked_in_stream lockedInStream;
      lockedInStream.Init(inStream);

      for (int j = 0; j < folderInfo.PackStreams.get_count(); j++)
      {
         ::ex1::locked_reader *lockedStreamImpSpec = new ::ex1::locked_reader;
         ::ca::smart_pointer<::ex1::reader> lockedStreamImp = lockedStreamImpSpec;
         lockedStreamImpSpec->Init(&lockedInStream, (file_size) startPos);
         startPos += packSizes[j];

         ::ex1::limited_reader *streamSpec = new
            ::ex1::limited_reader;
         ::ca::smart_pointer<::ex1::reader> inStream = streamSpec;
         streamSpec->SetStream(lockedStreamImp);
         streamSpec->Init(packSizes[j]);
         inStreams.add(inStream);
      }

      count numCoders = folderInfo.Coders.get_count();

      CBindInfoEx bindInfo;
      ConvertFolderItemInfoToBindInfo(folderInfo, bindInfo);
      bool createNewCoders;
      if (!_bindInfoExPrevIsDefined)
         createNewCoders = true;
      else
         createNewCoders = !AreBindInfoExEqual(bindInfo, _bindInfoExPrev);
      if (createNewCoders)
      {
         int i;
         _decoders.remove_all();
         // _decoders2.clear();

         gen::release(_mixerCoder.m_p);

         if (_multiThread)
         {
            _mixerCoderMTSpec = new ::compress::coder_mixer::CCoderMixer2MT;
            _mixerCoder = _mixerCoderMTSpec;
            _mixerCoderCommon = _mixerCoderMTSpec;
         }
         else
         {
#ifdef _ST_MODE
            _mixerCoderSTSpec = new ::compress::coder_mixer::CCoderMixer2ST;
            _mixerCoder = _mixerCoderSTSpec;
            _mixerCoderCommon = _mixerCoderSTSpec;
#endif
         }
         RINOK(_mixerCoderCommon->SetBindInfo(bindInfo));

         for (i = 0; i < numCoders; i++)
         {
            const CCoderInfo &coderInfo = folderInfo.Coders[i];


            ::ca::smart_pointer<::compress::coder_interface> decoder;
            ::ca::smart_pointer<::compress::coder2_interface> decoder2;

            if(FAILED(hr = ::compress::CreateCoder(
               codecsInfo, externalCodecs,
               coderInfo.MethodID, decoder, decoder2, false)))
            {
               return  hr;
            }
            ::ca::smart_pointer<::radix::object> decoderUnknown;
            if (coderInfo.IsSimpleCoder())
            {
               if (decoder == 0)
                  return E_NOTIMPL;

               decoderUnknown = (::radix::object *)decoder;

               if (_multiThread)
                  _mixerCoderMTSpec->AddCoder(decoder);
#ifdef _ST_MODE
               else
                  _mixerCoderSTSpec->AddCoder(decoder, false);
#endif
            }
            else
            {
               if (decoder2 == 0)
                  return E_NOTIMPL;
               decoderUnknown = (::radix::object *)decoder2;
               if (_multiThread)
                  _mixerCoderMTSpec->AddCoder2(decoder2);
#ifdef _ST_MODE
               else
                  _mixerCoderSTSpec->AddCoder2(decoder2, false);
#endif
            }
            _decoders.add(decoderUnknown.m_p);
            ::ca::smart_pointer<::compress::set_codecs_info_interface> setCompressCodecsInfo;
            setCompressCodecsInfo = dynamic_cast < ::compress::set_codecs_info_interface * > (setCompressCodecsInfo.m_p);
            if (setCompressCodecsInfo)
            {
               RINOK(setCompressCodecsInfo->SetCompressCodecsInfo(codecsInfo));
            }
         }
         _bindInfoExPrev = bindInfo;
         _bindInfoExPrevIsDefined = true;
      }
      int i;
      _mixerCoderCommon->ReInit();

      uint32 packStreamIndex = 0, unpackStreamIndex = 0;
      uint32 coderIndex = 0;
      // uint32 coder2Index = 0;

      for (i = 0; i < numCoders; i++)
      {
         const CCoderInfo &coderInfo = folderInfo.Coders[i];
//         ::ca::smart_pointer<::ca::ca> &decoder = _decoders[coderIndex];

         {
            ::ca::smart_pointer<::compress::set_decoder_properties2_interface> setDecoderProperties;
            setDecoderProperties = dynamic_cast < ::compress::set_decoder_properties2_interface * > (setDecoderProperties.m_p);
            if (setDecoderProperties)
            {
               const ::ex1::byte_buffer &props = coderInfo.Props;
               size_t size = props.GetCapacity();
               if (size > 0xFFFFFFFF)
                  return E_NOTIMPL;
               // if (size > 0)
               {
                  RINOK(setDecoderProperties->SetDecoderProperties2((const byte *)props, (uint32)size));
               }
            }
         }

         if (mtMode)
         {
            ::ca::smart_pointer<::compress::set_coder_mt_interface> setCoderMt;
            setCoderMt = dynamic_cast < ::compress::set_coder_mt_interface * > (setCoderMt.m_p);
            if (setCoderMt)
            {
               RINOK(setCoderMt->SetNumberOfThreads(numThreads));
            }
         }

         {
            ::ca::smart_pointer<::crypto::set_password_interface> cryptoSetPassword;
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
               ::ex1::byte_buffer buffer;
               passwordIsDefined = true;
               wstring password(gen::international::utf8_to_unicode(passwordBSTR));
               const uint32 sizeInBytes = (const uint32_t ) (password.get_length() * 2);
               buffer.SetCapacity(sizeInBytes);
               for (int i = 0; i < password.get_length(); i++)
               {
                  wchar_t c = password[i];
                  ((byte *)buffer)[i * 2] = (byte)c;
                  ((byte *)buffer)[i * 2 + 1] = (byte)(c >> 8);
               }
               RINOK(cryptoSetPassword->CryptoSetPassword((const byte *)buffer, sizeInBytes));
            }
         }

         coderIndex++;

         uint32 numInStreams = (uint32)coderInfo.NumInStreams;
         uint32 numOutStreams = (uint32)coderInfo.NumOutStreams;
         base_array<const file_size *> packSizesPointers;
         base_array<const file_size *> unpackSizesPointers;
         packSizesPointers.set_size(0, numInStreams);
         unpackSizesPointers.set_size(0, numOutStreams);
         uint32 j;
         for (j = 0; j < numOutStreams; j++, unpackStreamIndex++)
            unpackSizesPointers.add(&folderInfo.UnpackSizes[unpackStreamIndex]);

         for (j = 0; j < numInStreams; j++, packStreamIndex++)
         {
            int bindPairIndex = folderInfo.FindBindPairForInStream(packStreamIndex);
            if (bindPairIndex >= 0)
               packSizesPointers.add(
               &folderInfo.UnpackSizes[(uint32)folderInfo.BindPairs[bindPairIndex].OutIndex]);
            else
            {
               int index = folderInfo.FindPackStreamArrayIndex(packStreamIndex);
               if (index < 0)
                  return E_FAIL;
               packSizesPointers.add(&packSizes[index]);
            }
         }

         _mixerCoderCommon->SetCoderInfo(i,
            &packSizesPointers.first_element(),
            &unpackSizesPointers.first_element());
      }
      uint32 mainCoder, temp;
      bindInfo.FindOutStream(bindInfo.OutStreams[0], mainCoder, temp);

      if (_multiThread)
         _mixerCoderMTSpec->SetProgressCoderIndex(mainCoder);
      /*
      else
      _mixerCoderSTSpec->SetProgressCoderIndex(mainCoder);;
      */

      if (numCoders == 0)
         return 0;
      base_array<::ex1::reader *> inStreamPointers;
      inStreamPointers.set_size(0, inStreams.get_count());
      for (i = 0; i < inStreams.get_count(); i++)
         inStreamPointers.add(inStreams[i]);
      ::ex1::writer *outStreamPointer = outStream;
      return _mixerCoder->Code(&inStreamPointers.first_element(), NULL, (const uint32_t) inStreams.get_count(), &outStreamPointer, NULL, 1, compressProgress);
   }

} // namespace n7z
