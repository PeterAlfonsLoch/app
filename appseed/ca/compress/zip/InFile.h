#pragma once


#ifdef LINUX


namespace ex1
{


    class file;


} // namespace ex1



typedef ::ex1::file * HFILE;


#endif


namespace zip
{

   class File;

   class CLASS_DECL_ca InFile :
      public ex1::file
   {
   public:

      enum e_mode
      {
         mode_undefined,
         mode_zip,
         mode_unzip,
      };

      unz_file_info                       m_fi;
      BOOL                                m_bCloseOnDelete;
      string                              m_strFileName;
      uint64_t                            m_iPosition;
      stringa                             m_straPath;
      array_del_ptr < File, File & >      m_filea;
      array_del_ptr < InFile, InFile & >  m_izfilea;
      stringa                             m_straPrefix;
      e_mode                              m_emode;
      string                              m_strZipFile;


      InFile(::ca::application * papp);
      virtual ~InFile();



      operator HFILE() const;

      virtual file_position get_position() const;

      virtual BOOL zip_open(const char *,UINT,ex1::file_exception_sp *);
      virtual BOOL zip_open(File * pzfile, const char * lpcszFileName);

      virtual BOOL unzip_open(const char *,UINT,ex1::file_exception_sp *);
      virtual BOOL unzip_open(File * pzfile, const char * lpcszFileName);

      virtual bool locate(const char * pszFileName);

      virtual void add_file(const char * pszDir, const char * pszRelative);

      bool dump(ex1::file * pfile);

      virtual ex1::file * Duplicate() const;

      File * get_zip_file();
      const File * get_zip_file() const;

      virtual file_position seek(file_offset lOff, ::ex1::e_seek  nFrom);
      virtual void set_length(file_size dwNewLen);
      virtual file_size get_length() const;

      virtual ::primitive::memory_size read(void * lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);

      virtual void LockRange(file_position dwPos, file_size dwCount);
      virtual void UnlockRange(file_position dwPos, file_size dwCount);

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
      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);


   private:
      using ::ex1::file::open;

   };

} // namespace zip

