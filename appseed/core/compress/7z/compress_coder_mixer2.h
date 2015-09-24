// CoderMixer2.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{
   namespace coder_mixer
   {

      struct CBindPair
      {
         uint32 InIndex;
         uint32 OutIndex;
      };

      struct CCoderStreamsInfo
      {
         uint32 NumInStreams;
         uint32 NumOutStreams;
      };

      struct CBindInfo
      {
         array<CCoderStreamsInfo> Coders;
         array<CBindPair> BindPairs;
         array<uint32> InStreams;
         array<uint32> OutStreams;

         void remove_all()
         {
            Coders.remove_all();
            BindPairs.remove_all();
            InStreams.remove_all();
            OutStreams.remove_all();
         }

         /*
         uint32 GetCoderStartOutStream(uint32 coderIndex) const
         {
         uint32 numOutStreams = 0;
         for (uint32 i = 0; i < coderIndex; i++)
         numOutStreams += Coders[i].NumOutStreams;
         return numOutStreams;
         }
         */


         void GetNumStreams(uint32 &numInStreams, uint32 &numOutStreams) const
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

         int32_t FindBinderForInStream(uint32 inStream) const
         {
            for (int32_t i = 0; i < BindPairs.get_count(); i++)
               if (BindPairs[i].InIndex == inStream)
                  return i;
            return -1;
         }
         int32_t FindBinderForOutStream(uint32 outStream) const
         {
            for (int32_t i = 0; i < BindPairs.get_count(); i++)
               if (BindPairs[i].OutIndex == outStream)
                  return i;
            return -1;
         }

         uint32 GetCoderInStreamIndex(uint32 coderIndex) const
         {
            uint32 streamIndex = 0;
            for (uint32 i = 0; i < coderIndex; i++)
               streamIndex += Coders[i].NumInStreams;
            return streamIndex;
         }

         uint32 GetCoderOutStreamIndex(uint32 coderIndex) const
         {
            uint32 streamIndex = 0;
            for (uint32 i = 0; i < coderIndex; i++)
               streamIndex += Coders[i].NumOutStreams;
            return streamIndex;
         }


         void FindInStream(uint32 streamIndex, uint32 &coderIndex,
            uint32 &coderStreamIndex) const
         {
            for (coderIndex = 0; coderIndex < (uint32)Coders.get_count(); coderIndex++)
            {
               uint32 curSize = Coders[coderIndex].NumInStreams;
               if (streamIndex < curSize)
               {
                  coderStreamIndex = streamIndex;
                  return;
               }
               streamIndex -= curSize;
            }
            throw 1;
         }
         void FindOutStream(uint32 streamIndex, uint32 &coderIndex,
            uint32 &coderStreamIndex) const
         {
            for (coderIndex = 0; coderIndex < (uint32)Coders.get_count(); coderIndex++)
            {
               uint32 curSize = Coders[coderIndex].NumOutStreams;
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
         uint32 _numSrcOutStreams;
         ::libcompress::coder_mixer::CBindInfo _srcBindInfo;
         array<uint32> _srcInToDestOutMap;
         array<uint32> _srcOutToDestInMap;
         array<uint32> _destInToSrcOutMap;
      public:
         uint32 NumSrcInStreams;
         array<uint32> DestOutToSrcInMap;

         CBindReverseConverter(const ::libcompress::coder_mixer::CBindInfo &srcBindInfo);
         void CreateReverseBindInfo(::libcompress::coder_mixer::CBindInfo &destBindInfo);
      };

      struct CCoderInfo2
      {
         sp(::libcompress::coder_interface) Coder;
         sp(::libcompress::coder2_interface) Coder2;
         uint32 NumInStreams;
         uint32 NumOutStreams;

         array<file_size_t> InSizes;
         array<file_size_t> OutSizes;
         array<const file_size_t *> InSizePointers;
         array<const file_size_t *> OutSizePointers;

         CCoderInfo2(uint32 numInStreams, uint32 numOutStreams);
         void SetCoderInfo(const file_size_t **inSizes, const file_size_t **outSizes);

      };

      class CCoderMixer2
      {
      public:
         virtual ::ca::HRes SetBindInfo(const CBindInfo &bindInfo) = 0;
         virtual void ReInit() = 0;
         virtual void SetCoderInfo(uint32 coderIndex, const file_size_t **inSizes, const file_size_t **outSizes) = 0;
      };

   } // namespace coder_mixer

} // namespace libcompress


