#pragma once

namespace ex1
{

   class CLASS_DECL_ca str_stream_base_impl
   {
   public:
      DWORD m_dwPos;
      string * m_pstr;
   };

   class CLASS_DECL_ca str_reader :
      virtual public reader,
      virtual public str_stream_base_impl
   {
   public:
      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);
   };


   class CLASS_DECL_ca str_writer :
      virtual public writer,
      virtual public str_stream_base_impl
   {
   public:
      virtual void write(const void *lpBuf, DWORD_PTR nCount);
   };



} // namespace ex1

