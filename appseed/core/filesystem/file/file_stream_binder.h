// StreamBinder.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once





namespace file
{

   class CLASS_DECL_CORE stream_binder :
      virtual public ::object
   {
   public:
      
      
      manual_reset_event   _allBytesAreWritenEvent;
      manual_reset_event   _thereAreBytesToReadEvent;
      manual_reset_event   _readStreamIsClosedEvent;
      byte *               _data;
      uint_ptr            _size;
      uint_ptr            ProcessedSize;


      stream_binder(sp(::axis::application) papp);
      HRes CreateEvents();

      virtual void CreateStreams(sp(::file::reader) & inStream, sp(::file::writer) & outStream);

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void CloseRead();

      virtual void write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten);
      virtual void CloseWrite();

      virtual void ReInit();
   };


} // namespace file




