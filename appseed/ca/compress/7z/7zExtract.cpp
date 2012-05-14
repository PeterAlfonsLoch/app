// 7zExtract.cpp

#include "framework.h"

/*#include "../../../Common/ComTry.h"

#include "../../Common/ProgressUtils.h"

#include "7zDecode.h"
// #include "7z1Decode.h"
#include "7zFolderOutStream.h"
#include "7zHandler.h"
*/

namespace n7z
{

   struct CExtractFolderInfo
   {
     #ifdef _7Z_VOL
     int VolumeIndex;
     #endif
     CNum FileIndex;
     CNum FolderIndex;
     bool_array ExtractStatuses;
     uint64 UnpackSize;
     CExtractFolderInfo(
       #ifdef _7Z_VOL
       int volumeIndex,
       #endif
       CNum fileIndex, CNum folderIndex):
       #ifdef _7Z_VOL
       VolumeIndex(volumeIndex),
       #endif
       FileIndex(fileIndex),
       FolderIndex(folderIndex),
       UnpackSize(0)
     {
       if (fileIndex != kNumNoIndex)
       {
         ExtractStatuses.set_size(0, 1);
         ExtractStatuses.add(true);
       }
     };
   };

   ex1::HRes handler::Extract(const uint32 *indices, uint32 numItems,
       int32 testModeSpec, ::compress::archive_extract_callback_interface *extractCallbackSpec)
   {
     bool testMode = (testModeSpec != 0);
     ::ca::smart_pointer < ::compress::archive_extract_callback_interface > extractCallback = extractCallbackSpec;
     uint64 importantTotalUnpacked = 0;

     bool allFilesMode = (numItems == (uint32)-1);
     if (allFilesMode)
       numItems =
       #ifdef _7Z_VOL
       _refs.get_count();
       #else
       (const uint32_t) _db.Files.get_count();
       #endif

     if(numItems == 0)
       return S_OK;

     /*
     if(_volumes.get_count() != 1)
       return E_FAIL;
     const CVolume &volume = _volumes.Front();
     const CArchiveDatabaseEx &_db = volume.Database;
     IInStream *_inStream = volume.Stream;
     */

     array_del_ptr<CExtractFolderInfo> extractFolderInfoVector;
     for (uint32 ii = 0; ii < numItems; ii++)
     {
       // uint32 fileIndex = allFilesMode ? indexIndex : indices[indexIndex];
       uint32 ref2Index = allFilesMode ? ii : indices[ii];
       // const CRef2 &ref2 = _refs[ref2Index];

       // for (uint32 ri = 0; ri < ref2.Refs.get_count(); ri++)
       {
         #ifdef _7Z_VOL
         // const CRef &ref = ref2.Refs[ri];
         const CRef &ref = _refs[ref2Index];

         int volumeIndex = ref.VolumeIndex;
         const CVolume &volume = _volumes[volumeIndex];
         const CArchiveDatabaseEx &db = volume.Database;
         uint32 fileIndex = ref.ItemIndex;
         #else
         const CArchiveDatabaseEx &db = _db;
         uint32 fileIndex = ref2Index;
         #endif

         CNum folderIndex = db.FileIndexToFolderIndexMap[fileIndex];
         if (folderIndex == kNumNoIndex)
         {
           extractFolderInfoVector.add(new CExtractFolderInfo(
               #ifdef _7Z_VOL
               volumeIndex,
               #endif
               fileIndex, kNumNoIndex));
           continue;
         }
         if (extractFolderInfoVector.is_empty() ||
           folderIndex != extractFolderInfoVector.last_element().FolderIndex
           #ifdef _7Z_VOL
           || volumeIndex != extractFolderInfoVector.last_element().VolumeIndex
           #endif
           )
         {
           extractFolderInfoVector.add(new CExtractFolderInfo(
               #ifdef _7Z_VOL
               volumeIndex,
               #endif
               kNumNoIndex, folderIndex));
           const CFolder &folderInfo = db.Folders[folderIndex];
           uint64 unpackSize = folderInfo.GetUnpackSize();
           importantTotalUnpacked += unpackSize;
           extractFolderInfoVector.last_element().UnpackSize = unpackSize;
         }

         CExtractFolderInfo &efi = extractFolderInfoVector.last_element();

         // const CFolderInfo &folderInfo = m_dam_Folders[folderIndex];
         CNum startIndex = (CNum) db.FolderStartFileIndex[folderIndex];
         for(CNum index = (CNum) efi.ExtractStatuses.get_count();
             index <= fileIndex - startIndex; index++)
         {
           // uint64 unpackSize = _db.Files[startIndex + index].UnpackSize;
           // Count partial_folder_size
           // efi.UnpackSize += unpackSize;
           // importantTotalUnpacked += unpackSize;
           efi.ExtractStatuses.add(index == fileIndex - startIndex);
         }
       }
     }

     RINOK(extractCallback->SetTotal(importantTotalUnpacked));

     CDecoder decoder(
       #ifdef _ST_MODE
       false
       #else
       true
       #endif
       );
     // CDecoder1 decoder;

     uint64 totalPacked = 0;
     uint64 totalUnpacked = 0;
     uint64 curPacked, curUnpacked;

     ::compress::local_progress *lps = new ::compress::local_progress;
     ::ca::smart_pointer < ::compress::progress_info_interface > progress = lps;
     lps->Init(extractCallback, false);

     for (int i = 0;; i++, totalUnpacked += curUnpacked, totalPacked += curPacked)
     {
       lps->OutSize = totalUnpacked;
       lps->InSize = totalPacked;
       RINOK(lps->SetCur());

       if (i >= extractFolderInfoVector.get_count())
         break;

       const CExtractFolderInfo &efi = extractFolderInfoVector[i];
       curUnpacked = efi.UnpackSize;
       curPacked = 0;

       CFolderOutStream *folderOutStream = new CFolderOutStream;
       ::ca::smart_pointer < ::ex1::writer > outStream(folderOutStream);

       #ifdef _7Z_VOL
       const CVolume &volume = _volumes[efi.VolumeIndex];
       const CArchiveDatabaseEx &db = volume.Database;
       #else
       const CArchiveDatabaseEx &db = _db;
       #endif

       CNum startIndex;
       if (efi.FileIndex != kNumNoIndex)
         startIndex = efi.FileIndex;
       else
         startIndex = db.FolderStartFileIndex[efi.FolderIndex];

       HRESULT result = folderOutStream->Init(&db,
           #ifdef _7Z_VOL
           volume.StartRef2Index,
           #else
           0,
           #endif
           startIndex,
           &efi.ExtractStatuses, extractCallback, testMode, _crcSize != 0);

       RINOK(result);

       if (efi.FileIndex != kNumNoIndex)
         continue;

       CNum folderIndex = efi.FolderIndex;
       const CFolder &folderInfo = db.Folders[folderIndex];

       curPacked = _db.GetFolderFullPackSize(folderIndex);

       CNum packStreamIndex = db.FolderStartPackStreamIndex[folderIndex];
       uint64 folderStartPackPos = db.GetFolderStreamPos(folderIndex, 0);

       #ifndef _NO_CRYPTO
       ::ca::smart_pointer < ::crypto::get_text_password_interface > getTextPassword;
       if (extractCallback)
       {

         getTextPassword = dynamic_cast < ::crypto::get_text_password_interface * > (extractCallback.m_p);
       }
       #endif

       try
       {
         #ifndef _NO_CRYPTO
         bool passwordIsDefined;
         #endif

         HRESULT result = decoder.Decode(
             _codecsInfo, &_externalCodecs,
             #ifdef _7Z_VOL
             volume.Stream,
             #else
             _inStream,
             #endif
             folderStartPackPos,
             &db.PackSizes[packStreamIndex],
             folderInfo,
             outStream,
             progress
             , getTextPassword, passwordIsDefined
             , true, _numThreads
             );

         if (result == S_FALSE)
         {
            RINOK(folderOutStream->FlushCorrupted(::compress::archive::extract::operation_result_DataError));
           continue;
         }
         if (result == E_NOTIMPL)
         {
            RINOK(folderOutStream->FlushCorrupted(::compress::archive::extract::operation_result_UnSupportedMethod));
         }
         if (result != S_OK)
           return result;
         if (folderOutStream->WasWritingFinished() != S_OK)
         {
           RINOK(folderOutStream->FlushCorrupted(::compress::archive::extract::operation_result_DataError));
           continue;
         }
       }
       catch(...)
       {
         RINOK(folderOutStream->FlushCorrupted(::compress::archive::extract::operation_result_DataError));
         continue;
       }
     }
     return S_OK;
   }

} // namespace n7z
