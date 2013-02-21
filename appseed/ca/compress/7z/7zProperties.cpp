// 7zProperties.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

#include "7zProperties.h"
#include "7zHeader.h"
#include "7zHandler.h"

// #define _MULTI_PACK


namespace n7z
{


   struct CPropMap
   {
      uint64_t FilePropID;
      stat_prop_stg StatPROPSTG;
   };

   CPropMap kPropMap[] =
   {
   { NID::kName, { NULL, ::libcompress::kpidPath, var::type_string } },
   { NID::kSize, { NULL, ::libcompress::kpidSize, var::type_uint64 } },
   { NID::kPackInfo, { NULL,::libcompress:: kpidPackSize, var::type_uint64 } },

   #ifdef _MULTI_PACK
   { 100, { L"Pack0", kpidPackedSize0, var::type_uint64 } },
   { 101, { L"Pack1", kpidPackedSize1, var::type_uint64 } },
   { 102, { L"Pack2", kpidPackedSize2, var::type_uint64 } },
   { 103, { L"Pack3", kpidPackedSize3, var::type_uint64 } },
   { 104, { L"Pack4", kpidPackedSize4, var::type_uint64 } },
   #endif

   { NID::kCTime, { NULL, ::libcompress::kpidCTime, var::type_filetime } },
   { NID::kMTime, { NULL, ::libcompress::kpidMTime, var::type_filetime } },
   { NID::kATime, { NULL, ::libcompress::kpidATime, var::type_filetime } },
   { NID::kWinAttributes, { NULL, ::libcompress::kpidAttrib, var::type_uint } },
   { NID::kStartPos, { NULL, ::libcompress::kpidPosition, var::type_uint } },

   { NID::kCRC, { NULL, ::libcompress::kpidCRC, var::type_uint } },

   { NID::kAnti, { NULL, ::libcompress::kpidIsAnti, var::type_bool } }

   #ifndef _SFX
   ,
   { 97, { NULL,::libcompress::kpidEncrypted, var::type_bool } },
   { 98, { NULL,::libcompress::kpidMethod, var::type_string } },
   { 99, { NULL,::libcompress::kpidBlock, var::type_uint } }
   #endif
   };

   static const int32_t kPropMapSize = sizeof(kPropMap) / sizeof(kPropMap[0]);

   static int32_t FindPropInMap(uint64_t filePropID)
   {
      for (int32_t i = 0; i < kPropMapSize; i++)
      if (kPropMap[i].FilePropID == filePropID)
      return i;
      return -1;
   }

   static void CopyOneItem(base_array<uint64_t> &src,
      base_array<uint64_t> &dest, uint32_t item)
   {
      for (int32_t i = 0; i < src.get_count(); i++)
         if (src[i] == item)
         {
            dest.add(item);
            src.remove_at(i);
            return;
         }
   }

   static void RemoveOneItem(base_array<uint64_t> &src, uint32_t item)
   {
      for (int32_t i = 0; i < src.get_count(); i++)
         if (src[i] == item)
         {
            src.remove_at(i);
            return;
         }
   }

   static void InsertToHead(base_array<uint64_t> &dest, uint32_t item)
   {
      for (int32_t i = 0; i < dest.get_count(); i++)
         if (dest[i] == item)
         {
            dest.remove_at(i);
            break;
         }
         dest.insert_at(0, item);
   }

   void handler::FillPopIDs()
   {
      _fileInfoPopIDs.remove_all();

#ifdef _7Z_VOL
      if(_volumes.get_count() < 1)
         return;
      const CVolume &volume = _volumes.Front();
      const CArchiveDatabaseEx &_db = volume.Database;
#endif

      base_array<uint64_t> fileInfoPopIDs = _db.ArchiveInfo.FileInfoPopIDs;

      RemoveOneItem(fileInfoPopIDs, NID::kEmptyStream);
      RemoveOneItem(fileInfoPopIDs, NID::kEmptyFile);

      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kName);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kAnti);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kSize);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kPackInfo);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kCTime);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kMTime);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kATime);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kWinAttributes);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kCRC);
      CopyOneItem(fileInfoPopIDs, _fileInfoPopIDs, NID::kComment);
      _fileInfoPopIDs.add(fileInfoPopIDs);

#ifndef _SFX
      _fileInfoPopIDs.add(97);
      _fileInfoPopIDs.add(98);
      _fileInfoPopIDs.add(99);
#endif
#ifdef _MULTI_PACK
      _fileInfoPopIDs.add(100);
      _fileInfoPopIDs.add(101);
      _fileInfoPopIDs.add(102);
      _fileInfoPopIDs.add(103);
      _fileInfoPopIDs.add(104);
#endif

#ifndef _SFX
      InsertToHead(_fileInfoPopIDs, NID::kMTime);
      InsertToHead(_fileInfoPopIDs, NID::kPackInfo);
      InsertToHead(_fileInfoPopIDs, NID::kSize);
      InsertToHead(_fileInfoPopIDs, NID::kName);
#endif
   }

   gen::HRes handler::GetNumberOfProperties(uint32_t *numProperties)
   {

      *numProperties = (uint32_t) _fileInfoPopIDs.get_count();

      return S_OK;

   }

   gen::HRes handler::GetPropertyInfo(uint32_t index, string & name, int32_t * propID, var::e_type *varType)
   {
      if ((int32_t)index >= _fileInfoPopIDs.get_count())
         return E_INVALIDARG;
      int32_t indexInMap = FindPropInMap(_fileInfoPopIDs[index]);
      if (indexInMap == -1)
         return E_INVALIDARG;
      throw not_implemented(get_app());
      /*
      const STATPROPSTG &srcItem = kPropMap[indexInMap].StatPROPSTG;
      *propID = srcItem.propid;
      *varType = srcItem.vt;
      name.Empty();*/
      return S_OK;
   }


} // namespace n7z



