#pragma once


namespace file
{


   class memory_buffer;

   
   typedef sp(memory_buffer) memory_buffer_sp;


   class CLASS_DECL_AURA memory_buffer :
      virtual public ::file::stream_buffer,
      virtual public primitive::memory_container
   {
   protected:

   
      memory_position_t      m_dwPosition;


   public:
   
      memory_buffer(::aura::application * papp, memory_size_t iSize = 0);
      memory_buffer(::aura::application * papp, void * pMemory, memory_size_t dwSize);
      memory_buffer(::aura::application * papp, const memory_buffer & memoryfile);
      memory_buffer(::aura::application * papp, ::primitive::memory_base * pmemory);
      virtual ~memory_buffer();


      virtual bool IsValid() const;
      memory_size_t remove_begin(void * lpBuf, memory_size_t uiCount);
      void load_string(string & str);
      using ::object::create;
      void create(memory_size_t iSize = -1);
      file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom);
      file_position_t get_position() const;

      virtual string GetFilePath() const;

      virtual ::primitive::memory_base * create_memory();

      void set_length(file_size_t dwNewLen);
      file_size_t get_length() const;
      void Truncate(file_size_t iPosition);
      void clear();
      
      using ::file::stream_buffer::read;
      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      
      using ::file::stream_buffer::write;
      virtual void write(const void * lpBuf, memory_size_t nCount);
      virtual void write_from_hex(const void * lpBuf,memory_size_t nCount);

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

      void flush();


      virtual void full_load(const char * psz);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      using ::file::stream_buffer::get_internal_data;
      virtual void * get_internal_data();
      virtual memory_size_t get_internal_data_size() const;
      virtual bool set_internal_data_size(memory_size_t c);

      virtual void transfer_to(writer & writer, memory_size_t uiBufferSize = 1024 * 1024);

      
   };


} // namespace primitive


