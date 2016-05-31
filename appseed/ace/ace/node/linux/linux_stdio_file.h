#pragma once


/////////////////////////////////////////////////////////////////////////////
// STDIO file implementation


namespace linux
{


   class stdio_file :
      virtual public ::linux::file,
      virtual public ::file::text_buffer
   {
   public:


      FILE* m_pStream;    // stdio FILE
      // m_hFile from ace class is _fileno(m_pStream)



      stdio_file(sp(::ace::application) papp);
      virtual ~stdio_file();

      virtual void write_string(const char * lpsz);
      virtual char * read_string(char * lpsz, UINT nMax);
      virtual bool read_string(string & rString);


      void dump(dump_context & dumpcontext) const;
      virtual file_position_t get_position() const;
      virtual cres open(const ::file::path & lpszFileName, UINT nOpenFlags);
      virtual memory_size_t read(void * lpBuf, memory_size_t nCount);
      virtual void write(const void * lpBuf, memory_size_t nCount);
      virtual file_position_t seek(file_offset_t lOff, ::file::e_seek nFrom);
      virtual void Abort();
      virtual void Flush();
      virtual void close();
      virtual file_size_t get_length() const;

      // Unsupported APIs
      virtual sp(::file::stream_buffer) Duplicate() const;
      virtual void LockRange(file_position_t dwPos, file_size_t dwCount);
      virtual void UnlockRange(file_position_t dwPos, file_size_t dwCount);


   };



} // namespace linux


