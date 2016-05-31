#pragma once


namespace file
{


   class CLASS_DECL_AURA buffered_buffer :
      public ::file::binary_buffer
   {
   public:


      ::file::buffer_sp                m_pfile;

      memory_size_t   m_uiBufferSize;
      file_position_t              m_uiPosition;
      file_position_t              m_uiBufLPos;
      file_position_t              m_uiBufUPos;
      bool                       m_bDirty;
      file_position_t              m_uiWriteLPos;
      file_position_t              m_uiWriteUPos;
      memory          m_storage;


      buffered_buffer(::aura::application * papp, ::file::buffer_sp pfile, memory_size_t iBufferSize = 1024 * 128);
      virtual ~buffered_buffer();


      virtual bool IsValid() const;
      file_position_t seek(file_offset_t lOff, ::file::e_seek nFrom);
      file_position_t get_position() const;
      file_size_t get_length() const;

      using ::file::stream_buffer::read;
      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      
      using ::file::stream_buffer::write;
      virtual void write(const void * lpBuf, memory_size_t nCount);
      
      virtual void flush();
      virtual bool buffer(memory_size_t uiGrow = 0);
      virtual void set_length(file_size_t dwNewLen);

      uint64_t      GetBufferSize();

   };


} // namespace file


