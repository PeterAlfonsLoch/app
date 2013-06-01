#include "framework.h"


namespace zip
{

   File::File(sp(::ca::application) papp) :
      ca(papp)
   {
      m_bOwnFile                 = false;
      m_filefuncdef.opaque       = (voidpf) this;
      m_filefuncdef.zopen_file   = open_file_func;
      m_filefuncdef.zread_file   = read_file_func;
      m_filefuncdef.zwrite_file  = write_file_func;
      m_filefuncdef.ztell_file   = tell_file_func;
      m_filefuncdef.zseek_file   = seek_file_func;
      m_filefuncdef.zclose_file  = close_file_func;
      m_filefuncdef.zerror_file  = testerror_file_func;
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

      ::ca::filesp spfile(allocer());

      try
      {
         if(!spfile->open(lpcwsz, ::ca::file::mode_read | ::ca::file::type_binary))
         {
            return false;
         }
      }
      catch(::ca::exception * pe)
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

   bool File::unzip_open(::ca::filesp pfile)
   {
      m_pbuffile1 = new ::ca::buffered_file(get_app(), pfile, 1024 * 256);
      m_pbuffile2 = new ::ca::buffered_file(get_app(), m_pbuffile1, 1024 * 256);
      m_pbuffile2->seek_to_begin();
      m_pfile = m_pbuffile2;
      m_filefuncdef.opaque = (voidpf) this;
      m_pfUnzip = api::unzipOpen(this);
      return true;
   }

   bool File::zip_open(const char * lpcwsz)
   {
      m_bOwnFile = true;
      ::ca::filesp spfile(allocer());
      try
      {
         if(!spfile->open(lpcwsz, ::ca::file::mode_read_write | ::ca::file::type_binary | ::ca::file::mode_create | ::ca::file::defer_create_directory))
         {
            return false;
         }
      }
      catch(::ca::exception * pe)
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

   bool File::zip_open(::ca::filesp pfile)
   {
      m_pbuffile1 = new ::ca::buffered_file(get_app(), pfile, 1024 * 256);
      m_pbuffile2 = new ::ca::buffered_file(get_app(), m_pbuffile1, 1024 * 256);
      m_pbuffile2->seek_to_begin();
      m_pfile = m_pbuffile2;
      m_filefuncdef.opaque = (voidpf) this;
      m_pfZip = api::zipOpen(this);
      return true;
   }

   void  File::write_to_file(sp(::ca::file) pfileOut, const wchar_t * lpcsz)
   {
      string str;
      ::ca::international::unicode_to_utf8(str, lpcsz);
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


   voidpf File::open_file_func (voidpf opaque, const char* filename, int32_t mode)
   {
      UNREFERENCED_PARAMETER(mode);
      UNREFERENCED_PARAMETER(filename);
      File * pzipfile = (File *) opaque;
      sp(::ca::file) pfile = pzipfile->m_pfile;
      return (voidpf) pfile;
   }
   uint_ptr  File::read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      sp(::ca::file) pfile = pzipfile->m_pfile;
      return (uint_ptr) pfile->read(buf, size);
   }
   uint_ptr  File::write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      sp(::ca::file) pfile = pzipfile->m_pfile;
      pfile->write(buf, size);
      return size;
   }
   long   File::tell_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      sp(::ca::file) pfile = pzipfile->m_pfile;
      return (long) pfile->get_position();
   }

   long   File::seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      sp(::ca::file) pfile = pzipfile->m_pfile;
      if(pfile->seek(offset, (::ca::e_seek) origin) == 0xffffffff)
         return -1;
      else
         return 0;

   }

   int32_t    File::close_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(opaque);
      UNREFERENCED_PARAMETER(stream);
//      File * pzipfile = (File *) opaque;
//      sp(::ca::file) pfile = pzipfile->m_pfile;
      return 1;
   }

   int32_t File::testerror_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(opaque);
      UNREFERENCED_PARAMETER(stream);
//      File * pzipfile = (File *) opaque;
//      sp(::ca::file) pfile = pzipfile->m_pfile;
      //return spfile->IsValid() ? 0 : 1;
      return 0;
   }

} // namespace zip
