//#include "framework.h"


namespace fs
{


   data::data(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp)
   {


   }

   
   bool data::has_subdir(const ::file::path & pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      return false;
   }

   bool data::fast_has_subdir(const ::file::path & pszPath)
   {
      return has_subdir(pszPath);
   }


   //string data::file_name(const ::file::path & pszPath)
   //{
   //   UNREFERENCED_PARAMETER(pszPath);
   //   return "";
   //}

   bool data::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
   {
      UNREFERENCED_PARAMETER(pszDst);
      UNREFERENCED_PARAMETER(pszSrc);
      return false;
   }

   //string data::dir_path(const ::file::path & psz1, const ::file::path & psz2)
   //{
   //   string str(psz1);
   //   if(str.Right(1) != '/')
   //      str += "/";
   //   return str + psz2;
   //}


   bool data::tree_show_subdir(const ::file::path & pszPath)
   {
      
      return true;

   }

   //string data::eat_end_level(const ::file::path & pszPath, int32_t iCount)
   //{
   //   string strPath(pszPath);
   //   strsize iFind = 0;
   //   strsize iStart = strPath.get_length() - 1;
   //   if(iCount <= 0)
   //      return pszPath;
   //   while(iCount > 0)
   //   {
   //      iFind = strPath.reverse_find('/', iStart);
   //      strsize iPos = iFind - 1;
   //      if(iPos >= 0 && strPath[iPos] == '/')
   //      {
   //         iPos--;
   //         if(iPos >= 0 && strPath[iPos] == ':')
   //         {
   //            if(iFind == iStart)
   //            {
   //               iPos--;
   //               // t12n dedicaverse comments : protocol name
   //               iFind = strPath.reverse_find('/', iPos);
   //               if(iFind < 0)
   //                  iFind = 0;
   //            }
   //            else
   //            {
   //               iFind++;
   //            }
   //         }
   //      }
   //      iCount--;
   //      if(iCount <= 0)
   //         break;
   //      if(iFind < 0)
   //         return "";
   //      iStart = iFind - 1;
   //   }
   //   return strPath.Left(iFind);
   //}


   ::file::listing & data::ls(::file::listing & listing)
   {

      UNREFERENCED_PARAMETER(listing);

      return listing;

   }


   bool data::is_dir(const ::file::path & pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      return false;
   }

   ::file::listing & data::root_ones(::file::listing & listing)
   {
      
      return listing = failure;
      
   }

   //void data::get_ascendants_path(const ::file::path & lpcsz,::file::patha & straParam)
   //{
   //   ::file::patha stra;
   //   get_ascendants_name(lpcsz, stra);
   //   string str;
   //   for(int32_t i = 0; i < stra.get_size(); i++)
   //   {
   //      str += stra[i];
   //      if(i != 0 || !::str::ends(str, "//"))
   //      {
   //         str += "/";
   //      }
   //      straParam.add(::file::path(str));
   //   }
   //}

   //void data::get_ascendants_name(const ::file::path & lpcsz,::file::patha & straParam)
   //{
   //   stringa straSeparator;
   //   straSeparator.add("/");
   //   straSeparator.add("\\");
   //   straParam.add_smallest_tokens(lpcsz, straSeparator, TRUE);
   //   for(int32_t i = 0; i < straParam.get_size(); )
   //   {
   //      if(straParam[i].is_empty())
   //      {
   //         straParam.remove_at(i);
   //         if(i == 1 && ::str::ends(straParam[0], ":"))
   //         {
   //            straParam[0] = straParam[0] + "//";
   //         }
   //      }
   //      else
   //      {
   //         i++;
   //      }
   //   }
   //}


   ::file::buffer_sp data::get_file(const ::file::path & varFile,UINT nOpenFlags,cres * pfesp)
   {
      
      if(pfesp != NULL)
      {
         
         (*pfesp)->add(fesp(failure));

      }
      
      UNREFERENCED_PARAMETER(varFile);

      UNREFERENCED_PARAMETER(nOpenFlags);

      return NULL;

   }

   
   bool data::file_exists(const ::file::path & path)
   {
      
      ::file::listing listing(this);
      
      listing.ls(path.folder());
      
      return listing.contains_ci(path.name());

   }


   var data::file_length(const ::file::path & path)
   {
      
      ::file::listing listing(this);

      listing.ls(path.folder());
      
      index iFind = listing.find_first_ci(path.name());

      if (iFind < 0)
         return var(var::type_null);

      return listing[iFind].m_iSize;

   }


   sp(data) data::node_path_data(const ::file::path & psz)
   {

      return this;

   }

   sp(data) data::path_data(const ::file::path & psz)
   {

      return this;

   }


   bool data::is_link(const ::file::path & psz)
   {

      return ::str::ends_ci(psz,".lnk");

   }


   bool data::is_zero_latency(const ::file::path & psz)
   {

      return true;

   }


   ::file::listing & data::perform_file_listing(::file::listing & listing)
   {

      return ls(listing);

   }


} // namespace fs





