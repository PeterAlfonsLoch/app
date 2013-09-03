#pragma once

namespace primitive
{

   class CLASS_DECL_ca2 memory_file :
      virtual public ::file::file,
      virtual public primitive::memory_container
   {
   protected:

   
      ::primitive::memory_position      m_dwPosition;


   public:
   

      memory_file(sp(base_application) papp, ::primitive::memory_size iSize = 0);
      memory_file(sp(base_application) papp, void * pMemory, ::primitive::memory_size dwSize);
      memory_file(sp(base_application) papp, const memory_file & memoryfile);
      memory_file(sp(base_application) papp, memory_base * pmemory);
      virtual ~memory_file();


      virtual bool IsValid() const;
      memory_size remove_begin(void * lpBuf, ::primitive::memory_size uiCount);
      void load_string(string & str);
      using ::ca2::request_interface::create;
      void create(::primitive::memory_size iSize = -1);
      file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      file_position get_position() const;

      virtual string GetFilePath() const;

      virtual ::primitive::memory_base * create_memory();

      void set_length(file_size dwNewLen);
      file_size get_length() const;
      void Truncate(file_size iPosition);
      void clear();
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

      void flush();


      virtual void full_load(const char * psz);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;



   };




} // namespace primitive


