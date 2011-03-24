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
      public compress::set_codecs_info_interface
   {
   public:
      
      
      base_array<CRefItem>    _refItems;
      base_array<CItemEx>     _items;
      base_array<input_file>  _archives;
      input_file_info         _archiveInfo;
      string                  _errorMessage;


      ///DECL_EXTERNAL_CODECS_VARS
      ::compress::codecs_info_interface * _codecsInfo; 
      base_array < ::compress::codec_info_ex > _externalCodecs;




      uint64 GetPackSize(int refIndex) const;

      bool IsSolid(int refIndex);
      void AddErrorMessage(const string &s);

      //HRESULT Open2(ex1::input_stream *stream, // seekable input stream
      HRESULT Open2(ex1::input_stream *stream,
         const uint64 *maxCheckStartPosition,
         compress::archive_open_callback_interface *openCallback);

   /*public:
      MY_QUERYINTERFACE_BEGIN2(IInArchive)
         QUERY_ENTRY_ISetCompressCodecsInfo
         MY_QUERYINTERFACE_END
         MY_ADDREF_RELEASE*/

         CA2_COMPRESS_INTERFACE_input_archive(;)

         ex1::HRes SetCompressCodecsInfo(::compress::codecs_info_interface *compressCodecsInfo);
   };

} // namespace rar
