#pragma once


namespace metrowin
{

   /////////////////////////////////////////////////////////////////////////////
   // native_buffer - raw unbuffered disk native_buffer I/O

   class CLASS_DECL_ACE native_buffer:
      virtual public ::file::stream_buffer
   {
   public:


      enum Attribute
      {
         normal =    0x00,
         readOnly =  0x01,
         hidden =    0x02,
         system =    0x04,
         volume =    0x08,
         directory = 0x10,
         archive =   0x20
      };

      enum { hnative_bufferNull = -1 };

      bool              m_bCloseOnDelete;
      ::file::path      m_strFileName;
      StorageFile ^     m_file;
      StorageFolder ^   m_folder;
      Streams::IRandomAccessStream ^ m_stream;


      native_buffer(::ace::application * papp);
      native_buffer(::ace::application * papp,StorageFile ^ file);
      native_buffer(::ace::application * papp,const char * lpszfileName,UINT nOpenFlags);
      virtual ~native_buffer();


      operator StorageFile ^ () const;

      virtual file_position_t get_position() const;
      bool GetStatus(::file::file_status & rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * lpszNewName);

      virtual ::cres open(const ::file::path & lpszfileName,UINT nOpenFlags);

      virtual bool GetStatus(const ::file::path & lpszfileName,::file::file_status& rStatus);

      uint64_t ReadHuge(void * lpBuffer,uint64_t dwCount);
      void WriteHuge(const void * lpBuffer,uint64_t dwCount);

      virtual sp(::file::stream_buffer) Duplicate() const;

      virtual file_position_t seek(file_offset_t lOff,::file::e_seek nFrom);
      virtual void set_length(file_size_t dwNewLen);
      virtual file_size_t get_length() const;

      virtual memory_size_t read(void * lpBuf,memory_size_t nCount);
      virtual void write(const void * lpBuf,memory_size_t nCount);

      virtual void LockRange(file_position_t dwPos,file_size_t dwCount);
      virtual void UnlockRange(file_position_t dwPos,file_size_t dwCount);

      virtual void Abort();
      virtual void Flush();
      virtual void close();

      virtual bool IsOpened();
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      enum BufferCommand { bufferRead,bufferWrite,bufferCommit,bufferCheck };
      virtual uint64_t GetBufferPtr(UINT nCommand,uint64_t nCount = 0,
         void ** ppBufStart = NULL,void ** ppBufMax = NULL);

   };


} // namespace metrowin




