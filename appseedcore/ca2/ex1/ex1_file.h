#pragma once

namespace primitive
{
   class memory;
} // namespace primitive

namespace ex1
{

   class file_exception;
   typedef ca::smart_pointer < file_exception > file_exception_sp;
   struct file_status;

   /////////////////////////////////////////////////////////////////////////////
   // ex1::filesp - raw unbuffered disk file I/O

   class CLASS_DECL_ca file :
      virtual public ::ex1::io_stream,
      virtual public ::ex1::output_stream_flush_interface
   {
   public:

      enum e_open
      {
         mode_read               = (int) 0x00000,
         mode_write              = (int) 0x00001,
         mode_read_write         = (int) 0x00002,
         shareCompat             = (int) 0x00000,
         shareExclusive          = (int) 0x00010,
         shareDenyWrite          = (int) 0x00020,
         shareDenyRead           = (int) 0x00030,
         shareDenyNone           = (int) 0x00040,
         modeNoInherit           = (int) 0x00080,
         mode_create             = (int) 0x01000,
         modeNoTruncate          = (int) 0x02000,
         type_text               = (int) 0x04000, // type_text and type_binary are used in
         type_binary             = (int) 0x08000, // derived classes only
         defer_create_directory  = (int) 0x10000,
      };



      file();

   // Attributes
   //   UINT m_hFile;
      operator HFILE() const;

      virtual DWORD_PTR GetPosition() const;
      virtual BOOL GetStatus(file_status& rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * lpszNewName);


   // Operations
      virtual BOOL open(const char * lpszFileName, UINT nOpenFlags, file_exception_sp * pError = NULL);

      //virtual void PASCAL Rename(const char * lpszOldName, const char * lpszNewName);
      //virtual void PASCAL remove(const char * lpszFileName);
      virtual BOOL PASCAL GetStatus(const char * lpszFileName, file_status& rStatus);
      virtual void PASCAL SetStatus(const char * lpszFileName, const file_status& status);

      DWORD_PTR seek_to_end();
      void seek_to_begin();

   // Overridables
      virtual file* Duplicate() const;

      virtual INT_PTR seek(INT_PTR lOff, UINT nFrom);
      virtual void SetLength(DWORD_PTR dwNewLen);
      virtual DWORD_PTR get_length() const;

      virtual void LockRange(DWORD_PTR dwPos, DWORD_PTR dwCount);
      virtual void UnlockRange(DWORD_PTR dwPos, DWORD_PTR dwCount);

      virtual void Abort();
      virtual void Flush();
      virtual void close();


      // io_stream
      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);
      virtual void write(const void * lpBuf, DWORD_PTR nCount);
      virtual string get_location() const;

      virtual bool read(char * pch);
      virtual bool read(unsigned char * pch);

      virtual bool read(char & pch);
      virtual bool read(unsigned char & pch);

      virtual bool peek(char * pch);
      virtual bool peek(unsigned char * pch);

      virtual bool peek(char & pch);
      virtual bool peek(unsigned char & pch);

   // Implementation
   public:
      virtual bool IsOpened();
      virtual ~file();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
      virtual DWORD_PTR GetBufferPtr(UINT nCommand, DWORD_PTR nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);
   public:


   // derived
      virtual void write(output_stream & ostream);
      virtual void read(input_stream & ostream);


   };

   typedef ca::smart_pointer < file > filesp;

   class CLASS_DECL_ca file_exception :
      virtual public exception
   {
   public:
      enum
      {
         none,
         generic,
         fileNotFound,
         badPath,
         tooManyOpenFiles,
         accessDenied,
         invalidFile,
         removeCurrentDir,
         directoryFull,
         badSeek,
         hardIO,
         sharingViolation,
         lockViolation,
         diskFull,
         endOfFile
      };

   // Constructor
      file_exception(const file_exception & e) :
         exception(e)
      {
      }

      file_exception(::ca::application * papp, int cause = file_exception::none, LONG lOsError = -1,
         const char * lpszArchiveName = NULL);

      virtual void Construct(int cause = file_exception::none, LONG lOsError = -1,
         const char * lpszArchiveName = NULL);

   public:
      virtual ~file_exception();

      virtual int get_cause();
      virtual LONG get_os_error();
      virtual string get_file_path();


   #ifdef _DEBUG
      virtual void dump(dump_context&) const;
   #endif
      virtual BOOL GetErrorMessage(string & str, PUINT pnHelpContext = NULL);
   };

   typedef ca::smart_pointer < file_exception > file_exception_sp;

   // ex1::filesp
   inline file::operator HFILE() const
      { return NULL; }
   inline DWORD_PTR file::seek_to_end()
      { return seek(0, seek_end); }
   inline void file::seek_to_begin()
      { seek(0, seek_begin); }
   inline void file::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ex1::filesp status

   struct file_status
   {
      class time  m_ctime;         // creation date/time of file
      class time  m_mtime;         // last modification date/time of file
      class time  m_atime;         // last access date/time of file
      INT_PTR     m_size;          // logical size of file in bytes
      BYTE        m_attribute;     // logical OR of ex1::filesp::Attribute enum values
      BYTE        m_padding;       // pad the structure to a WORD
      string      m_strFullName;   // absolute path name

   #ifdef _DEBUG
      void dump(dump_context & dumpcontext) const;
   #endif
   };

} // namespace ex1;