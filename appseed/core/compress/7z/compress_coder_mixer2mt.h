// CoderMixer2MT.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{
   namespace coder_mixer
   {
      struct CCoder2: public CCoderInfo2, public ::ca::thread
      {
         HRESULT Result;
         array < sp(::ca::reader) > InStreams;
         array < sp(::ca::writer) > OutStreams;
         array < ::ca::reader * > InStreamPointers;
         array < ::ca::writer * > OutStreamPointers;

         CCoder2(::ca::base::application * papp, uint32 numInStreams, uint32 numOutStreams);
         void SetCoderInfo(const file_size **inSizes, const file_size **outSizes);
         virtual int32_t run();
         void Code(progress_info_interface *progress);
      };


      /*
      SetBindInfo()
      for each coder
      AddCoder[2]()
      SetProgressIndex(uint32 coderIndex);

      for each file
      {
      ReInit()
      for each coder
      SetCoderInfo
      Code
      }
      */

      class CCoderMixer2MT:
         public ::libcompress::coder2_interface,
         public CCoderMixer2
      {
         CBindInfo _bindInfo;
         array < ::ca::stream_binder > _streamBinders;
         int32_t _progressCoderIndex;

         void AddCoderCommon();
         HRESULT Init(::ca::reader **inStreams, ::ca::writer **outStreams);
         HRESULT ReturnIfError(HRESULT code);
      public:
         array_app_alloc<CCoder2> _coders;

         ::ca::HRes Code(::ca::reader **inStreams,
            const file_size **inSizes,
            uint32 numInStreams,
            ::ca::writer **outStreams,
            const file_size **outSizes,
            uint32 numOutStreams,
            progress_info_interface *progress);

         ::ca::HRes SetBindInfo(const CBindInfo &bindInfo);
         void AddCoder(::libcompress::coder_interface *coder);
         void AddCoder2(::libcompress::coder2_interface *coder);
         void SetProgressCoderIndex(int32_t coderIndex) {  _progressCoderIndex = coderIndex; }

         void ReInit();
         void SetCoderInfo(uint32 coderIndex, const file_size **inSizes, const file_size **outSizes)
         {  _coders[coderIndex].SetCoderInfo(inSizes, outSizes); }
         uint64 GetWriteProcessedSize(uint32 binderIndex) const
         {  return _streamBinders[binderIndex].ProcessedSize; }
      };

   } // namespace coder_mixer

} // namespace libcompress


