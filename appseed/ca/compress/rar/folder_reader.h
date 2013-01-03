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
      public ex1::reader
   {
   public:


     base_array<input_file> *_archives;
     const base_array<CItemEx> *_items;
     CRefItem _refItem;
     int32_t _curIndex;
     uint32_t _crc;
     bool _fileIsOpen;
     ex1::reader * _stream;
     uint_array CRCs;

     ::primitive::memory_size read(void * data, ::primitive::memory_size size);

     HRESULT OpenStream();
     HRESULT CloseStream();
     void Init(base_array < input_file > * archives, const base_array < CItemEx > * items, const CRefItem & refItem);

   };
  
} // namespace rar
