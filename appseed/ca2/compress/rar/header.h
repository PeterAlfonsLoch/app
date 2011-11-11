// Archive/RarHeader.h
// from 7-zip

namespace rar
{
   namespace header
   {

      const int kMarkerSize = 7;
      extern byte kMarker[kMarkerSize];

      const int kArchiveSolid = 0x1;

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

         const int kHeaderSizeMin = 7;

         const int kArchiveHeaderSize = 13;

         const int kBlockHeadersAreEncrypted = 0x80;

      }

      namespace file
      {
         const int kSplitBefore = 1 << 0;
         const int kSplitAfter  = 1 << 1;
         const int kEncrypted   = 1 << 2;
         const int kComment     = 1 << 3;
         const int kSolid       = 1 << 4;

         const int kDictBitStart     = 5;
         const int kNumDictBits  = 3;
         const int kDictMask         = (1 << kNumDictBits) - 1;
         const int kDictDirectoryValue  = 0x7;

         const int kSize64Bits    = 1 << 8;
         const int kUnicodeName   = 1 << 9;
         const int kSalt          = 1 << 10;
         const int kOldVersion    = 1 << 11;
         const int kExtTime       = 1 << 12;
         // const int kExtFlags      = 1 << 13;
         // const int kSkipIfUnknown = 1 << 14;

         const int kLongBlock    = 1 << 15;

         /*
         struct CBlock
         {
         // uint16_t HeadCRC;
         // byte Type;
         // uint16_t Flags;
         // uint16_t HeadSize;
         uint32 PackSize;
         uint32 UnPackSize;
         byte HostOS;
         uint32 FileCRC;
         uint32 Time;
         byte UnPackVersion;
         byte Method;
         uint16_t NameSize;
         uint32 Attributes;
         };
         */

         /*
         struct CBlock32
         {
         uint16_t HeadCRC;
         byte Type;
         uint16_t Flags;
         uint16_t HeadSize;
         uint32 PackSize;
         uint32 UnPackSize;
         byte HostOS;
         uint32 FileCRC;
         uint32 Time;
         byte UnPackVersion;
         byte Method;
         uint16_t NameSize;
         uint32 Attributes;
         uint16_t GetRealCRC(const void *aName, uint32 aNameSize,
         bool anExtraDataDefined = false, byte *anExtraData = 0) const;
         };
         struct CBlock64
         {
         uint16_t HeadCRC;
         byte Type;
         uint16_t Flags;
         uint16_t HeadSize;
         uint32 PackSizeLow;
         uint32 UnPackSizeLow;
         byte HostOS;
         uint32 FileCRC;
         uint32 Time;
         byte UnPackVersion;
         byte Method;
         uint16_t NameSize;
         uint32 Attributes;
         uint32 PackSizeHigh;
         uint32 UnPackSizeHigh;
         uint16_t GetRealCRC(const void *aName, uint32 aNameSize) const;
         };
         */

         const int kLabelFileAttribute            = 0x08;
         const int kWinFileDirectoryAttributeMask = 0x10;

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
            //  uint32 DataSize;
         };
      }

      /*
      struct CSubBlock
      {
      uint16_t HeadCRC;
      byte HeadType;
      uint16_t Flags;
      uint16_t HeadSize;
      uint32 DataSize;
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
      uint32 DataSize;
      byte Version;
      uint16_t RecSectors;
      uint32 TotalBlocks;
      byte Mark[8];
      };
      */

   } // namespace header

} // namespace rar
