#pragma once

#include "ioapi.h"
#include "unzip.h"



namespace zip
{

   class CLASS_DECL_ca2 File : 
      virtual public object
   {
   public:
      ::file::binary_buffer_sp              m_pfile;
      ::file::binary_buffer_sp              m_pbuffile1;
      ::file::binary_buffer_sp              m_pbuffile2;
      unzFile                    m_pfUnzip;
      zipFile                    m_pfZip;
      zlib_filefunc_def_s        m_filefuncdef;
      bool                       m_bOwnFile;

      File(sp(base_application) papp);
      virtual ~File();
      static voidpf     open_file_func (voidpf opaque, const char* filename, int32_t mode);
      static uint_ptr      read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size);
      static uint_ptr      write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size);
      static long       tell_file_func (voidpf opaque, voidpf stream);
      static long       seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin);
      static int32_t        close_file_func (voidpf opaque, voidpf stream);
      static int32_t        testerror_file_func (voidpf opaque, voidpf stream);

      void write_to_file(sp(::file::binary_buffer) pfile, const wchar_t * lpcsz);

      bool unzip_open(const char * lpcwsz);
      bool unzip_open(::file::binary_buffer_sp pfile);

      bool zip_open(const char * lpcwsz);
      bool zip_open(::file::binary_buffer_sp pfile);

   };

} // namespace zip
