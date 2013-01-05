#pragma once

namespace primitive
{

   class CLASS_DECL_ca memory_file :
      virtual public ex1::file,
      virtual public primitive::memory_container
   {
   protected:

   
      ::primitive::memory_position      m_dwPosition;


   public:
   

      memory_file(::ca::application * papp, ::primitive::memory_size iSize = 0);
      memory_file(::ca::application * papp, void * pMemory, ::primitive::memory_size dwSize);
      memory_file(::ca::application * papp, const memory_file & memoryfile);
      memory_file(::ca::application * papp, memory_base * pmemory);
      virtual ~memory_file();


      virtual bool IsValid() const;
      memory_size remove_begin(void * lpBuf, ::primitive::memory_size uiCount);
      void load_string(string & str);
      using ::ex1::request_interface::create;
      void create(::primitive::memory_size iSize = -1);
      file_position seek(file_offset lOff, ::ex1::e_seek  nFrom);
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


