#pragma once


namespace ca
{


   class CLASS_DECL_ca timeout_file : 
      public ::ca::file
   {
   public:


      sp(::ca::file)     m_pfile;
      uint64_t          m_uiExpectedSize;
      uint32_t             m_dwTimeOut;
      uint32_t             m_dwLastCall;
      uint32_t             m_dwSleep;
      sp(mutex)         m_spmutex;


      timeout_file(::ca::applicationsp papp, ::ca::file * pfile, uint64_t uiExpectedSize = ((uint64_t) 0));
      virtual ~timeout_file();

      virtual bool IsValid() const;
      file_position seek(file_offset lOff, ::ca::e_seek  nFrom);
      file_position get_position() const;
      file_size get_length() const;
      file_size get_length(single_lock * psl) const;

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void flush();
      virtual void set_length(file_size dwNewLen);


   };


} // namespace ca


