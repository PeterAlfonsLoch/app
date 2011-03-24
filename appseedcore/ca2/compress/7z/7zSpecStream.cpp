// 7zSpecStream.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "StdAfx.h"

namespace compress
{

   DWORD_PTR size_count_reader2::read(void *data, DWORD_PTR size)
   {
     uint32 realProcessedSize = realProcessedSize = _stream->read(data, size);
     _size += realProcessedSize;
     return realProcessedSize;
   }

   ex1::HRes size_count_reader2::GetSubStreamSize(uint64 subStream, uint64 *value)
   {
     if (_getSubStreamSize == NULL)
       return E_NOTIMPL;
     return  _getSubStreamSize->GetSubStreamSize(subStream, value);
   }


}