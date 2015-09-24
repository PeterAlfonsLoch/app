// Rar/Handler.h

#pragma once

/*#include "../IArchive.h"

#include "../../Common/CreateCoder.h"

#include "RarIn.h"
#include "RarVolumeInStream.h"*/


namespace rar
{

   class handler:
      public input_file,
      public ::libcompress::set_codecs_info_interface
   {
   public:


      array<CRefItem>    _refItems;
      array<CItemEx>     _items;
      array<input_file>  _archives;
      input_file_info         _archiveInfo;
      string                  _errorMessage;


      ///DECL_EXTERNAL_CODECS_VARS
      ::libcompress::codecs_info_interface * _codecsInfo;
      array < ::libcompress::codec_info_ex > _externalCodecs;




      uint64_t GetPackSize(int32_t refIndex) const;

      bool IsSolid(int32_t refIndex);
      void AddErrorMessage(const string &s);

      //HRESULT Open2(::file::input_stream *stream, // seekable input stream
      HRESULT Open2(::file::input_stream * stream, const file_position_t * maxCheckStartPosition,  ::libcompress::archive_open_callback_interface *openCallback);

   /*public:
      MY_QUERYINTERFACE_BEGIN2(IInArchive)
         QUERY_ENTRY_ISetCompressCodecsInfo
         MY_QUERYINTERFACE_END
         MY_ADDREF_RELEASE*/

         CA2_COMPRESS_INTERFACE_input_archive(;)

         HRes SetCompressCodecsInfo(::libcompress::codecs_info_interface *compressCodecsInfo);
   };

} // namespace rar
