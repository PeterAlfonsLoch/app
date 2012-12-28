// CoderMixer2MT.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace compress
{
   namespace coder_mixer
   {
      struct CCoder2: public CCoderInfo2, public ::radix::thread
      {
         HRESULT Result;
         base_array < sp(::ex1::reader) > InStreams;
         base_array < sp(::ex1::writer) > OutStreams;
         base_array < ::ex1::reader * > InStreamPointers;
         base_array < ::ex1::writer * > OutStreamPointers;

         CCoder2(::ca::application * papp, uint32 numInStreams, uint32 numOutStreams);
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
         virtual public ::compress::coder2_interface,
         virtual public CCoderMixer2
      {
         CBindInfo _bindInfo;
         array_app_alloc < ::ex1::stream_binder > _streamBinders;
         int32_t _progressCoderIndex;

         void AddCoderCommon();
         HRESULT Init(::ex1::reader **inStreams, ::ex1::writer **outStreams);
         HRESULT ReturnIfError(HRESULT code);
      public:
         array_app_alloc<CCoder2> _coders;


         CCoderMixer2MT(::ca::application * papp);

         ex1::HRes Code(::ex1::reader **inStreams,
            const file_size **inSizes,
            uint32 numInStreams,
            ::ex1::writer **outStreams,
            const file_size **outSizes,
            uint32 numOutStreams,
            progress_info_interface *progress);

         ex1::HRes SetBindInfo(const CBindInfo &bindInfo);
         void AddCoder(::compress::coder_interface *coder);
         void AddCoder2(::compress::coder2_interface *coder);
         void SetProgressCoderIndex(int32_t coderIndex) {  _progressCoderIndex = coderIndex; }

         void ReInit();
         void SetCoderInfo(uint32 coderIndex, const file_size **inSizes, const file_size **outSizes)
         {  _coders[coderIndex].SetCoderInfo(inSizes, outSizes); }
         uint64 GetWriteProcessedSize(uint32 binderIndex) const
         {  return _streamBinders[binderIndex].ProcessedSize; }
      };

   } // namespace coder_mixer

} // namespace compress


