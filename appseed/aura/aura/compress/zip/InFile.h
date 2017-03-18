#pragma once


namespace file
{


   class file;


} // namespace file


namespace zip
{


   class File;

   class CLASS_DECL_AURA InFile:
      public ::file::binary_file,
      virtual public ::file::listing_provider
   {
   public:

      enum e_mode
      {

         mode_undefined,
         mode_zip,
         mode_unzip

      };

      enum BufferCommand
      {
         
         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };


      unz_file_info m_fi;
      string m_strFileName;
      uint64_t m_iPosition;
      stringa m_straPath;
      spa(File) m_filea;
      spa(InFile) m_izfilea;
      stringa m_straPrefix;
      e_mode m_emode;
      string m_strZipFile;


      InFile(::aura::application * papp);
      virtual ~InFile();



      //      operator HFILE() const;

      virtual file_position_t get_position() const;

      virtual bool zip_open(const char *,UINT);
      virtual bool zip_open(File * pzfile,const char * lpcszFileName);

      virtual bool unzip_open(::file::file_sp pfile);
      virtual bool unzip_open(const char *,UINT);
      virtual bool unzip_open(File * pzfile,const char * lpcszFileName);

      virtual bool locate(const char * pszFileName);

      virtual void add_file(const ::file::path & pszDir,const ::file::path & pszRelative);

      bool dump(::file::file_sp pfile);

      virtual ::file::file_sp Duplicate() const;

      File * get_zip_file();
      const File * get_zip_file() const;

      virtual file_position_t seek(file_offset_t lOff,::file::e_seek nFrom);
      virtual void set_length(file_size_t dwNewLen);
      virtual file_size_t get_length() const;

      using ::file::file::read;
      virtual memory_size_t read(void * lpBuf,memory_size_t nCount);

      using ::file::file::write;
      virtual void write(const void * lpBuf,memory_size_t nCount);

      virtual void LockRange(file_position_t dwPos,file_size_t dwCount);
      virtual void UnlockRange(file_position_t dwPos,file_size_t dwCount);

      virtual void Abort();
      virtual void flush();
      virtual void close();

      virtual ::file::listing & ls(::file::listing & listing);

      virtual bool IsOpened();
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual uint64_t GetBufferPtr(UINT nCommand,uint64_t nCount = 0,void ** ppBufStart = NULL,void ** ppBufMax = NULL);

      virtual ::file::listing & perform_file_listing(::file::listing & listing);

   private:

      using ::file::binary_file::open;

   };


} // namespace zip











