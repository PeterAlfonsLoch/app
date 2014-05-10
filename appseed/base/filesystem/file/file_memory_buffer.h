#pragma once


namespace file
{


   class memory_buffer;

   
   typedef sp(memory_buffer) memory_buffer_sp;


   class CLASS_DECL_BASE memory_buffer :
      virtual public ::file::stream_buffer,
      virtual public primitive::memory_container
   {
   protected:

   
      ::primitive::memory_position      m_dwPosition;


   public:
   

      memory_buffer(sp(::base::application) papp, ::primitive::memory_size iSize = 0);
      memory_buffer(sp(::base::application) papp, void * pMemory, ::primitive::memory_size dwSize);
      memory_buffer(sp(::base::application) papp, const memory_buffer & memoryfile);
      memory_buffer(sp(::base::application) papp, ::primitive::memory_base * pmemory);
      virtual ~memory_buffer();


      virtual bool IsValid() const;
      ::primitive::memory_size remove_begin(void * lpBuf, ::primitive::memory_size uiCount);
      void load_string(string & str);
      using ::request_interface::create;
      void create(::primitive::memory_size iSize = -1);
      file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      file_position get_position() const;

      virtual string GetFilePath() const;

      virtual ::primitive::memory_base * create_memory();

      void set_length(file_size dwNewLen);
      file_size get_length() const;
      void Truncate(file_size iPosition);
      void clear();
      
      using ::file::stream_buffer::read;
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      
      using ::file::stream_buffer::write;
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

      void flush();


      virtual void full_load(const char * psz);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual void * get_internal_data();
      virtual ::primitive::memory_size get_internal_data_size();
      virtual bool set_internal_data_size(::primitive::memory_size c);

      virtual void transfer_to(writer & writer, ::primitive::memory_size uiBufferSize = 1024 * 1024);

      
   };


} // namespace primitive


