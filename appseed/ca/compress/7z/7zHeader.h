// 7z/7zHeader.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace n7z
{

   const int kSignatureSize = 6;
   extern byte kSignature[kSignatureSize];

   // #define _7Z_VOL
   // 7z-MultiVolume is not finished yet.
   // It can work already, but I still do not like some
   // things of that new multivolume format.
   // So please keep it commented.

#ifdef _7Z_VOL
   extern byte kFinishSignature[kSignatureSize];
#endif

   struct CArchiveVersion
   {
      byte Major;
      byte Minor;
   };

   const byte kMajorVersion = 0;

   struct CStartHeader
   {
      uint64 NextHeaderOffset;
      uint64 NextHeaderSize;
      uint32 NextHeaderCRC;
   };

   const uint32 kStartHeaderSize = 20;

   struct CFinishHeader: public CStartHeader
   {
      uint64 ArchiveStartOffset;  // data offset from end if that struct
      uint64 AdditionalStartBlockSize; // start  signature & start header size
   };

   const uint32 kFinishHeaderSize = kStartHeaderSize + 16;

   namespace NID
   {
      enum EEnum
      {
         kEnd,

         kHeader,

         kArchiveProperties,

         kAdditionalStreamsInfo,
         kMainStreamsInfo,
         kFilesInfo,

         kPackInfo,
         kUnpackInfo,
         kSubStreamsInfo,

         kSize,
         kCRC,

         kFolder,

         kCodersUnpackSize,
         kNumUnpackStream,

         kEmptyStream,
         kEmptyFile,
         kAnti,

         kName,
         kCTime,
         kATime,
         kMTime,
         kWinAttributes,
         kComment,

         kEncodedHeader,

         kStartPos,
         kDummy
      };
   }

} // namespace n7z
