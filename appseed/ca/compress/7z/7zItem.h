// 7zItem.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace n7z
{

   const uint64 k_AES = 0x06F10701;

   typedef uint32 CNum;
   const CNum kNumMax     = 0x7FFFFFFF;
   const CNum kNumNoIndex = 0xFFFFFFFF;

   struct CCoderInfo
   {
      ::compress::method_id MethodID;
      ::ex1::byte_buffer Props;
      CNum NumInStreams;
      CNum NumOutStreams;
      bool IsSimpleCoder() const { return (NumInStreams == 1) && (NumOutStreams == 1); }
   };

   struct CBindPair
   {
      CNum InIndex;
      CNum OutIndex;
   };

   struct CFolder
   {
      array_ptr_alloc<CCoderInfo> Coders;
      base_array<CBindPair> BindPairs;
      base_array<CNum> PackStreams;
      base_array<file_size> UnpackSizes;
      uint32 UnpackCRC;
      bool UnpackCRCDefined;

      CFolder(): UnpackCRCDefined(false) {}

      file_size GetUnpackSize() const // test it
      {
         if (UnpackSizes.is_empty())
            return 0;
         for (index i = UnpackSizes.get_count() - 1; i >= 0; i--)
            if (FindBindPairForOutStream((::n7z::CNum) i) < 0)
               return UnpackSizes[i];
         throw 1;
      }

      CNum GetNumOutStreams() const
      {
         CNum result = 0;
         for (index i = 0; i < Coders.get_count(); i++)
            result += Coders[i].NumOutStreams;
         return result;
      }

      int FindBindPairForInStream(CNum inStreamIndex) const
      {
         for(int i = 0; i < BindPairs.get_count(); i++)
            if (BindPairs[i].InIndex == inStreamIndex)
               return i;
         return -1;
      }
      int FindBindPairForOutStream(CNum outStreamIndex) const
      {
         for(int i = 0; i < BindPairs.get_count(); i++)
            if (BindPairs[i].OutIndex == outStreamIndex)
               return i;
         return -1;
      }
      int FindPackStreamArrayIndex(CNum inStreamIndex) const
      {
         for(int i = 0; i < PackStreams.get_count(); i++)
            if (PackStreams[i] == inStreamIndex)
               return i;
         return -1;
      }

      bool IsEncrypted() const
      {
         for (index i = Coders.get_count() - 1; i >= 0; i--)
            if (Coders[i].MethodID == k_AES)
               return true;
         return false;
      }

      bool CheckStructure() const;
   };

   struct CUInt64DefVector
   {
      uint64_array   Values;
      bool_array     Defined;

      void remove_all()
      {
         Values.remove_all();
         Defined.remove_all();
      }

      void free_extra()
      {
         Values.free_extra();
         Values.free_extra();
      }

      bool GetItem(int index, uint64 &value) const
      {
         if (index < Defined.get_count() && Defined[index])
         {
            value = Values[index];
            return true;
         }
         value = 0;
         return false;
      }

      void SetItem(int index, bool defined, uint64 value)
      {
         while (index >= Defined.get_count())
            Defined.add(false);
         Defined[index] = defined;
         if (!defined)
            return;
         while (index >= Values.get_count())
            Values.add(0);
         Values[index] = value;
      }

      bool CheckSize(int size) const { return Defined.get_count() == size || Defined.get_count() == 0; }
   };

   struct CFileItem
   {
      file_size get_count;
      uint32 Attrib;
      uint32 Crc;
      string Name;

      bool HasStream; // Test it !!! it means that there is
      // stream in some folder. It can be empty stream
      bool IsDir;
      bool CrcDefined;
      bool AttribDefined;

      CFileItem():
      HasStream(true),
         IsDir(false),
         CrcDefined(false),
         AttribDefined(false)
      {}
      void SetAttrib(uint32 attrib)
      {
         AttribDefined = true;
         Attrib = attrib;
      }
   };

   struct CFileItem2
   {
      uint64 CTime;
      uint64 ATime;
      uint64 MTime;
      uint64 StartPos;
      bool CTimeDefined;
      bool ATimeDefined;
      bool MTimeDefined;
      bool StartPosDefined;
      bool IsAnti;
   };

   struct CArchiveDatabase
   {
      base_array<file_size> PackSizes;
      bool_array PackCRCsDefined;
      base_array<uint32> PackCRCs;
      array_ptr_alloc<CFolder> Folders;
      base_array<CNum> NumUnpackStreamsVector;
      array_ptr_alloc<CFileItem> Files;

      CUInt64DefVector CTime;
      CUInt64DefVector ATime;
      CUInt64DefVector MTime;
      CUInt64DefVector StartPos;
      bool_array IsAnti;

      void clear()
      {
         PackSizes.remove_all();
         PackCRCsDefined.remove_all();
         PackCRCs.remove_all();
         Folders.remove_all();
         NumUnpackStreamsVector.remove_all();
         Files.remove_all();
         CTime.remove_all();
         ATime.remove_all();
         MTime.remove_all();
         StartPos.remove_all();
         IsAnti.remove_all();
      }

      void free_extra()
      {
         PackSizes.free_extra();
         PackCRCsDefined.free_extra();
         PackCRCs.free_extra();
         NumUnpackStreamsVector.free_extra();
         CTime.free_extra();
         ATime.free_extra();
         MTime.free_extra();
         StartPos.free_extra();
         IsAnti.free_extra();
      }

      bool is_empty() const
      {
         return (PackSizes.is_empty() &&
            PackCRCsDefined.is_empty() &&
            PackCRCs.is_empty() &&
            Folders.is_empty() &&
            NumUnpackStreamsVector.is_empty() &&
            Files.is_empty());
      }

      bool CheckNumFiles() const
      {
         count size = Files.get_count();
         return (
            CTime.CheckSize((int) size) &&
            ATime.CheckSize((int) size) &&
            MTime.CheckSize((int) size) &&
            StartPos.CheckSize((int) size) &&
            (size == IsAnti.get_count() || IsAnti.get_count() == 0));
      }

      bool IsSolid() const
      {
         for (int i = 0; i < NumUnpackStreamsVector.get_count(); i++)
            if (NumUnpackStreamsVector[i] > 1)
               return true;
         return false;
      }
      bool IsItemAnti(int index) const { return (index < IsAnti.get_count() && IsAnti[index]); }
      void SetItemAnti(int index, bool isAnti)
      {
         while (index >= IsAnti.get_count())
            IsAnti.add(false);
         IsAnti[index] = isAnti;
      }

      void GetFile(int index, CFileItem &file, CFileItem2 &file2) const;
      void AddFile(const CFileItem &file, const CFileItem2 &file2);
   };

} // namespace n7z

