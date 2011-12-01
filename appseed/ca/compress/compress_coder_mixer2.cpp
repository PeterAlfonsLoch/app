// CoderMixer2.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "StdAfx.h"


namespace compress
{

   namespace coder_mixer
   {

      CBindReverseConverter::CBindReverseConverter(const CBindInfo &srcBindInfo):
         _srcBindInfo(srcBindInfo)
      {
         srcBindInfo.GetNumStreams(NumSrcInStreams, _numSrcOutStreams);

         uint32  j;
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

         uint32 destInOffset = 0;
         uint32 destOutOffset = 0;
         uint32 srcInOffset = NumSrcInStreams;
         uint32 srcOutOffset = _numSrcOutStreams;

         for (int i = srcBindInfo.Coders.get_count() - 1; i >= 0; i--)
         {
            const CCoderStreamsInfo &srcCoderInfo = srcBindInfo.Coders[i];

            srcInOffset -= srcCoderInfo.NumInStreams;
            srcOutOffset -= srcCoderInfo.NumOutStreams;

            uint32 j;
            for (j = 0; j < srcCoderInfo.NumInStreams; j++, destOutOffset++)
            {
               uint32 index = srcInOffset + j;
               _srcInToDestOutMap[index] = destOutOffset;
               DestOutToSrcInMap[destOutOffset] = index;
            }
            for (j = 0; j < srcCoderInfo.NumOutStreams; j++, destInOffset++)
            {
               uint32 index = srcOutOffset + j;
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

         int i;
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

      CCoderInfo2::CCoderInfo2(uint32 numInStreams, uint32 numOutStreams):
      NumInStreams(numInStreams),
         NumOutStreams(numOutStreams)
      {
         InSizes.set_size(0, NumInStreams);
         InSizePointers.set_size(0, NumInStreams);
         OutSizes.set_size(0, NumOutStreams);
         OutSizePointers.set_size(0, NumOutStreams);
      }

      static void SetSizes(const file_size **srcSizes, base_array<file_size> &sizes,
         base_array<const file_size *> &sizePointers, uint32 numItems)
      {
         sizes.remove_all();
         sizePointers.remove_all();
         for(uint32 i = 0; i < numItems; i++)
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

      void CCoderInfo2::SetCoderInfo(const file_size **inSizes,
         const file_size **outSizes)
      {
         SetSizes(inSizes, InSizes, InSizePointers, NumInStreams);
         SetSizes(outSizes, OutSizes, OutSizePointers, NumOutStreams);
      }

   } // namespace coder_mixer

} // namespace compress
