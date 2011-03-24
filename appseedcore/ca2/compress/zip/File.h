#pragma once

#include "ioapi.h"
#include "unzip.h"



namespace zip
{

   class CLASS_DECL_ca File : 
      virtual public ::radix::object
   {
   public:
      ::ex1::filesp              m_pfile;
      ::ex1::filesp              m_pbuffile1;
      ::ex1::filesp              m_pbuffile2;
      unzFile                    m_pf;
      zlib_filefunc_def_s        m_filefuncdef;
      bool                       m_bOwnFile;

      File(::ca::application * papp);
      virtual ~File();
      static voidpf     open_file_func (voidpf opaque, const char* filename, int mode);
      static uLong      read_file_func (voidpf opaque, voidpf stream, void * buf, uLong size);
      static uLong      write_file_func (voidpf opaque, voidpf stream, const void * buf, uLong size);
      static long       tell_file_func (voidpf opaque, voidpf stream);
      static long       seek_file_func (voidpf opaque, voidpf stream, uLong offset, int origin);
      static int        close_file_func (voidpf opaque, voidpf stream);
      static int        testerror_file_func (voidpf opaque, voidpf stream);

      void write_to_file(ex1::file * pfile, const wchar_t * lpcsz);

      bool open(const char * lpcwsz);
      bool open(ex1::filesp pfile);

   };

} // namespace zip
