#include "framework.h"


namespace zip
{

   memory_buffer::memory_buffer(sp(::base::application) papp) :
      element(papp),
      ::file::memory_buffer(papp),
      ::primitive::memory_container(papp)
   {

      common_construct();

   }

   memory_buffer::memory_buffer(sp(::base::application) papp, ::primitive::memory_base * pmemory) :
      element(papp),
      ::file::memory_buffer(papp, pmemory),
      ::primitive::memory_container(papp, pmemory)
   {

      common_construct();

   }


   void memory_buffer::common_construct()
   {

      m_filefuncdef.opaque = (voidpf) this;
      m_filefuncdef.zopen_file   = &c_zip_memory_buffer_open_file_func;
      m_filefuncdef.zread_file   = &c_zip_memory_buffer_read_file_func;
      m_filefuncdef.zwrite_file  = &c_zip_memory_buffer_write_file_func;
      m_filefuncdef.ztell_file   = &c_zip_memory_buffer_tell_file_func;
      m_filefuncdef.zseek_file   = &c_zip_memory_buffer_seek_file_func;
      m_filefuncdef.zclose_file  = &c_zip_memory_buffer_close_file_func;
      m_filefuncdef.zerror_file  = &c_zip_memory_buffer_testerror_file_func;

   }


   memory_buffer::~memory_buffer()
   {

   }


} // namespace zip



BEGIN_EXTERN_C

voidpf c_zip_memory_buffer_open_file_func (voidpf opaque, const char* filename, int32_t mode)
{
   UNREFERENCED_PARAMETER(mode);
   UNREFERENCED_PARAMETER(filename);
   ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;
   return (voidpf) pfile;
}

uint_ptr  c_zip_memory_buffer_read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;
   return (uint_ptr) pfile->read(buf, size);
}

uint_ptr  c_zip_memory_buffer_write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;

   pfile->write(buf, size);
   return size;
}

long   c_zip_memory_buffer_tell_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;
   return (long) pfile->get_position();
}

long   c_zip_memory_buffer_seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;
   if(pfile->seek(offset, (::file::e_seek) origin) == 0xffffffff)
      return -1;
   else
      return 0;
}

int32_t    c_zip_memory_buffer_close_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(opaque);
   UNREFERENCED_PARAMETER(stream);
//      ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;
   return 1;
}

int32_t c_zip_memory_buffer_testerror_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::memory_buffer * pfile = (::zip::memory_buffer *) opaque;
   return pfile->IsValid() ? 0 : 1;
}

END_EXTERN_C
