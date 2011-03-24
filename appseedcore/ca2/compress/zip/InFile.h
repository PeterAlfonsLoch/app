#pragma once

namespace zip
{

   class File;

   class CLASS_DECL_ca InFile :
      public ex1::file
   {
   public:

      unz_file_info                    m_fi;
      BOOL                             m_bCloseOnDelete;
      string                           m_strFileName;
      DWORD_PTR                        m_iPosition;
      stringa                          m_straPath;
      array_ptr < File, File & >       m_filea;
      array_ptr < InFile, InFile & >   m_izfilea;
      stringa                          m_straPrefix;

      InFile(::ca::application * papp);
      virtual ~InFile();



      operator HFILE() const;

      virtual DWORD_PTR GetPosition() const;

      virtual BOOL open(const char *,UINT,ex1::file_exception_sp *);
      virtual BOOL open(File * pzfile, const char * lpcszFileName);
      virtual bool locate(const char * pszFileName);

      bool dump(ex1::file * pfile);

      virtual ex1::file * Duplicate() const;

      File * get_zip_file();
      const File * get_zip_file() const;

      virtual INT_PTR seek(INT_PTR lOff, UINT nFrom);
      virtual void SetLength(DWORD_PTR dwNewLen);
      virtual DWORD_PTR get_length() const;

      virtual DWORD_PTR read(void * lpBuf, DWORD_PTR nCount);
      virtual void write(const void * lpBuf, DWORD_PTR nCount);

      virtual void LockRange(DWORD_PTR dwPos, DWORD_PTR dwCount);
      virtual void UnlockRange(DWORD_PTR dwPos, DWORD_PTR dwCount);

      virtual void Abort();
      virtual void Flush();
      virtual void close();

   // Implementation
   public:
      virtual bool IsOpened();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
      virtual DWORD_PTR GetBufferPtr(UINT nCommand, DWORD_PTR nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

   };

} // namespace zip

