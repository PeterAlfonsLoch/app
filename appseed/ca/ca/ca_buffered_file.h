#pragma once


namespace ca
{


   class CLASS_DECL_ca buffered_file : 
      public ::ca::file
   {
   public:


      ::ca::filesp                m_pfile;

      ::primitive::memory_size   m_uiBufferSize;
      file_position              m_uiPosition;
      file_position              m_uiBufLPos;
      file_position              m_uiBufUPos;
      bool                       m_bDirty;
      file_position              m_uiWriteLPos;
      file_position              m_uiWriteUPos;
      primitive::memory          m_storage;


      buffered_file(::ca::application * papp, ::ca::filesp pfile, ::primitive::memory_size iBufferSize = 1024 * 128);
      virtual ~buffered_file();


      virtual bool IsValid() const;
      file_position seek(file_offset lOff, ::ca::e_seek nFrom);
      file_position get_position() const;
      file_size get_length() const;

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual void flush();
      virtual bool buffer(::primitive::memory_size uiGrow = 0);
      virtual void set_length(file_size dwNewLen);

      uint64_t      GetBufferSize();

   };


} // namespace ca


