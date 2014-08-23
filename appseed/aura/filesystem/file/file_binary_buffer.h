#pragma once


namespace file
{


   class exception;
   struct file_status;


   class CLASS_DECL_AURA binary_buffer :
      virtual public ::file::stream_buffer
   {
   public:


      



      binary_buffer();
      virtual ~binary_buffer();

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
      virtual ::file::buffer_sp  Duplicate() const;

      virtual file_position seek(file_offset lOff, ::file::e_seek  nFrom);
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


      virtual bool IsOpened();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);



      using ::file::stream_buffer::write;
      void write(output_stream & ostream);


      using ::file::stream_buffer::read;
      void read(input_stream & istream);


      //virtual bool read_string(string & str);



   };


   typedef smart_pointer < binary_buffer > binary_buffer_sp;

   inline void binary_buffer::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }



} // namespace file






