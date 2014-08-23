#pragma once

#include "ioapi.h"
#include "unzip.h"



namespace zip
{


   class CLASS_DECL_BASE File :
      virtual public ::object
   {
   public:
      ::file::binary_buffer_sp              m_pfile;
      ::file::binary_buffer_sp              m_pbuffile1;
      ::file::binary_buffer_sp              m_pbuffile2;
      unzFile                    m_pfUnzip;
      zipFile                    m_pfZip;
      zlib_filefunc_def_s        m_filefuncdef;
      bool                       m_bOwnFile;

      File(sp(::aura::application) papp);
      virtual ~File();



      void write_to_file(::file::buffer_sp  pfile, const wchar_t * lpcsz);

      bool unzip_open(const char * lpcwsz);
      bool unzip_open(::file::binary_buffer_sp pfile);

      bool zip_open(const char * lpcwsz);
      bool zip_open(::file::binary_buffer_sp pfile);

   };

} // namespace zip


BEGIN_EXTERN_C

voidpf         c_zip_file_open_file_func        (voidpf opaque, const char* filename, int32_t mode);
uint_ptr       c_zip_file_read_file_func        (voidpf opaque, voidpf stream, void * buf, uint_ptr size);
uint_ptr       c_zip_file_write_file_func       (voidpf opaque, voidpf stream, const void * buf, uint_ptr size);
long           c_zip_file_tell_file_func        (voidpf opaque, voidpf stream);
long           c_zip_file_seek_file_func        (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin);
int32_t        c_zip_file_close_file_func       (voidpf opaque, voidpf stream);
int32_t        c_zip_file_testerror_file_func   (voidpf opaque, voidpf stream);

END_EXTERN_C
