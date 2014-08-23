#include "framework.h"


namespace zip
{

   File::File(sp(::aura::application) papp) :
      element(papp)
   {
      m_bOwnFile                 = false;
      m_filefuncdef.opaque       = (voidpf) this;
      m_filefuncdef.zopen_file   = &c_zip_file_open_file_func;
      m_filefuncdef.zread_file   = &c_zip_file_read_file_func;
      m_filefuncdef.zwrite_file  = &c_zip_file_write_file_func;
      m_filefuncdef.ztell_file   = &c_zip_file_tell_file_func;
      m_filefuncdef.zseek_file   = &c_zip_file_seek_file_func;
      m_filefuncdef.zclose_file  = &c_zip_file_close_file_func;
      m_filefuncdef.zerror_file  = &c_zip_file_testerror_file_func;
      m_pfUnzip = NULL;
      m_pfZip = NULL;
   }

   File::~File()
   {
      if(m_pfUnzip != NULL)
      {
         unzClose(m_pfUnzip);
      }
      if(m_pfZip != NULL)
      {
         zipClose(m_pfZip, NULL);
      }
   }

   bool File::unzip_open(const char * lpcwsz)
   {

      m_bOwnFile = true;

      ::file::binary_buffer_sp spfile(allocer());

      try
      {
         if(!spfile->open(lpcwsz, ::file::mode_read | ::file::type_binary))
         {
            return false;
         }
      }
      catch(exception::exception * pe)
      {
         pe->Delete();
         return false;
      }
      catch(...)
      {
         return false;
      }
      return unzip_open(spfile);
   }

   bool File::unzip_open(::file::binary_buffer_sp pfile)
   {
      m_pbuffile1 = new ::file::buffered_buffer(get_app(), pfile, 1024 * 256);
      m_pbuffile2 = new ::file::buffered_buffer(get_app(), m_pbuffile1, 1024 * 256);
      m_pbuffile2->seek_to_begin();
      m_pfile = m_pbuffile2;
      m_filefuncdef.opaque = (voidpf) this;
      m_pfUnzip = api::unzipOpen(this);
      return true;
   }

   bool File::zip_open(const char * lpcwsz)
   {
      m_bOwnFile = true;
      ::file::binary_buffer_sp spfile(allocer());
      try
      {
         if(!spfile->open(lpcwsz, ::file::mode_read_write | ::file::type_binary | ::file::mode_create | ::file::defer_create_directory))
         {
            return false;
         }
      }
      catch(exception::exception * pe)
      {
         pe->Delete();
         return false;
      }
      catch(...)
      {
         return false;
      }
      return zip_open(spfile);
   }

   bool File::zip_open(::file::binary_buffer_sp pfile)
   {
      m_pbuffile1 = new ::file::buffered_buffer(get_app(), pfile, 1024 * 256);
      m_pbuffile2 = new ::file::buffered_buffer(get_app(), m_pbuffile1, 1024 * 256);
      m_pbuffile2->seek_to_begin();
      m_pfile = m_pbuffile2;
      m_filefuncdef.opaque = (voidpf) this;
      m_pfZip = api::zipOpen(this);
      return true;
   }

   void  File::write_to_file(::file::buffer_sp  pfileOut, const wchar_t * lpcsz)
   {
      string str;
      ::str::international::unicode_to_utf8(str, lpcsz);
      str.replace("\\", "/");
      if(unzLocateFile(m_pfUnzip, str, 1) != UNZ_OK)
         return;
      BYTE buf[1024];
      int32_t iRead;
      if(unzOpenCurrentFile(m_pfUnzip) != UNZ_OK)
         return;

      while((iRead = unzReadCurrentFile(m_pfUnzip, buf, sizeof(buf))) > 0)
      {
         pfileOut->write(buf, iRead);
      }
      if(unzCloseCurrentFile(m_pfUnzip) != UNZ_OK)
         return;
   }


} // namespace zip


BEGIN_EXTERN_C


voidpf c_zip_file_open_file_func (voidpf opaque, const char* filename, int32_t mode)
{
   UNREFERENCED_PARAMETER(mode);
   UNREFERENCED_PARAMETER(filename);
   ::zip::File * pzipfile = (::zip::File *) opaque;
   ::file::buffer_sp  pfile = pzipfile->m_pfile;
   return (voidpf) pfile;
}
uint_ptr  c_zip_file_read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::File * pzipfile = (::zip::File *) opaque;
   ::file::buffer_sp  pfile = pzipfile->m_pfile;
   return (uint_ptr) pfile->read(buf, size);
}
uint_ptr  c_zip_file_write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::File * pzipfile = (::zip::File *) opaque;
   ::file::buffer_sp  pfile = pzipfile->m_pfile;
   pfile->write(buf, size);
   return size;
}
long   c_zip_file_tell_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::File * pzipfile = (::zip::File *) opaque;
   ::file::buffer_sp  pfile = pzipfile->m_pfile;
   return (long) pfile->get_position();
}

long   c_zip_file_seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin)
{
   UNREFERENCED_PARAMETER(stream);
   ::zip::File * pzipfile = (::zip::File *) opaque;
   ::file::buffer_sp  pfile = pzipfile->m_pfile;
   if(pfile->seek(offset, (::file::e_seek) origin) == 0xffffffff)
      return -1;
   else
      return 0;

}

int32_t    c_zip_file_close_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(opaque);
   UNREFERENCED_PARAMETER(stream);
//      ::zip::File * pzipfile = (::zip::File *) opaque;
//      ::file::buffer_sp  pfile = pzipfile->m_pfile;
   return 1;
}

int32_t c_zip_file_testerror_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(opaque);
   UNREFERENCED_PARAMETER(stream);
//      ::zip::File * pzipfile = (::zip::File *) opaque;
//      ::file::buffer_sp  pfile = pzipfile->m_pfile;
   //return spfile->IsValid() ? 0 : 1;
   return 0;
}

END_EXTERN_C

