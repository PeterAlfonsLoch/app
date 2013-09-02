// Archive/RarHeader.h
// from 7-zip

namespace rar
{
   namespace header
   {

      const int32_t kMarkerSize = 7;
      extern byte kMarker[kMarkerSize];

      const int32_t kArchiveSolid = 0x1;

      namespace block_type
      {
         enum e_block_type
         {
            kMarker = 0x72,
            kArchiveHeader,
            kFileHeader,
            kCommentHeader,
            kOldAuthenticity,
            kOldSubBlock,
            kRecoveryRecord,
            kAuthenticity,
            kSubBlock,
            kEndOfArchive
         };
      }

      namespace archive
      {
         const uint16_t kVolume  = 1;
         const uint16_t kComment = 2;
         const uint16_t kLock    = 4;
         const uint16_t kSolid   = 8;
         const uint16_t kNewVolName = 0x10; // ('volname.partN.rar')
         const uint16_t kAuthenticity  = 0x20;
         const uint16_t kRecovery = 0x40;
         const uint16_t kBlockEncryption  = 0x80;
         const uint16_t kFirstVolume = 0x100; // (set only by RAR 3.0 and later)
         const uint16_t kEncryptVer = 0x200; // RAR 3.6 there is EncryptVer byte in End of MainHeader

         const int32_t kHeaderSizeMin = 7;

         const int32_t kArchiveHeaderSize = 13;

         const int32_t kBlockHeadersAreEncrypted = 0x80;

      }

      namespace file
      {
         const int32_t kSplitBefore = 1 << 0;
         const int32_t kSplitAfter  = 1 << 1;
         const int32_t kEncrypted   = 1 << 2;
         const int32_t kComment     = 1 << 3;
         const int32_t kSolid       = 1 << 4;

         const int32_t kDictBitStart     = 5;
         const int32_t kNumDictBits  = 3;
         const int32_t kDictMask         = (1 << kNumDictBits) - 1;
         const int32_t kDictDirectoryValue  = 0x7;

         const int32_t kSize64Bits    = 1 << 8;
         const int32_t kUnicodeName   = 1 << 9;
         const int32_t kSalt          = 1 << 10;
         const int32_t kOldVersion    = 1 << 11;
         const int32_t kExtTime       = 1 << 12;
         // const int32_t kExtFlags      = 1 << 13;
         // const int32_t kSkipIfUnknown = 1 << 14;

         const int32_t kLongBlock    = 1 << 15;

         /*
         struct CBlock
         {
         // uint16_t HeadCRC;
         // byte Type;
         // uint16_t Flags;
         // uint16_t HeadSize;
         uint32_t PackSize;
         uint32_t UnPackSize;
         byte HostOS;
         uint32_t FileCRC;
         uint32_t Time;
         byte UnPackVersion;
         byte Method;
         uint16_t NameSize;
         uint32_t Attributes;
         };
         */

         /*
         struct CBlock32
         {
         uint16_t HeadCRC;
         byte Type;
         uint16_t Flags;
         uint16_t HeadSize;
         uint32_t PackSize;
         uint32_t UnPackSize;
         byte HostOS;
         uint32_t FileCRC;
         uint32_t Time;
         byte UnPackVersion;
         byte Method;
         uint16_t NameSize;
         uint32_t Attributes;
         uint16_t GetRealCRC(const void *aName, uint32_t aNameSize,
         bool anExtraDataDefined = false, byte *anExtraData = 0) const;
         };
         struct CBlock64
         {
         uint16_t HeadCRC;
         byte Type;
         uint16_t Flags;
         uint16_t HeadSize;
         uint32_t PackSizeLow;
         uint32_t UnPackSizeLow;
         byte HostOS;
         uint32_t FileCRC;
         uint32_t Time;
         byte UnPackVersion;
         byte Method;
         uint16_t NameSize;
         uint32_t Attributes;
         uint32_t PackSizeHigh;
         uint32_t UnPackSizeHigh;
         uint16_t GetRealCRC(const void *aName, uint32_t aNameSize) const;
         };
         */

         const int32_t kLabelFileAttribute            = 0x08;
         const int32_t kWinFileDirectoryAttributeMask = 0x10;

         enum CHostOS
         {
            kHostMSDOS = 0,
            kHostOS2   = 1,
            kHostWin32 = 2,
            kHostUnix  = 3,
            kHostMacOS = 4,
            kHostBeOS = 5
         };
      }

      namespace NBlock
      {
         const uint16_t kLongBlock = 1 << 15;
         struct CBlock
         {
            uint16_t CRC;
            byte Type;
            uint16_t Flags;
            uint16_t HeadSize;
            //  uint32_t DataSize;
         };
      }

      /*
      struct CSubBlock
      {
      uint16_t HeadCRC;
      byte HeadType;
      uint16_t Flags;
      uint16_t HeadSize;
      uint32_t DataSize;
      uint16_t SubType;
      byte Level; // Reserved : Must be 0
      };

      struct CCommentBlock
      {
      uint16_t HeadCRC;
      byte HeadType;
      uint16_t Flags;
      uint16_t HeadSize;
      uint16_t UnpSize;
      byte UnpVer;
      byte Method;
      uint16_t CommCRC;
      };


      struct CProtectHeader
      {
      uint16_t HeadCRC;
      byte HeadType;
      uint16_t Flags;
      uint16_t HeadSize;
      uint32_t DataSize;
      byte Version;
      uint16_t RecSectors;
      uint32_t TotalBlocks;
      byte Mark[8];
      };
      */

   } // namespace header

} // namespace rar
