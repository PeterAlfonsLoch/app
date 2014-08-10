#pragma once

CLASS_DECL_BASE int get_sync_io_error();
CLASS_DECL_BASE void set_sync_io_error(int iError);
CLASS_DECL_BASE int get_generate_sync_io_error();
CLASS_DECL_BASE void set_generate_sync_io_error(int iError);


class CLASS_DECL_BASE sync_io_error
{
public:

   int   m_iGenerateBefore;
   int   m_iErrorBefore;
   int * m_piError;

   sync_io_error(int * piError = NULL)
   {
      m_iGenerateBefore = get_generate_sync_io_error();
      m_iErrorBefore = get_sync_io_error();
      set_sync_io_error(0);
      set_generate_sync_io_error(1);
      m_piError = piError;
   }

   ~sync_io_error()
   {
      if(m_piError != NULL)
      {
         *m_piError = get_sync_io_error();
      }
      set_generate_sync_io_error(m_iGenerateBefore);
      set_sync_io_error(m_iGenerateBefore);
   }

   bool none() { return get_sync_io_error() == 0; }

};

namespace file
{



   class CLASS_DECL_BASE stream_buffer :
      virtual public ::file::reader,
      virtual public ::file::writer,
      virtual public ::file::seekable,
      virtual public ::file::writer_flush
   {
   public:


      stream_buffer();
      virtual ~stream_buffer();


      virtual file_position get_position() const;
      virtual file_position tell() const;
      virtual bool GetStatus(file_status& rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * lpszNewName);

      
      virtual bool open(const char * lpszFileName, UINT nOpenFlags);

      virtual bool GetStatus(const char * lpszFileName, file_status& rStatus);
      virtual void SetStatus(const char * lpszFileName, const file_status& status);


      virtual ::file::buffer_sp  Duplicate() const;

      virtual file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      virtual file_position seek_from_begin(file_position lPos);
      virtual void set_length(file_size dwNewLen);
      virtual file_size get_length() const;

      virtual void LockRange(file_position dwPos, file_size dwCount);
      virtual void UnlockRange(file_position dwPos, file_size dwCount);

      virtual void Abort();
      virtual void flush();
      virtual void close();


      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void full_read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual string get_location() const;


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool IsOpened();
      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);


      using ::file::writer::write;
      void write(output_stream & ostream);


      using ::file::reader::read;
      void read(input_stream & istream);


      virtual bool read(char * pch);
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
      virtual bool full_read_string(string & str);


      void writef(const char *format, ...);

      /** Common interface for write used by Tcp and Udp sockets. */
//      virtual void write(const void *, primitive::memory_size c);

      /** Common interface for Send used by Tcp and Udp sockets. */
      virtual void write(const string &);



   };



} // namespace file






