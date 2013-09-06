#include "framework.h"


namespace zip
{

   memory_buffer::memory_buffer(sp(base_application) papp) :
      ::::file::memory_buffer(papp),
      ::primitive::memory_container(papp)
   {
      m_filefuncdef.opaque = (voidpf) this;
      m_filefuncdef.zopen_file   = open_file_func;
      m_filefuncdef.zread_file   = read_file_func;
      m_filefuncdef.zwrite_file  = write_file_func;
      m_filefuncdef.ztell_file   = tell_file_func;
      m_filefuncdef.zseek_file   = seek_file_func;
      m_filefuncdef.zclose_file  = close_file_func;
      m_filefuncdef.zerror_file  = testerror_file_func;

   }

   memory_buffer::~memory_buffer()
   {

   }

   voidpf memory_buffer::open_file_func (voidpf opaque, const char* filename, int32_t mode)
   {
      UNREFERENCED_PARAMETER(mode);
      UNREFERENCED_PARAMETER(filename);
      memory_buffer * pfile = (memory_buffer *) opaque;
      return (voidpf) pfile;
   }

   uint_ptr  memory_buffer::read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_buffer * pfile = (memory_buffer *) opaque;
      return (uint_ptr) pfile->read(buf, size);
   }

   uint_ptr  memory_buffer::write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_buffer * pfile = (memory_buffer *) opaque;
   
      pfile->write(buf, size);
      return size;
   }

   long   memory_buffer::tell_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_buffer * pfile = (memory_buffer *) opaque;
      return (long) pfile->get_position();      
   }

   long   memory_buffer::seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_buffer * pfile = (memory_buffer *) opaque;
      if(pfile->seek(offset, (::file::e_seek) origin) == 0xffffffff)
         return -1;
      else
         return 0;
   }

   int32_t    memory_buffer::close_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(opaque);
      UNREFERENCED_PARAMETER(stream);
//      memory_buffer * pfile = (memory_buffer *) opaque;
      return 1;
   }

   int32_t memory_buffer::testerror_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_buffer * pfile = (memory_buffer *) opaque;
      return pfile->IsValid() ? 0 : 1;
   }

} // namespace zip
