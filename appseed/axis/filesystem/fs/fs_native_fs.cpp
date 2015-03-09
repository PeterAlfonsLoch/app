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
   bool native::has_subdir(const char * pszPath)
   {

      return System.dir().has_subdir(get_app(), pszPath);

   }


   bool native::ls(const char * pszDir,::file::patha * ppatha,::file::patha * ppathaName,int64_array * piaSize,bool_array * pbaDir)
   {

      System.dir().ls(get_app(), pszDir, ppatha, ppathaName, pbaDir, piaSize);

      return true;

   }


   bool native::is_dir(const char * pszPath)
   {

      return System.dir().is(pszPath, get_app());

   }


   void native::root_ones(stringa & patha,stringa & straTitle)
   {

      System.dir().root_ones(patha, straTitle, get_app());

      
#ifdef WINDOWSEX

      string strDesktopFolder;

      ::windows::SHGetSpecialFolderPath(
         NULL,
         strDesktopFolder,
         CSIDL_DESKTOP,
         FALSE);

      patha.insert_at(0,strDesktopFolder);
      straTitle.insert_at(0,"Área de Trabalho");
      
#endif
      

   }


   void native::get_ascendants_path(const char * pszPath, stringa & stra)
   {

      return System.file().get_ascendants_path(pszPath, stra);

   }


   void native::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {

      return System.file().get_ascendants_name(lpcsz, straParam);

   }


   string native::eat_end_level(const char * pszPath, int32_t iCount)
   {

      string strPath(pszPath);

      while(iCount > 0)
      {

         strPath = System.dir().name(strPath);

         iCount--;

      }

      return strPath;

   }


   string native::file_name(const char * pszPath)
   {

      return System.file().name_(pszPath);

   }


   string native::dir_path(const char * psz1, const char * psz2)
   {

      return System.dir().path(psz1, psz2);

   }


   bool native::file_move(const char * pszDst, const char * pszSrc)
   {

      System.file().move(pszDst, pszSrc);

      return true;

   }


   ::file::buffer_sp native::get_file(var varFile, UINT nOpenFlags, fesp * pfesp)
   {

      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }


      ::fesp fesp;

      ::file::binary_buffer_sp spfile(allocer());

      // ::file::mode_read | ::file::share_deny_none | ::file::type_binary
      fesp  = spfile->open(varFile.get_string(),nOpenFlags);

      if(!fesp)
      {

         spfile.release();

         if(pfesp != NULL)
         {


            *pfesp = fesp;

         }

      }

      return spfile;

   }


   bool native::file_exists(const char * pszPath)
   {

      return ::file_exists_dup(pszPath) != FALSE;

   }


} // namespace fs



