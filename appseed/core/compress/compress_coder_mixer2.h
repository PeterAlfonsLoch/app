// CoderMixer2.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{
   namespace coder_mixer
   {

      struct CBindPair
      {
         uint32_t InIndex;
         uint32_t OutIndex;
      };

      struct CCoderStreamsInfo
      {
         uint32_t NumInStreams;
         uint32_t NumOutStreams;
      };

      struct CBindInfo
      {
         array<CCoderStreamsInfo> Coders;
         array<CBindPair> BindPairs;
         array<uint32_t> InStreams;
         array<uint32_t> OutStreams;

         void remove_all()
         {
            Coders.remove_all();
            BindPairs.remove_all();
            InStreams.remove_all();
            OutStreams.remove_all();
         }

         /*
         uint32_t GetCoderStartOutStream(uint32_t coderIndex) const
         {
         uint32_t numOutStreams = 0;
         for (uint32_t i = 0; i < coderIndex; i++)
         numOutStreams += Coders[i].NumOutStreams;
         return numOutStreams;
         }
         */


         void GetNumStreams(uint32_t &numInStreams, uint32_t &numOutStreams) const
         {
            numInStreams = 0;
            numOutStreams = 0;
            for (int32_t i = 0; i < Coders.get_count(); i++)
            {
               const CCoderStreamsInfo &coderStreamsInfo = Coders[i];
               numInStreams += coderStreamsInfo.NumInStreams;
               numOutStreams += coderStreamsInfo.NumOutStreams;
            }
         }

         int32_t FindBinderForInStream(uint32_t inStream) const
         {
            for (int32_t i = 0; i < BindPairs.get_count(); i++)
               if (BindPairs[i].InIndex == inStream)
                  return i;
            return -1;
         }
         int32_t FindBinderForOutStream(uint32_t outStream) const
         {
            for (int32_t i = 0; i < BindPairs.get_count(); i++)
               if (BindPairs[i].OutIndex == outStream)
                  return i;
            return -1;
         }

         uint32_t GetCoderInStreamIndex(uint32_t coderIndex) const
         {
            uint32_t streamIndex = 0;
            for (uint32_t i = 0; i < coderIndex; i++)
               streamIndex += Coders[i].NumInStreams;
            return streamIndex;
         }

         uint32_t GetCoderOutStreamIndex(uint32_t coderIndex) const
         {
            uint32_t streamIndex = 0;
            for (uint32_t i = 0; i < coderIndex; i++)
               streamIndex += Coders[i].NumOutStreams;
            return streamIndex;
         }


         void FindInStream(uint32_t streamIndex, uint32_t &coderIndex,
            uint32_t &coderStreamIndex) const
         {
            for (coderIndex = 0; coderIndex < (uint32_t)Coders.get_count(); coderIndex++)
            {
               uint32_t curSize = Coders[coderIndex].NumInStreams;
               if (streamIndex < curSize)
               {
                  coderStreamIndex = streamIndex;
                  return;
               }
               streamIndex -= curSize;
            }
            throw 1;
         }
         void FindOutStream(uint32_t streamIndex, uint32_t &coderIndex,
            uint32_t &coderStreamIndex) const
         {
            for (coderIndex = 0; coderIndex < (uint32_t)Coders.get_count(); coderIndex++)
            {
               uint32_t curSize = Coders[coderIndex].NumOutStreams;
               if (streamIndex < curSize)
               {
                  coderStreamIndex = streamIndex;
                  return;
               }
               streamIndex -= curSize;
            }
            throw 1;
         }
      };

      class CBindReverseConverter
      {
         uint32_t _numSrcOutStreams;
         ::libcompress::coder_mixer::CBindInfo _srcBindInfo;
         array<uint32_t> _srcInToDestOutMap;
         array<uint32_t> _srcOutToDestInMap;
         array<uint32_t> _destInToSrcOutMap;
      public:
         uint32_t NumSrcInStreams;
         array<uint32_t> DestOutToSrcInMap;

         CBindReverseConverter(const ::libcompress::coder_mixer::CBindInfo &srcBindInfo);
         void CreateReverseBindInfo(::libcompress::coder_mixer::CBindInfo &destBindInfo);
      };

      struct CCoderInfo2
      {
         sp(::libcompress::coder_interface) Coder;
         sp(::libcompress::coder2_interface) Coder2;
         uint32_t NumInStreams;
         uint32_t NumOutStreams;

         array<file_size_t> InSizes;
         array<file_size_t> OutSizes;
         array<const file_size_t *> InSizePointers;
         array<const file_size_t *> OutSizePointers;

         CCoderInfo2(uint32_t numInStreams, uint32_t numOutStreams);
         void SetCoderInfo(const file_size_t **inSizes, const file_size_t **outSizes);

      };

      class CCoderMixer2
      {
      public:
         virtual HRes SetBindInfo(const CBindInfo &bindInfo) = 0;
         virtual void ReInit() = 0;
         virtual void SetCoderInfo(uint32_t coderIndex, const file_size_t **inSizes, const file_size_t **outSizes) = 0;
      };

   } // namespace coder_mixer

} // namespace libcompress


