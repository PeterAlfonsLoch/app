// CoderMixer2MT.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"

namespace libcompress
{

   namespace coder_mixer
   {

      CCoder2::CCoder2(::ca::application * papp, uint32_t numInStreams, uint32_t numOutStreams):
               ca(papp),
            thread(papp),
         CCoderInfo2(numInStreams, numOutStreams)
      {
         InStreams.set_size(0, NumInStreams);
         InStreamPointers.set_size(0, NumInStreams);
         OutStreams.set_size(0, NumOutStreams);
         OutStreamPointers.set_size(0, NumOutStreams);
      }

      int32_t CCoder2::run() { Code(NULL); return 0;}

      void CCoder2::Code(::libcompress::progress_info_interface *progress)
      {
         InStreamPointers.remove_all();
         OutStreamPointers.remove_all();
         for(uint32_t i = 0; i < NumInStreams; i++)
         {
            if (InSizePointers[i] != NULL)
               InSizePointers[i] = &InSizes[i];
            InStreamPointers.add((::gen::reader *)InStreams[i]);
         }
         for(uint32_t i = 0; i < NumOutStreams; i++)
         {
            if (OutSizePointers[i] != NULL)
               OutSizePointers[i] = &OutSizes[i];
            OutStreamPointers.add((::gen::writer *)OutStreams[i]);
         }
         if (Coder)
            Result = Coder->Code(InStreamPointers[0], OutStreamPointers[0],
            InSizePointers[0], OutSizePointers[0], progress);
         else
            Result = Coder2->Code(&InStreamPointers.first_element(), &InSizePointers.first_element(), NumInStreams,
            &OutStreamPointers.first_element(), &OutSizePointers.first_element(), NumOutStreams, progress);
         {
            for(int32_t i = 0; i < InStreams.get_count(); i++)
            {
               gen::release(InStreams[i].m_p);
            }
            for(int32_t i = 0; i < OutStreams.get_count(); i++)
            {
               gen::release(OutStreams[i].m_p);
            }
         }
      }

      static void SetSizes(const file_size **srcSizes, base_array<file_size> &sizes,
         base_array<const file_size *> &sizePointers, uint32_t numItems)
      {
         sizes.remove_all();
         sizePointers.remove_all();
         for (uint32_t i = 0; i < numItems; i++)
         {
            if (srcSizes == 0 || srcSizes[i] == NULL)
            {
               sizes.add((file_size) 0);
               sizePointers.add(NULL);
            }
            else
            {
               sizes.add(*srcSizes[i]);
               sizePointers.add(&sizes.last_element());
            }
         }
      }


      void CCoder2::SetCoderInfo(const file_size **inSizes, const file_size **outSizes)
      {
         SetSizes(inSizes, InSizes, InSizePointers, NumInStreams);
         SetSizes(outSizes, OutSizes, OutSizePointers, NumOutStreams);
      }

      //////////////////////////////////////
      // CCoderMixer2MT

      gen::HRes CCoderMixer2MT::SetBindInfo(const CBindInfo &bindInfo)
      {
         _bindInfo = bindInfo;
         _streamBinders.remove_all();
         for (int32_t i = 0; i < _bindInfo.BindPairs.get_count(); i++)
         {
            _streamBinders.add_new();
            RINOK(_streamBinders.last_element().CreateEvents());
         }
         return S_OK;
      }

      void CCoderMixer2MT::AddCoderCommon()
      {
         const CCoderStreamsInfo &c = _bindInfo.Coders[_coders.get_count()];
         CCoder2 threadCoderInfo(get_app(), c.NumInStreams, c.NumOutStreams);
         _coders.add(threadCoderInfo);
      }

      void CCoderMixer2MT::AddCoder(::libcompress::coder_interface *coder)
      {
         AddCoderCommon();
         _coders.last_element().Coder = coder;
      }

      void CCoderMixer2MT::AddCoder2(::libcompress::coder2_interface *coder)
      {
         AddCoderCommon();
         _coders.last_element().Coder2 = coder;
      }


      void CCoderMixer2MT::ReInit()
      {
         for (int32_t i = 0; i < _streamBinders.get_count(); i++)
            _streamBinders[i].ReInit();
      }

      CCoderMixer2MT::CCoderMixer2MT(::ca::application * papp) :
         ca(papp),
         _streamBinders(papp)
      {
      }

      HRESULT CCoderMixer2MT::Init(::gen::reader **inStreams, gen::writer **outStreams)
      {
         /*
         if (_coders.get_count() != _bindInfo.Coders.get_count())
         throw 0;
         */
         int32_t i;
         for (i = 0; i < _coders.get_count(); i++)
         {
            CCoder2 &coderInfo = _coders[i];
            const CCoderStreamsInfo &coderStreamsInfo = _bindInfo.Coders[i];
            coderInfo.InStreams.remove_all();
            uint32_t j;
            for (j = 0; j < coderStreamsInfo.NumInStreams; j++)
               coderInfo.InStreams.add_new();
            coderInfo.OutStreams.remove_all();
            for (j = 0; j < coderStreamsInfo.NumOutStreams; j++)
               coderInfo.OutStreams.add_new();
         }

         for (i = 0; i < _bindInfo.BindPairs.get_count(); i++)
         {
            const CBindPair &bindPair = _bindInfo.BindPairs[i];
            uint32_t inCoderIndex, inCoderStreamIndex;
            uint32_t outCoderIndex, outCoderStreamIndex;
            _bindInfo.FindInStream(bindPair.InIndex, inCoderIndex, inCoderStreamIndex);
            _bindInfo.FindOutStream(bindPair.OutIndex, outCoderIndex, outCoderStreamIndex);

            _streamBinders[i].CreateStreams(
               &_coders[inCoderIndex].InStreams[inCoderStreamIndex].m_p,
               &_coders[outCoderIndex].OutStreams[outCoderStreamIndex].m_p);

            throw "implement below";
            /*::ca::smart_pointer<::libcompress::set_buffer_size_interface> inSetSize, outSetSize;
            inSetSize = dynamic_cast < ::libcompress::set_buffer_size_interface * > (_coders[inCoderIndex].m_p);
            outSetSize = dynamic_cast < ::libcompress::set_buffer_size_interface * > (_coders[outCoderIndex].m_p);
            if (inSetSize && outSetSize)
            {
               const uint32_t kBufSize = 1 << 19;
               inSetSize->SetInBufSize(inCoderStreamIndex, kBufSize);
               outSetSize->SetOutBufSize(outCoderStreamIndex, kBufSize);
            }*/
         }

         for (i = 0; i < _bindInfo.InStreams.get_count(); i++)
         {
            uint32_t inCoderIndex, inCoderStreamIndex;
            _bindInfo.FindInStream(_bindInfo.InStreams[i], inCoderIndex, inCoderStreamIndex);
            _coders[inCoderIndex].InStreams[inCoderStreamIndex] = inStreams[i];
         }

         for (i = 0; i < _bindInfo.OutStreams.get_count(); i++)
         {
            uint32_t outCoderIndex, outCoderStreamIndex;
            _bindInfo.FindOutStream(_bindInfo.OutStreams[i], outCoderIndex, outCoderStreamIndex);
            _coders[outCoderIndex].OutStreams[outCoderStreamIndex] = outStreams[i];
         }
         return S_OK;
      }

      HRESULT CCoderMixer2MT::ReturnIfError(HRESULT code)
      {
         for (int32_t i = 0; i < _coders.get_count(); i++)
            if (_coders[i].Result == code)
               return code;
         return S_OK;
      }

      gen::HRes CCoderMixer2MT::Code(::gen::reader **inStreams,
         const file_size ** /* inSizes */,
         uint32_t numInStreams,
         ::gen::writer **outStreams,
         const file_size ** /* outSizes */,
         uint32_t numOutStreams,
         ::libcompress::progress_info_interface *progress)
      {
         if (numInStreams != (uint32_t)_bindInfo.InStreams.get_count() ||
            numOutStreams != (uint32_t)_bindInfo.OutStreams.get_count())
            return E_INVALIDARG;

         Init(inStreams, outStreams);

         int32_t i;
         for (i = 0; i < _coders.get_count(); i++)
            if (i != _progressCoderIndex)
            {
//               RINOK(_coders[i].Create());
            }

            for (i = 0; i < _coders.get_count(); i++)
               if (i != _progressCoderIndex)
                  _coders[i].begin();

            _coders[_progressCoderIndex].Code(progress);

            throw "should implement below";
            /*
            for (i = 0; i < _coders.get_count(); i++)
               if (i != _progressCoderIndex)
                  _coders[i].WaitFinish();
                  */
            RINOK(ReturnIfError(E_ABORT));
            RINOK(ReturnIfError(E_OUTOFMEMORY));

            for (i = 0; i < _coders.get_count(); i++)
            {
               HRESULT result = _coders[i].Result;
               if (result != S_OK && result != E_FAIL && result != S_FALSE)
                  return result;
            }

            RINOK(ReturnIfError(S_FALSE));

            for (i = 0; i < _coders.get_count(); i++)
            {
               HRESULT result = _coders[i].Result;
               if (result != S_OK)
                  return result;
            }
            return S_OK;
      }

   } // namespace coder_mixer

} // namespace libcompress
