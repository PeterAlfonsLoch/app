#pragma once


namespace file
{


   class writer;

   typedef smart_pointer < writer > writer_sp;


   class CLASS_DECL_BASE writer :
      virtual public stream_buffer_base
   {
   public:

      
      writer();
      virtual ~writer();

      
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten);

      virtual void transfer_from(reader & reader, ::primitive::memory_size uiBufferSize = 1024 * 1024);
      virtual void transfer_from_begin(reader & reader, ::primitive::memory_size uiBufSize = 1024 * 1024);

      virtual void close();

      virtual void flush();


   };


   typedef writer writable;

   
   CLASS_DECL_BASE HRESULT write(writer * pwriter, const void * data, ::primitive::memory_size size);



} // namespace file




