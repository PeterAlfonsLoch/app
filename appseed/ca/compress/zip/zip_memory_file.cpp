#include "framework.h"


namespace zip
{

   memory_file::memory_file(::ca::application * papp) :
      ::gen::memory_file(papp),
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

   memory_file::~memory_file()
   {

   }

   voidpf memory_file::open_file_func (voidpf opaque, const char* filename, int mode)
   {
      UNREFERENCED_PARAMETER(mode);
      UNREFERENCED_PARAMETER(filename);
      memory_file * pfile = (memory_file *) opaque;
      return (voidpf) pfile;
   }

   uLong  memory_file::read_file_func (voidpf opaque, voidpf stream, void * buf, uLong size)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_file * pfile = (memory_file *) opaque;
      return (uLong) pfile->read(buf, size);
   }

   uLong  memory_file::write_file_func (voidpf opaque, voidpf stream, const void * buf, uLong size)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_file * pfile = (memory_file *) opaque;
   
      pfile->write(buf, size);
      return size;
   }

   long   memory_file::tell_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_file * pfile = (memory_file *) opaque;
      return (long) pfile->get_position();      
   }

   long   memory_file::seek_file_func (voidpf opaque, voidpf stream, uLong offset, int origin)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_file * pfile = (memory_file *) opaque;
      if(pfile->seek(offset, (::ex1::e_seek) origin) == 0xffffffff)
         return -1;
      else
         return 0;
   }

   int    memory_file::close_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(opaque);
      UNREFERENCED_PARAMETER(stream);
//      memory_file * pfile = (memory_file *) opaque;
      return 1;
   }

   int memory_file::testerror_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(stream);
      memory_file * pfile = (memory_file *) opaque;
      return pfile->IsValid() ? 0 : 1;
   }

} // namespace zip
