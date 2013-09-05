#pragma once


namespace file
{


   class writer;

   typedef smart_pointer < writer > writer_sp;


   class CLASS_DECL_c writer :
      virtual public object
   {
   public:

      
      writer();
      virtual ~writer();

      
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten);

      virtual void read_from(reader & reader);

      virtual void close();

      virtual void flush();

      

   };


   typedef writer writable;

   CLASS_DECL_c HRESULT write_writer(writer * stream, const void * data, ::primitive::memory_size size);



} // namespace file




