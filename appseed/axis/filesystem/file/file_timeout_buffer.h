#pragma once


namespace file
{


   class CLASS_DECL_AXIS timeout_buffer :
      public ::file::binary_buffer
   {
   public:


      ::file::buffer_sp      m_pfile;
      uint64_t          m_uiExpectedSize;
      uint32_t             m_dwTimeOut;
      uint32_t             m_dwLastCall;
      uint32_t             m_dwSleep;
      sp(mutex)         m_spmutex;


      timeout_buffer(sp(::base::application) papp, ::file::buffer_sp  pfile, uint64_t uiExpectedSize = ((uint64_t)0));
      virtual ~timeout_buffer();

      virtual bool IsValid() const;
      file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      file_position get_position() const;
      file_size get_length() const;
      file_size get_length(single_lock * psl) const;

      using ::file::stream_buffer::read;
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      using ::file::stream_buffer::write;
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void flush();
      virtual void set_length(file_size dwNewLen);


   };


} // namespace file


