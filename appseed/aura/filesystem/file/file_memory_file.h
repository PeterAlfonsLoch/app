#pragma once


class memory_file;

   
typedef sp(memory_file) memory_file_sp;


class CLASS_DECL_AURA memory_file :
   virtual public ::file::file,
   virtual public primitive::memory_container
{
protected:

   
   memory_position_t      m_dwPosition;


public:
   
   memory_file(const memory_file & file);
   memory_file(memory_file && file);
   memory_file(::aura::application * papp, memory_size_t iSize = 0);
   memory_file(::aura::application * papp, void * pMemory, memory_size_t dwSize);
   memory_file(::aura::application * papp, const memory_file & memoryfile);
   memory_file(::aura::application * papp, ::primitive::memory_base * pmemory);
   virtual ~memory_file();


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
      
   using ::file::file::read;
   virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      
   using ::file::file::write;
   virtual void write(const void * lpBuf, memory_size_t nCount);
   virtual void write_from_hex(const void * lpBuf,memory_size_t nCount);

   virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

   void flush();


   virtual void full_load(var varFile);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   using ::file::file::get_internal_data;
   virtual void * get_internal_data();
   virtual memory_size_t get_internal_data_size() const;
   virtual bool set_internal_data_size(memory_size_t c);

   virtual void transfer_to(writer & writer, memory_size_t uiBufferSize = 1024 * 1024);

   void copy_this(const memory_file & file);

   memory_file & operator = (const memory_file & file);
      
};


