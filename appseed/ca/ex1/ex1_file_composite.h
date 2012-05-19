#pragma once


namespace ex1
{


   class CLASS_DECL_ca file_composite :
      virtual public ::ex1::file
   {
   public:



      ::ex1::filesp     m_spfile;


      file_composite();
      file_composite(::ex1::file * pfile);
      virtual ~file_composite();

      operator HFILE() const;

      virtual file_position get_position() const;
      virtual bool GetStatus(file_status& rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * lpszNewName);


      virtual bool open(const char * lpszFileName, UINT nOpenFlags, file_exception_sp * pError = NULL);

      //virtual void PASCAL Rename(const char * lpszOldName, const char * lpszNewName);
      //virtual void PASCAL remove(const char * lpszFileName);
      virtual bool PASCAL GetStatus(const char * lpszFileName, file_status& rStatus);
      virtual void PASCAL SetStatus(const char * lpszFileName, const file_status& status);


      virtual file* Duplicate() const;

      virtual file_position seek(file_offset lOff, ::ex1::e_seek  nFrom);
      virtual void set_length(file_size dwNewLen);
      virtual file_size get_length() const;

      virtual void LockRange(file_position dwPos, file_size dwCount);
      virtual void UnlockRange(file_position dwPos, file_size dwCount);

      virtual void Abort();
      virtual void Flush();
      virtual void close();


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual string get_location() const;

      virtual bool read(char * pch);
      virtual bool read(unsigned char * pch);

      virtual bool read(char & pch);
      virtual bool read(unsigned char & pch);

      virtual bool peek(char * pch);
      virtual bool peek(unsigned char * pch);

      virtual bool peek(char & pch);
      virtual bool peek(unsigned char & pch);

      virtual bool IsOpened();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);



      using ::ex1::reader::write;
      using ::ex1::writer::write;
      void write(byte_output_stream & ostream);


      using ::ex1::writer::read;
      using ::ex1::reader::read;
      void read(byte_input_stream & istream);



   };


} // namespace ex1


