// StreamBinder.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"


namespace file
{


   class reader_for_binder:
      public ::file::reader
   {
   public:

      
      stream_binder * m_StreamBinder;


      ~reader_for_binder() { m_StreamBinder->CloseRead(); }
      
      virtual ::primitive::memory_size read(void *data, ::primitive::memory_size size);

      void set_binder(stream_binder *streamBinder) { m_StreamBinder = streamBinder; }

   };

   ::primitive::memory_size reader_for_binder::read(void *data, ::primitive::memory_size size)
   { 
      return m_StreamBinder->read(data, size); 
   }

   class writer_for_binder:
      public ::file::writer
   {
   public:


      stream_binder *m_StreamBinder;

      
      ~writer_for_binder() {  m_StreamBinder->CloseWrite(); }

      virtual void write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten);

      void set_binder(stream_binder *streamBinder) { m_StreamBinder = streamBinder; }

   };

   void writer_for_binder::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize)
   { 
      return m_StreamBinder->write(data, size, processedSize); 
   }


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



   stream_binder::stream_binder(sp(::base::application) papp) :
      element(papp),
      _allBytesAreWritenEvent(papp),
      _thereAreBytesToReadEvent(papp),
      _readStreamIsClosedEvent(papp)
   {
   }


   void stream_binder::CreateStreams(sp(::file::reader) & inStream, sp(::file::writer) & outStream)
   {
      
      reader_for_binder * inStreamSpec = new reader_for_binder;
      inStreamSpec->set_binder(this);
      inStream = inStreamSpec;

      writer_for_binder *outStreamSpec = new writer_for_binder;
      outStreamSpec->set_binder(this);
      outStream = outStreamSpec;

      _data = NULL;
      _size = 0;
      ProcessedSize = 0;

   }

   ::primitive::memory_size stream_binder::read(void *data, ::primitive::memory_size size)
   {
      primitive::memory_size sizeToRead = size;
      if(size > 0)
      {
         _thereAreBytesToReadEvent.wait();
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

   void stream_binder::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size * processedSize)
   {
      if (size > 0)
      {
         _data = (byte *) data;
         _size = size;
         _allBytesAreWritenEvent.ResetEvent();
         _thereAreBytesToReadEvent.SetEvent();

         event_collection eva(get_app());
         eva.add(_allBytesAreWritenEvent);
         eva.add(_readStreamIsClosedEvent);
         if(!eva.wait(false, duration::infinite()).signaled())
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


} // namespace file



