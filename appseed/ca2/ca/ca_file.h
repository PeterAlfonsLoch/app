#pragma once


namespace ca
{

   class file_exception;
   struct file_status;


   class CLASS_DECL_ca file :
      virtual public ::ca::stream,
      virtual public ::ca::output_stream_flush_interface
   {
   public:





      file();

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
      virtual sp(::ca::file) Duplicate() const;

      virtual file_position seek(file_offset lOff, ::ca::e_seek  nFrom);
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
      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = ::null(), void ** ppBufMax = ::null());
   public:



      using ::ca::reader::write;
      using ::ca::writer::write;
      void write(byte_output_stream & ostream);


      using ::ca::writer::read;
      using ::ca::reader::read;
      void read(byte_input_stream & istream);



   };

   typedef ::ca::smart_pointer < file > filesp;

   inline void file::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }



} // namespace ca






