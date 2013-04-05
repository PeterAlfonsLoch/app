// CoderMixer2MT.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once


namespace libcompress
{


   namespace coder_mixer
   {


      struct CCoder2: public CCoderInfo2, public ::ca::thread
      {


         HRESULT                          Result;
         spa(::ca::reader)                InStreams;
         spa(::ca::writer)                OutStreams;
         spa(::ca::reader)                InStreamPointers;
         spa(::ca::writer)                OutStreamPointers;

         CCoder2(::ca::applicationsp papp, uint32_t numInStreams, uint32_t numOutStreams);
         void SetCoderInfo(const file_size **inSizes, const file_size **outSizes);
         virtual int32_t run();
         void Code(progress_info_interface *progress);
      };


      /*
      SetBindInfo()
      for each coder
      AddCoder[2]()
      SetProgressIndex(uint32_t coderIndex);

      for each file
      {
      ReInit()
      for each coder
      SetCoderInfo
      Code
      }
      */

      class CCoderMixer2MT:
         virtual public ::libcompress::coder2_interface,
         virtual public CCoderMixer2
      {
         CBindInfo _bindInfo;
         spa(::ca::stream_binder) _streamBinders;
         int32_t _progressCoderIndex;

         void AddCoderCommon();
         HRESULT Init(spa(::ca::reader) & inStreams, spa(::ca::writer) & outStreams);
         HRESULT ReturnIfError(HRESULT code);
      public:
         spa(CCoder2) _coders;


         CCoderMixer2MT(::ca::applicationsp papp);

         ::ca::HRes Code(spa(::ca::reader) & inStreams,
            const file_size **inSizes,
            spa(::ca::writer) & outStreams,
            const file_size **outSizes,
            progress_info_interface *progress);

         ::ca::HRes SetBindInfo(const CBindInfo &bindInfo);
         void AddCoder(::libcompress::coder_interface *coder);
         void AddCoder2(::libcompress::coder2_interface *coder);
         void SetProgressCoderIndex(int32_t coderIndex) {  _progressCoderIndex = coderIndex; }

         void ReInit();
         void SetCoderInfo(uint32_t coderIndex, const file_size **inSizes, const file_size **outSizes)
         {  _coders[coderIndex].SetCoderInfo(inSizes, outSizes); }
         uint64_t GetWriteProcessedSize(uint32_t binderIndex) const
         {  return _streamBinders[binderIndex].ProcessedSize; }
      };

   } // namespace coder_mixer

} // namespace libcompress


