#pragma once


class FileException;
struct FileStatus;


void CLASS_DECL_AURA vfxGetRoot(const unichar * lpszPath, string& wstrRoot);
void CLASS_DECL_AURA vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath);


/////////////////////////////////////////////////////////////////////////////
// File - raw unbuffered disk file I/O


namespace android
{


   class CLASS_DECL_AURA file :
      virtual public ::file::binary_buffer
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

      enum
      {

         hFileNull = -1

      };

      enum BufferCommand
      {

         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };

      ::file::path   m_strFileName;
      int32_t        m_iFile;


      file(::ace::application * papp);
      file(::ace::application * papp, int32_t hFile);
      file(::ace::application * papp, const char * lpszFileName, UINT nOpenFlags);
      virtual ~file();


      virtual file_position_t get_position() const;


      bool GetStatus(::file::file_status & rStatus) const;
      virtual string GetFileName() const;
      virtual string GetFileTitle() const;
      virtual string GetFilePath() const;
      virtual void SetFilePath(const char * lpszNewName);

      virtual cres open(const ::file::path & lpszFileName, UINT nOpenFlags);

      virtual bool PASCAL GetStatus(const char * lpszFileName, ::file::file_status& rStatus);

      uint64_t ReadHuge(void * lpBuffer, uint64_t dwCount);
      void WriteHuge(const void * lpBuffer, uint64_t dwCount);

      virtual ::file::buffer_sp Duplicate() const;

      virtual file_position_t seek(file_offset_t lOff, ::file::e_seek nFrom);
      virtual void set_length(file_size_t dwNewLen);
      virtual file_size_t get_length() const;

      virtual memory_size_t read(void * lpBuf, memory_size_t nCount);
      virtual void write(const void * lpBuf, memory_size_t nCount);

      virtual void LockRange(file_position_t dwPos, file_size_t dwCount);
      virtual void UnlockRange(file_position_t dwPos, file_size_t dwCount);

      virtual void Abort();
      virtual void Flush();
      virtual void close();

      virtual bool IsOpened();
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);


   };


   namespace file_exception
   {


      ::file::exception::e_cause PASCAL OsErrorToException(LONG lOsError);
      ::file::exception::e_cause PASCAL ErrnoToException(int32_t nErrno);
      void PASCAL ThrowOsError(::ace::application * papp, LONG lOsError, const char * lpszFileName = NULL);
      void PASCAL ThrowErrno(::ace::application * papp, int32_t nErrno, const char * lpszFileName = NULL);


   }  // namespace file_exception


} // namepsace android




bool CLASS_DECL_AURA vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath);



