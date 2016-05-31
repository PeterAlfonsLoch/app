#pragma once


namespace file
{


   class CLASS_DECL_ACE timeout_buffer :
      public ::file::binary_buffer
   {
   public:


      ::file::buffer_sp      m_pfile;
      uint64_t          m_uiExpectedSize;
      uint32_t             m_dwTimeOut;
      uint32_t             m_dwLastCall;
      uint32_t             m_dwSleep;
      sp(mutex)         m_spmutex;


      timeout_buffer(::ace::application * papp, ::file::buffer_sp  pfile, uint64_t uiExpectedSize = ((uint64_t)0));
      virtual ~timeout_buffer();

      virtual bool IsValid() const;
      file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom);
      file_position_t get_position() const;
      file_size_t get_length() const;
      file_size_t get_length(single_lock * psl) const;

      using ::file::stream_buffer::read;
      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      using ::file::stream_buffer::write;
      virtual void write(const void * lpBuf, memory_size_t nCount);
      virtual void flush();
      virtual void set_length(file_size_t dwNewLen);


   };


} // namespace file


