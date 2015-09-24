// RarVolumeInStream.cpp
// from 7-zip
#include "framework.h"

/*#include "../../../../C/7zCrc.h"

#include "RarVolumeInStream.h"*/

namespace rar
{

   void folder_reader::Init(array<input_file> *archives, const array<CItemEx> *items, const CRefItem &refItem)
   {
      _archives = archives;
      _items = items;
      _refItem = refItem;
      _curIndex = 0;
      CRCs.remove_all();
      _fileIsOpen = false;
   }

   HRESULT folder_reader::OpenStream()
   {
      while (_curIndex < _refItem.NumItems)
      {
         const CItemEx &item = (*_items)[_refItem.ItemIndex + _curIndex];
         _stream = (*_archives)[_refItem.VolumeIndex + _curIndex].CreateLimitedStream(item.GetDataPosition(), item.PackSize);
         _curIndex++;
         _fileIsOpen = true;
         _crc = CRC_INIT_VAL;
         return S_OK;
      }
      return S_OK;
   }

   HRESULT folder_reader::CloseStream()
   {
      CRCs.add(CRC_GET_DIGEST(_crc));
      //_stream.Release();
      _fileIsOpen = false;
      return S_OK;
   }

   memory_size_t folder_reader::read(void *data, memory_size_t size)
   {
      memory_size_t realProcessedSize = 0;
      while ((_curIndex < _refItem.NumItems || _fileIsOpen) && size > 0)
      {
         if (_fileIsOpen)
         {
            memory_size_t localProcessedSize;
               
            localProcessedSize = _stream->read(((byte *)data) + realProcessedSize, size);
            _crc = crc_update(_crc, ((byte *)data) + realProcessedSize, localProcessedSize);
            if (localProcessedSize == 0)
            {
               CloseStream();
               continue;
            }
            realProcessedSize += localProcessedSize;
            size -= localProcessedSize;
            break;
         }
         else
         {
            OpenStream();
         }
      }
      return realProcessedSize;
   }

} // namespace rar
