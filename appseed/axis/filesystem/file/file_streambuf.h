#pragma once


namespace file
{


   class CLASS_DECL_AXIS streambuf:
      virtual public ::file::stream_buffer
   {
   public:


      _FILE *        m_pfile;


      streambuf();
      virtual ~streambuf();


      virtual file_position get_position() const;
      virtual bool GetStatus(file_status& rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      //virtual void SetFilePath(const char * lpszNewName);


      virtual bool open(const char * lpszFileName,UINT nOpenFlags);

      virtual bool GetStatus(const char * lpszFileName,file_status& rStatus);
      virtual void SetStatus(const char * lpszFileName,const file_status& status);


      virtual ::file::buffer_sp  Duplicate() const;

      virtual file_position seek(file_offset lOff,::file::e_seek  nFrom);
      virtual void set_length(file_size dwNewLen);
      virtual file_size get_length() const;

      virtual void LockRange(file_position dwPos,file_size dwCount);
      virtual void UnlockRange(file_position dwPos,file_size dwCount);

      virtual void Abort();
      virtual void flush();
      virtual void close();


      virtual ::primitive::memory_size read(void *lpBuf,::primitive::memory_size nCount);
      virtual void write(const void * lpBuf,::primitive::memory_size nCount);
      virtual string get_location() const;


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool IsOpened();
      virtual bool is_open();
      virtual uint64_t GetBufferPtr(UINT nCommand,uint64_t nCount = 0,void ** ppBufStart = NULL,void ** ppBufMax = NULL);


      /*using ::file::writer::write;
      void write(output_stream & ostream);


      using ::file::reader::read;
      void read(input_stream & istream);*/


      /*virtual bool read(char * pch);
      virtual bool read(uchar * puch);
      virtual bool peek(char * pch);
      virtual bool peek(uchar * puch);
      virtual bool read(char & ch);
      virtual bool read(uchar & uch);
      virtual bool peek(char & ch);
      virtual bool peek(uchar & uch);
      virtual int sgetc();
      virtual int sbumpc();
      virtual bool read_string(string & str);
      virtual bool full_read_string(string & str);*/


      //void writef(const char *format,...);

      /** Common interface for write used by Tcp and Udp sockets. */
      //      virtual void write(const void *, primitive::memory_size c);

      /** Common interface for Send used by Tcp and Udp sockets. */
      //virtual void write(const string &);



   };



} // namespace file






