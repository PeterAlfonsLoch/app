// RarVolumeInStream.h

#pragma once

/*#include "../../IStream.h"
#include "RarIn.h"*/

namespace rar
{

   struct CRefItem
   {
     int VolumeIndex;
     int ItemIndex;
     int NumItems;
   };

   class folder_reader :
      public ex1::reader
   {
   public:


     base_array<input_file> *_archives;
     const base_array<CItemEx> *_items;
     CRefItem _refItem;
     int _curIndex;
     uint32 _crc;
     bool _fileIsOpen;
     ex1::reader * _stream;
     uint_array CRCs;

     ::primitive::memory_size read(void * data, ::primitive::memory_size size);

     HRESULT OpenStream();
     HRESULT CloseStream();
     void Init(base_array < input_file > * archives, const base_array < CItemEx > * items, const CRefItem & refItem);

   };
  
} // namespace rar
