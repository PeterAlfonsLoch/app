// RarItem.h

#pragma once

namespace rar
{

   struct CRarTime
   {
      uint32 DosTime;
      byte LowSecond;
      byte SubTime[3];
   };

   struct CItem
   {
      uint64 Size;
      uint64 PackSize;

      CRarTime CTime;
      CRarTime ATime;
      CRarTime MTime;

      uint32 FileCRC;
      uint32 Attrib;

      uint16 Flags;
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

      uint32 GetDictSize() const { return (Flags >> header::file::kDictBitStart) & header::file::kDictMask; }
      bool IsDir() const;
      bool IgnoreItem() const;
      uint32 GetWinAttributes() const;

      CItem(): CTimeDefined(false), ATimeDefined(false) {}
   };

   class CItemEx: public CItem
   {
   public:
      uint64 Position;
      uint16 MainPartSize;
      uint16 CommentSize;
      uint16 AlignSize;
      uint64 GetFullSize()  const { return MainPartSize + CommentSize + AlignSize + PackSize; };
      //  DWORD GetHeaderWithCommentSize()  const { return MainPartSize + CommentSize; };
      uint64 GetCommentPosition() const { return Position + MainPartSize; };
      uint64 GetDataPosition()    const { return GetCommentPosition() + CommentSize + AlignSize; };
   };

} // namespace rar
