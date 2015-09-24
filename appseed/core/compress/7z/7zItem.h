// 7zItem.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once


namespace n7z
{

   const uint64_t k_AES = 0x06F10701;

   typedef uint32_t CNum;
   const CNum kNumMax     = 0x7FFFFFFF;
   const CNum kNumNoIndex = 0xFFFFFFFF;

   struct CCoderInfo :
      virtual public element
   {
      ::libcompress::method_id MethodID;
      ::file::byte_buffer Props;
      CNum NumInStreams;
      CNum NumOutStreams;
      bool IsSimpleCoder() const { return (NumInStreams == 1) && (NumOutStreams == 1); }
   };

   struct CBindPair
   {
      CNum InIndex;
      CNum OutIndex;
   };

   struct CFolder :
      virtual public element
   {
      spa(CCoderInfo) Coders;
      array<CBindPair> BindPairs;
      array<CNum> PackStreams;
      array<file_size_t> UnpackSizes;
      uint32_t UnpackCRC;
      bool UnpackCRCDefined;

      CFolder(): UnpackCRCDefined(false) {}

      file_size_t GetUnpackSize() const // test it
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

      int32_t FindBindPairForInStream(CNum inStreamIndex) const
      {
         for(int32_t i = 0; i < BindPairs.get_count(); i++)
            if (BindPairs[i].InIndex == inStreamIndex)
               return i;
         return -1;
      }
      int32_t FindBindPairForOutStream(CNum outStreamIndex) const
      {
         for(int32_t i = 0; i < BindPairs.get_count(); i++)
            if (BindPairs[i].OutIndex == outStreamIndex)
               return i;
         return -1;
      }
      int32_t FindPackStreamArrayIndex(CNum inStreamIndex) const
      {
         for(int32_t i = 0; i < PackStreams.get_count(); i++)
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

      bool GetItem(index index, uint64_t &value) const
      {
         if (index < Defined.get_count() && Defined[index])
         {
            value = Values[index];
            return true;
         }
         value = 0;
         return false;
      }

      void SetItem(index index, bool defined, uint64_t value)
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

      bool CheckSize(::count size) const
      {
         return Defined.get_count() == size || Defined.get_count() == 0;
      }

   };

   struct CFileItem :
      virtual public element
   {
      file_size_t get_count;
      uint32_t Attrib;
      uint32_t Crc;
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
      void SetAttrib(uint32_t attrib)
      {
         AttribDefined = true;
         Attrib = attrib;
      }
   };

   struct CFileItem2
   {
      uint64_t CTime;
      uint64_t ATime;
      uint64_t MTime;
      uint64_t StartPos;
      bool CTimeDefined;
      bool ATimeDefined;
      bool MTimeDefined;
      bool StartPosDefined;
      bool IsAnti;
   };

   struct CArchiveDatabase
   {
      array<file_size_t> PackSizes;
      bool_array PackCRCsDefined;
      array<uint32_t> PackCRCs;
      spa(CFolder) Folders;
      array<CNum> NumUnpackStreamsVector;
      spa(CFileItem) Files;

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
         ::count size = Files.get_count();
         return (
            CTime.CheckSize((int32_t) size) &&
            ATime.CheckSize((int32_t) size) &&
            MTime.CheckSize((int32_t) size) &&
            StartPos.CheckSize((int32_t) size) &&
            (size == IsAnti.get_count() || IsAnti.get_count() == 0));
      }

      bool IsSolid() const
      {
         for (int32_t i = 0; i < NumUnpackStreamsVector.get_count(); i++)
            if (NumUnpackStreamsVector[i] > 1)
               return true;
         return false;
      }
      bool IsItemAnti(index index) const { return (index < IsAnti.get_count() && IsAnti[index]); }
      void SetItemAnti(index index, bool isAnti)
      {
         while (index >= IsAnti.get_count())
            IsAnti.add(false);
         IsAnti[index] = isAnti;
      }

      void GetFile(index index, CFileItem &file, CFileItem2 &file2) const;
      void AddFile(const CFileItem &file, const CFileItem2 &file2);
   };

} // namespace n7z

