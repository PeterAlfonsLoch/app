#pragma once


namespace file
{


   class CLASS_DECL_c string_stream_base_impl
   {
   public:


      primitive::memory_size m_dwPos;
      string * m_pstr;


      string_stream_base_impl();
      virtual ~string_stream_base_impl();

   };


   class CLASS_DECL_c string_reader :
      virtual public reader,
      virtual public string_stream_base_impl
   {
   public:


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);


   };


   class CLASS_DECL_c string_writer :
      virtual public writer,
      virtual public string_stream_base_impl
   {
   public:


      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);



   };


} // namespace file



