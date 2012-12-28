#pragma once

#include "ioapi.h"

namespace zip
{

   class CLASS_DECL_ca memory_file :
      public ::gen::memory_file

   {
   public:
      memory_file(::ca::application * papp);
      virtual ~memory_file();
      static voidpf open_file_func (voidpf opaque, const char* filename, int32_t mode);
      static uLong  read_file_func (voidpf opaque, voidpf stream, void * buf, uLong size);
      static uLong  write_file_func (voidpf opaque, voidpf stream, const void * buf, uLong size);
      static long   tell_file_func (voidpf opaque, voidpf stream);
      static long   seek_file_func (voidpf opaque, voidpf stream, uLong offset, int32_t origin);
      static int32_t    close_file_func (voidpf opaque, voidpf stream);
      static int32_t testerror_file_func (voidpf opaque, voidpf stream);

   public:
      zlib_filefunc_def_s m_filefuncdef;
   };

} // namespace zip