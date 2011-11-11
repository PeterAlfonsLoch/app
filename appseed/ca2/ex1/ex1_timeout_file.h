#pragma once


namespace ex1
{


   class CLASS_DECL_ca timeout_file : 
      public ::ex1::file
   {
   public:


      sp(ex1::file)     m_pfile;
      uint64_t         m_uiExpectedSize;
      DWORD             m_dwTimeOut;
      DWORD             m_dwLastCall;
      DWORD             m_dwSleep;
      sp(mutex)         m_spmutex;


      timeout_file(::ca::application * papp, ex1::file * pfile, uint64_t uiExpectedSize = ((uint64_t) 0));
      virtual ~timeout_file();

      virtual bool IsValid() const;
      file_position seek(file_offset lOff, ::ex1::e_seek  nFrom);
      file_position get_position() const;
      file_size get_length() const;

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void Flush();
      virtual void set_length(file_size dwNewLen);


   };


} // namespace ex1


