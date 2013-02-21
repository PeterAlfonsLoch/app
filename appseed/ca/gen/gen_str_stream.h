#pragma once


namespace ex1
{


   class CLASS_DECL_ca str_stream_base_impl
   {
   public:
      
      
      primitive::memory_size m_dwPos;
      string * m_pstr;

      
      str_stream_base_impl();
      virtual ~str_stream_base_impl();

   };


   class CLASS_DECL_ca str_reader :
      virtual public reader,
      virtual public str_stream_base_impl
   {
   public:


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);


   };


   class CLASS_DECL_ca str_writer :
      virtual public writer,
      virtual public str_stream_base_impl
   {
   public:


      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);



   };



} // namespace ex1

