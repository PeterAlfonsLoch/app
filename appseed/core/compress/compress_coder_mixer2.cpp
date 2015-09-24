// CoderMixer2.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"


namespace libcompress
{

   namespace coder_mixer
   {

      CBindReverseConverter::CBindReverseConverter(const CBindInfo &srcBindInfo):
         _srcBindInfo(srcBindInfo)
      {
         srcBindInfo.GetNumStreams(NumSrcInStreams, _numSrcOutStreams);

         uint32_t  j;
         for (j = 0; j < NumSrcInStreams; j++)
         {
            _srcInToDestOutMap.add(0);
            DestOutToSrcInMap.add(0);
         }
         for (j = 0; j < _numSrcOutStreams; j++)
         {
            _srcOutToDestInMap.add(0);
            _destInToSrcOutMap.add(0);
         }

         uint32_t destInOffset = 0;
         uint32_t destOutOffset = 0;
         uint32_t srcInOffset = NumSrcInStreams;
         uint32_t srcOutOffset = _numSrcOutStreams;

         for(index i = srcBindInfo.Coders.get_count() - 1; i >= 0; i--)
         {
            const CCoderStreamsInfo &srcCoderInfo = srcBindInfo.Coders[i];

            srcInOffset -= srcCoderInfo.NumInStreams;
            srcOutOffset -= srcCoderInfo.NumOutStreams;

            uint32_t j;
            for (j = 0; j < srcCoderInfo.NumInStreams; j++, destOutOffset++)
            {
               uint32_t index = srcInOffset + j;
               _srcInToDestOutMap[index] = destOutOffset;
               DestOutToSrcInMap[destOutOffset] = index;
            }
            for (j = 0; j < srcCoderInfo.NumOutStreams; j++, destInOffset++)
            {
               uint32_t index = srcOutOffset + j;
               _srcOutToDestInMap[index] = destInOffset;
               _destInToSrcOutMap[destInOffset] = index;
            }
         }
      }

      void CBindReverseConverter::CreateReverseBindInfo(CBindInfo &destBindInfo)
      {
         destBindInfo.Coders.remove_all();
         destBindInfo.BindPairs.remove_all();
         destBindInfo.InStreams.remove_all();
         destBindInfo.OutStreams.remove_all();

         index i;
         for (i = _srcBindInfo.Coders.get_count() - 1; i >= 0; i--)
         {
            const CCoderStreamsInfo &srcCoderInfo = _srcBindInfo.Coders[i];
            CCoderStreamsInfo destCoderInfo;
            destCoderInfo.NumInStreams = srcCoderInfo.NumOutStreams;
            destCoderInfo.NumOutStreams = srcCoderInfo.NumInStreams;
            destBindInfo.Coders.add(destCoderInfo);
         }
         for (i = _srcBindInfo.BindPairs.get_count() - 1; i >= 0; i--)
         {
            const CBindPair &srcBindPair = _srcBindInfo.BindPairs[i];
            CBindPair destBindPair;
            destBindPair.InIndex = _srcOutToDestInMap[srcBindPair.OutIndex];
            destBindPair.OutIndex = _srcInToDestOutMap[srcBindPair.InIndex];
            destBindInfo.BindPairs.add(destBindPair);
         }
         for (i = 0; i < _srcBindInfo.InStreams.get_count(); i++)
            destBindInfo.OutStreams.add(_srcInToDestOutMap[_srcBindInfo.InStreams[i]]);
         for (i = 0; i < _srcBindInfo.OutStreams.get_count(); i++)
            destBindInfo.InStreams.add(_srcOutToDestInMap[_srcBindInfo.OutStreams[i]]);
      }

      CCoderInfo2::CCoderInfo2(uint32_t numInStreams, uint32_t numOutStreams):
      NumInStreams(numInStreams),
         NumOutStreams(numOutStreams)
      {
         InSizes.allocate(0, NumInStreams);
         InSizePointers.allocate(0, NumInStreams);
         OutSizes.allocate(0, NumOutStreams);
         OutSizePointers.allocate(0, NumOutStreams);
      }

      static void SetSizes(const file_size_t **srcSizes, array<file_size_t> &sizes,
         array<const file_size_t *> &sizePointers, uint32_t numItems)
      {
         sizes.remove_all();
         sizePointers.remove_all();
         for(uint32_t i = 0; i < numItems; i++)
         {
            if (srcSizes == 0 || srcSizes[i] == NULL)
            {
               sizes.add((file_size_t) 0);
               sizePointers.add(NULL);
            }
            else
            {
               sizes.add(*srcSizes[i]);
               sizePointers.add(&sizes.last_element());
            }
         }
      }

      void CCoderInfo2::SetCoderInfo(const file_size_t **inSizes,
         const file_size_t **outSizes)
      {
         SetSizes(inSizes, InSizes, InSizePointers, NumInStreams);
         SetSizes(outSizes, OutSizes, OutSizePointers, NumOutStreams);
      }

   } // namespace coder_mixer

} // namespace libcompress
