// StreamBinder.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace ex1
{

   class CLASS_DECL_ca stream_binder :
      virtual public ::radix::object
   {
   public:
      
      
      manual_reset_event   _allBytesAreWritenEvent;
      manual_reset_event   _thereAreBytesToReadEvent;
      manual_reset_event   _readStreamIsClosedEvent;
      byte *               _data;
      dword_ptr            _size;
      dword_ptr            ProcessedSize;


      stream_binder();
      HRes CreateEvents();

      virtual void CreateStreams(ex1::reader **inStream, ex1::writer **outStream);

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void CloseRead();

      virtual void write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten);
      virtual void CloseWrite();

      virtual void ReInit();
   };

} // namespace ex1

