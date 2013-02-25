#pragma once

#include "ioapi.h"
#include "unzip.h"



namespace zip
{

   class CLASS_DECL_ca File : 
      virtual public ::ca::object
   {
   public:
      ::ca::filesp              m_pfile;
      ::ca::filesp              m_pbuffile1;
      ::ca::filesp              m_pbuffile2;
      unzFile                    m_pfUnzip;
      zipFile                    m_pfZip;
      zlib_filefunc_def_s        m_filefuncdef;
      bool                       m_bOwnFile;

      File(::ca::application * papp);
      virtual ~File();
      static voidpf     open_file_func (voidpf opaque, const char* filename, int32_t mode);
      static uint_ptr      read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size);
      static uint_ptr      write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size);
      static long       tell_file_func (voidpf opaque, voidpf stream);
      static long       seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin);
      static int32_t        close_file_func (voidpf opaque, voidpf stream);
      static int32_t        testerror_file_func (voidpf opaque, voidpf stream);

      void write_to_file(::ca::file * pfile, const wchar_t * lpcsz);

      bool unzip_open(const char * lpcwsz);
      bool unzip_open(::ca::filesp pfile);

      bool zip_open(const char * lpcwsz);
      bool zip_open(::ca::filesp pfile);

   };

} // namespace zip
