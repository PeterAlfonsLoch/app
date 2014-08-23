#pragma once


#include "ioapi.h"


namespace zip
{

   class CLASS_DECL_BASE memory_buffer :
      public ::file::memory_buffer

   {
   public:


      zlib_filefunc_def_s m_filefuncdef;


      memory_buffer(sp(::aura::application) papp);
      memory_buffer(sp(::aura::application) papp, ::primitive::memory_base * pmemory);
      virtual ~memory_buffer();


      void common_construct();



   };


} // namespace zip



BEGIN_EXTERN_C

voidpf      c_zip_memory_buffer_open_file_func        (voidpf opaque, const char* filename, int32_t mode);
uint_ptr    c_zip_memory_buffer_read_file_func        (voidpf opaque, voidpf stream, void * buf, uint_ptr size);
uint_ptr    c_zip_memory_buffer_write_file_func       (voidpf opaque, voidpf stream, const void * buf, uint_ptr size);
long        c_zip_memory_buffer_tell_file_func        (voidpf opaque, voidpf stream);
long        c_zip_memory_buffer_seek_file_func        (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin);
int32_t     c_zip_memory_buffer_close_file_func       (voidpf opaque, voidpf stream);
int32_t     c_zip_memory_buffer_testerror_file_func   (voidpf opaque, voidpf stream);

END_EXTERN_C
