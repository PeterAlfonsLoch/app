#pragma once


namespace file
{


   class writer;

   class CLASS_DECL_c out_stream_flush :
      virtual public object
   {
   public:
      virtual void flush() = 0;
   };


   typedef smart_pointer < writer > writer_sp;


   class CLASS_DECL_c writer :
      virtual public seekable,
      virtual public out_stream_flush
   {
   public:

      
      writer_sp       m_spwriter;

      
      writer();
      writer(writer * pwriter);
      writer(const writer & pwriter);
      virtual ~writer();

      
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten);

      virtual void read(reader & reader);

      writer & operator = (const writer & writer);

      virtual bool is_writer_null();
      virtual bool is_writer_set();

      virtual void close();

      virtual void from_hex(const char * psz);

      virtual void flush();

   };


   typedef writer writable;


} // namespace file




