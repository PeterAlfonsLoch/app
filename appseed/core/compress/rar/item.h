// RarItem.h

#pragma once

namespace rar
{

   struct CRarTime
   {
      uint32_t DosTime;
      byte LowSecond;
      byte SubTime[3];
   };

   struct CItem
   {
      file_size_t Size;
      file_size_t PackSize;

      CRarTime CTime;
      CRarTime ATime;
      CRarTime MTime;

      uint32_t FileCRC;
      uint32_t Attrib;

      uint16_t Flags;
      byte HostOS;
      byte UnPackVersion;
      byte Method;

      bool CTimeDefined;
      bool ATimeDefined;

      string Name;

      byte Salt[8];

      bool IsEncrypted()   const { return (Flags & header::file::kEncrypted) != 0; }
      bool IsSolid()       const { return (Flags & header::file::kSolid) != 0; }
      bool IsCommented()   const { return (Flags & header::file::kComment) != 0; }
      bool IsSplitBefore() const { return (Flags & header::file::kSplitBefore) != 0; }
      bool IsSplitAfter()  const { return (Flags & header::file::kSplitAfter) != 0; }
      bool HasSalt()       const { return (Flags & header::file::kSalt) != 0; }
      bool HasExtTime()    const { return (Flags & header::file::kExtTime) != 0; }
      bool HasUnicodeName()const { return (Flags & header::file::kUnicodeName) != 0; }
      bool IsOldVersion()  const { return (Flags & header::file::kOldVersion) != 0; }

      uint32_t GetDictSize() const { return (Flags >> header::file::kDictBitStart) & header::file::kDictMask; }
      bool IsDir() const;
      bool IgnoreItem() const;
      uint32_t GetWinAttributes() const;

      CItem(): CTimeDefined(false), ATimeDefined(false) {}
   };

   class CItemEx: public CItem
   {
   public:
      uint64_t Position;
      uint16_t MainPartSize;
      uint16_t CommentSize;
      uint16_t AlignSize;
      uint64_t GetFullSize()  const { return MainPartSize + CommentSize + AlignSize + PackSize; };
      //  uint32_t GetHeaderWithCommentSize()  const { return MainPartSize + CommentSize; };
      uint64_t GetCommentPosition() const { return Position + MainPartSize; };
      uint64_t GetDataPosition()    const { return GetCommentPosition() + CommentSize + AlignSize; };
   };

} // namespace rar
