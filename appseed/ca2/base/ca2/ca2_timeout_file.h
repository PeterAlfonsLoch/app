#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 timeout_file : 
      public ::file::file
   {
   public:


      sp(::file::file)     m_pfile;
      uint64_t          m_uiExpectedSize;
      uint32_t             m_dwTimeOut;
      uint32_t             m_dwLastCall;
      uint32_t             m_dwSleep;
      sp(mutex)         m_spmutex;


      timeout_file(sp(::application) papp, sp(::file::file) pfile, uint64_t uiExpectedSize = ((uint64_t) 0));
      virtual ~timeout_file();

      virtual bool IsValid() const;
      file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      file_position get_position() const;
      file_size get_length() const;
      file_size get_length(single_lock * psl) const;

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void flush();
      virtual void set_length(file_size dwNewLen);


   };


} // namespace ca2


