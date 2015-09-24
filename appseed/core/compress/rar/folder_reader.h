// RarVolumeInStream.h

#pragma once

/*#include "../../IStream.h"
#include "RarIn.h"*/

namespace rar
{

   struct CRefItem
   {
     int32_t VolumeIndex;
     int32_t ItemIndex;
     int32_t NumItems;
   };

   class folder_reader :
      public ::file::reader
   {
   public:


     array<input_file> *_archives;
     const array<CItemEx> *_items;
     CRefItem _refItem;
     int32_t _curIndex;
     uint32_t _crc;
     bool _fileIsOpen;
     ::file::reader * _stream;
     uint_array CRCs;

     memory_size_t read(void * data, memory_size_t size);

     HRESULT OpenStream();
     HRESULT CloseStream();
     void Init(array < input_file > * archives, const array < CItemEx > * items, const CRefItem & refItem);

   };
  
} // namespace rar
