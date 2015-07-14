//#include "framework.h"
#ifdef WINDOWSEX
//#include "aura/node/windows/windows.h"
#endif


namespace fs
{


   native::native(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp),
      ::fs::data(papp)
   {

   }


   // optional if ls_dir is implemented
   bool native::has_subdir(const ::file::path & path)
   {

      return System.dir().has_subdir(get_app(), path);

   }


   ::file::listing & native::ls(::file::listing & listing)
   {

      System.dir().ls(get_app(), listing);

      return listing;

   }


   bool native::is_dir(const ::file::path & pszPath)
   {

      return System.dir().is(pszPath, get_app());

   }


   ::file::listing & native::root_ones(::file::listing & listing)
   {

      System.dir().root_ones(listing, get_app());

      
#ifdef WINDOWSEX

      ::file::path strDesktopFolder;

      ::windows::SHGetSpecialFolderPath(
         NULL,
         strDesktopFolder,
         CSIDL_DESKTOP,
         FALSE);

      ::file::path & path = listing.insert_at(0,strDesktopFolder);
      path.m_iDir = 1;
      listing.m_straTitle.insert_at(0,unitext("Área de Trabalho"));
      
#endif
      
      return listing;

   }


   //void native::get_ascendants_path(const ::file::path & pszPath,::file::patha & stra)
   //{

   //   return System.file().get_ascendants_path(pszPath, stra);

   //}


   //void native::get_ascendants_name(const ::file::path & lpcsz,::file::patha & straParam)
   //{

   //   return System.file().get_ascendants_name(lpcsz, straParam);

   //}


   //string native::eat_end_level(const char * pszPath, int32_t iCount)
   //{

   //   string strPath(pszPath);

   //   while(iCount > 0)
   //   {

   //      strPath = System.dir().name(strPath);

   //      iCount--;

   //   }

   //   return strPath;

   //}


   //string native::file_name(const char * pszPath)
   //{

   //   return System.file().name_(pszPath);

   //}


   //string native::dir_path(const char * psz1, const char * psz2)
   //{

   //   return ::file::path(psz1) / ::file::path(psz2);

   //}


   bool native::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {

      Application.file().move(pszDst, pszSrc);

      return true;

   }


   ::file::buffer_sp native::get_file(const ::file::path & path,UINT nOpenFlags,cres * pfesp)
   {

      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      ::cres cres;

      ::file::binary_buffer_sp spfile(allocer());

      // ::file::mode_read | ::file::share_deny_none | ::file::type_binary
      cres  = spfile->open(path,nOpenFlags);

      if(!cres)
      {

         spfile.release();

         if(pfesp != NULL)
         {


            *pfesp = cres;

         }

      }

      return spfile;

   }


   bool native::file_exists(const ::file::path & path)
   {

      return Application.file().exists(path);

   }


} // namespace fs



