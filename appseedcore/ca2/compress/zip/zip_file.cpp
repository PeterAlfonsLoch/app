#include "StdAfx.h"


namespace zip
{

   File::File(::ca::application * papp) :
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
      m_pf = NULL;
   }

   File::~File()
   {
   }

   bool File::open(const char * lpcwsz)
   {
      m_bOwnFile = true;
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(lpcwsz, ::ex1::file::mode_read | ::ex1::file::type_binary))
         {
            return false;
         }
      }
      catch(ex1::exception * pe)
      {
         pe->Delete();
         return false;
      }
      catch(...)
      {
         return false;
      }
      return open(spfile);
   }

   bool File::open(ex1::filesp pfile)
   {
      m_pbuffile1(new ::ex1::buffered_file(get_app(), pfile, 1024 * 256));
      m_pbuffile2(new ::ex1::buffered_file(get_app(), m_pbuffile1, 1024 * 256));
      m_pbuffile2->seek_to_begin();
      m_pfile = m_pbuffile2;
      m_filefuncdef.opaque = (voidpf) this;
      m_pf = api::unzipOpen(this);
      return true;
   }

   void  File::write_to_file(ex1::file * pfileOut, const wchar_t * lpcsz)
   {
      string str;
      gen::international::UnicodeToACP(str, lpcsz);
      str.replace("\\", "/");
      if(unzLocateFile(m_pf, str, 1) != UNZ_OK)
         return;
      BYTE buf[1024];
      int iRead;
      if(unzOpenCurrentFile(m_pf) != UNZ_OK)
         return;

      while((iRead = unzReadCurrentFile(m_pf, buf, sizeof(buf))) > 0)
      {
         pfileOut->write(buf, iRead);
      }  
      if(unzCloseCurrentFile(m_pf) != UNZ_OK)
         return;
   }


   voidpf File::open_file_func (voidpf opaque, const char* filename, int mode)
   {
      UNREFERENCED_PARAMETER(mode);
      UNREFERENCED_PARAMETER(filename);
      File * pzipfile = (File *) opaque;
      ex1::file * pfile = pzipfile->m_pfile;
      return (voidpf) pfile;
   }
   uLong  File::read_file_func (voidpf opaque, voidpf stream, void * buf, uLong size)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      ex1::file * pfile = pzipfile->m_pfile;
      return pfile->read(buf, size);
   }
   uLong  File::write_file_func (voidpf opaque, voidpf stream, const void * buf, uLong size)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      ex1::file * pfile = pzipfile->m_pfile;
      pfile->write(buf, size);
      return size;
   }
   long   File::tell_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      ex1::file * pfile = pzipfile->m_pfile;
      return pfile->GetPosition();      
   }

   long   File::seek_file_func (voidpf opaque, voidpf stream, uLong offset, int origin)
   {
      UNREFERENCED_PARAMETER(stream);
      File * pzipfile = (File *) opaque;
      ex1::file * pfile = pzipfile->m_pfile;
      if(pfile->seek(offset, origin) == 0xffffffff)
         return -1;
      else
         return 0;

   }

   int    File::close_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(opaque);
      UNREFERENCED_PARAMETER(stream);
//      File * pzipfile = (File *) opaque;
//      ex1::file * pfile = pzipfile->m_pfile;
      return 1;
   }

   int File::testerror_file_func (voidpf opaque, voidpf stream)
   {
      UNREFERENCED_PARAMETER(opaque);
      UNREFERENCED_PARAMETER(stream);
//      File * pzipfile = (File *) opaque;
//      ex1::file * pfile = pzipfile->m_pfile;
      //return spfile->IsValid() ? 0 : 1;
      return 0;
   }

} // namespace zip