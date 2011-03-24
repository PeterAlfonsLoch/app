// StreamBinder.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "StdAfx.h"

namespace ex1
{

   class reader_for_binder:
      public ex1::reader
   {
   public:

      
      stream_binder * m_StreamBinder;


      ~reader_for_binder() { m_StreamBinder->CloseRead(); }
      
      virtual DWORD_PTR read(void *data, DWORD_PTR size);

      void set_binder(stream_binder *streamBinder) { m_StreamBinder = streamBinder; }

   };

   DWORD_PTR reader_for_binder::read(void *data, DWORD_PTR size)
   { 
      return m_StreamBinder->read(data, size); 
   }

   class writer_for_binder:
      public ex1::writer
   {
   public:


      stream_binder *m_StreamBinder;

      
      ~writer_for_binder() {  m_StreamBinder->CloseWrite(); }

      virtual void write(const void *lpBuf, DWORD_PTR nCount, DWORD_PTR * dwWritten);

      void set_binder(stream_binder *streamBinder) { m_StreamBinder = streamBinder; }

   };

   void writer_for_binder::write(const void *data, DWORD_PTR size, DWORD_PTR *processedSize)
   { return m_StreamBinder->write(data, size, processedSize); }


   //////////////////////////
   // stream_binder
   // (_thereAreBytesToReadEvent && _bufferSize == 0) means that stream is finished.

   HRes stream_binder::CreateEvents()
   {
      _allBytesAreWritenEvent.SetEvent();
      _thereAreBytesToReadEvent.ResetEvent();
      _readStreamIsClosedEvent.ResetEvent();
      return S_OK;
   }

   void stream_binder::ReInit()
   {
      _thereAreBytesToReadEvent.ResetEvent();
      _readStreamIsClosedEvent.ResetEvent();
      ProcessedSize = 0;
   }



   stream_binder::stream_binder()
   {
   }


   void stream_binder::CreateStreams(ex1::reader **inStream, ex1::writer **outStream)
   {
      reader_for_binder * inStreamSpec = new reader_for_binder;
      sp(ex1::reader) inStreamLoc(inStreamSpec);
      inStreamSpec->set_binder(this);
      *inStream = inStreamLoc.detach();

      writer_for_binder *outStreamSpec = new
         writer_for_binder;
      sp(ex1::writer) outStreamLoc(outStreamSpec);
      outStreamSpec->set_binder(this);
      *outStream = outStreamLoc.detach();

      _data = NULL;
      _size = 0;
      ProcessedSize = 0;
   }

   DWORD_PTR stream_binder::read(void *data, DWORD_PTR size)
   {
      uint sizeToRead = size;
      if(size > 0)
      {
         _thereAreBytesToReadEvent.Lock();
         sizeToRead = min(_size, size);
         if(_size > 0)
         {
            memcpy(data, _data, sizeToRead);
            _data += sizeToRead;
            _size -= sizeToRead;
            if(_size <= 0)
            {
               _thereAreBytesToReadEvent.ResetEvent();
               _allBytesAreWritenEvent.SetEvent();
            }
         }
      }
      ProcessedSize += sizeToRead;
      return sizeToRead;
   }

   void stream_binder::CloseRead()
   {
      _readStreamIsClosedEvent.SetEvent();
   }

   void stream_binder::write(const void *data, DWORD_PTR size, DWORD_PTR *processedSize)
   {
      if (size > 0)
      {
         _data = (byte *) data;
         _size = size;
         _allBytesAreWritenEvent.ResetEvent();
         _thereAreBytesToReadEvent.SetEvent();

         sync_object_base * events[2];
         events[0] = &_allBytesAreWritenEvent;
         events[1] = &_readStreamIsClosedEvent;
         CMultiLock ml(events, 2);
         DWORD waitResult = ml.Lock(INFINITE, FALSE);
         if(waitResult != WAIT_OBJECT_0 + 0)
         {
            throw S_FALSE;
         }
      }
      if (processedSize != NULL)
         *processedSize = size;
   }

   void stream_binder::CloseWrite()
   {
      // _bufferSize must be = 0
      _thereAreBytesToReadEvent.SetEvent();
   }


} // namespace ex1