#pragma once


namespace file
{


   class CLASS_DECL_BASE buffered_buffer :
      public ::file::binary_buffer
   {
   public:


      ::file::binary_buffer_sp                m_pfile;

      ::primitive::memory_size   m_uiBufferSize;
      file_position              m_uiPosition;
      file_position              m_uiBufLPos;
      file_position              m_uiBufUPos;
      bool                       m_bDirty;
      file_position              m_uiWriteLPos;
      file_position              m_uiWriteUPos;
      primitive::memory          m_storage;


      buffered_buffer(sp(::base::application) papp, ::file::binary_buffer_sp pfile, ::primitive::memory_size iBufferSize = 1024 * 128);
      virtual ~buffered_buffer();


      virtual bool IsValid() const;
      file_position seek(file_offset lOff, ::file::e_seek nFrom);
      file_position get_position() const;
      file_size get_length() const;

      using ::file::stream_buffer::read;
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      
      using ::file::stream_buffer::write;
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      
      virtual void flush();
      virtual bool buffer(::primitive::memory_size uiGrow = 0);
      virtual void set_length(file_size dwNewLen);

      uint64_t      GetBufferSize();

   };


} // namespace file


