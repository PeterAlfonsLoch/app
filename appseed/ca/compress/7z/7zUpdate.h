// 7zUpdate.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

/*#include "7zCompressionMode.h"
#include "7zIn.h"
#include "7zOut.h"

#include "../IArchive.h"*/


namespace n7z
{

   struct CUpdateItem
   {
      int32_t IndexInArchive;
      int32_t IndexInClient;

      uint64_t CTime;
      uint64_t ATime;
      uint64_t MTime;

      uint64_t get_count;
      string Name;

      uint32_t Attrib;

      bool NewData;
      bool NewProps;

      bool IsAnti;
      bool IsDir;

      bool AttribDefined;
      bool CTimeDefined;
      bool ATimeDefined;
      bool MTimeDefined;

      bool HasStream() const { return !IsDir && !IsAnti && this->get_count != 0; }

      CUpdateItem():
      IsAnti(false),
         IsDir(false),
         AttribDefined(false),
         CTimeDefined(false),
         ATimeDefined(false),
         MTimeDefined(false)
      {}
      void SetDirStatusFromAttrib() { IsDir = ((Attrib & FILE_ATTRIBUTE_DIRECTORY) != 0); };

      strsize GetExtensionPos() const;
      string GetExtension() const;
   };

   struct CUpdateOptions
   {
      const CCompressionMethodMode *Method;
      const CCompressionMethodMode *HeaderMethod;
      bool UseFilters;
      bool MaxFilter;

      CHeaderOptions HeaderOptions;

      uint64_t NumSolidFiles;
      uint64_t NumSolidBytes;
      bool SolidExtension;
      bool RemoveSfxBlock;
      bool VolumeMode;
   };

   HRESULT Update(
      ::libcompress::codecs_info_interface *codecsInfo, const base_array < ::libcompress::codec_info_ex > *externalCodecs,
      ::ex1::byte_input_stream *inStream,
      const CArchiveDatabaseEx *db,
      const array_ptr_alloc<CUpdateItem> &updateItems,
      COutArchive &archive,
      CArchiveDatabase &newDatabase,
      ::ex1::writer *seqOutStream,
      ::libcompress::archive_update_callback_interface *updateCallback,
      const CUpdateOptions &options,
      ::crypto::get_text_password_interface *getDecoderPassword
      );
} // namespace n7z


