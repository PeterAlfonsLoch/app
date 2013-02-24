#pragma once


namespace gen
{

   class file_exception;
   struct file_status;


   class CLASS_DECL_ca file :
      virtual public ::gen::stream,
      virtual public ::gen::output_stream_flush_interface
   {
   public:





      file();

      operator HFILE() const;

      virtual file_position get_position() const;
      virtual bool GetStatus(file_status& rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * lpszNewName);

      
   // Operations
      virtual bool open(const char * lpszFileName, UINT nOpenFlags);

      //virtual void Rename(const char * lpszOldName, const char * lpszNewName);
      //virtual void remove(const char * lpszFileName);
      virtual bool GetStatus(const char * lpszFileName, file_status& rStatus);
      virtual void SetStatus(const char * lpszFileName, const file_status& status);


   // Overridables
      virtual file* Duplicate() const;

      virtual file_position seek(file_offset lOff, ::gen::e_seek  nFrom);
      virtual void set_length(file_size dwNewLen);
      virtual file_size get_length() const;

      virtual void LockRange(file_position dwPos, file_size dwCount);
      virtual void UnlockRange(file_position dwPos, file_size dwCount);

      virtual void Abort();
      virtual void flush();
      virtual void close();


      // io_stream
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual string get_location() const;

      virtual bool read(char * pch);
      virtual bool read(uchar * pch);

      virtual bool read(char & pch);
      virtual bool read(uchar & pch);

      virtual bool peek(char * pch);
      virtual bool peek(uchar * pch);

      virtual bool peek(char & pch);
      virtual bool peek(uchar & pch);

   // Implementation
   public:
      virtual bool IsOpened();
      virtual ~file();
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);
   public:



      using ::gen::reader::write;
      using ::gen::writer::write;
      void write(byte_output_stream & ostream);


      using ::gen::writer::read;
      using ::gen::reader::read;
      void read(byte_input_stream & istream);



   };

   typedef ca::smart_pointer < file > filesp;

   // gen::filesp
   inline file::operator HFILE() const
      { return NULL; }
   inline void file::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }



} // namespace gen






