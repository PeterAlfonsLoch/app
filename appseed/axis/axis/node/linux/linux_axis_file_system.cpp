#include "framework.h"
#include "linux.h"
#include <sys/stat.h>
#include <ctype.h>


struct PROCESS_INFO_t
{
    string csProcess;
    uint32_t dwImageListIndex;
};


namespace linux
{

   namespace axis
   {

   file_system::file_system(::aura::application *  papp) :
      ::object(papp),
      ::file::system(papp),
      ::file::axis::system(papp),
      ::linux::file_system(papp)
   {
   }

//   bool file_system::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
//   {
//      string stra(lpszFilPathA);
//      string wstrb(lpszFilPathB);
//
//   //   ::str::international::ACPToUnicode(stra, lpszFilPathA);
//   //   ::str::international::ACPToUnicode(wstrb, lpszFilPathB);
//      if(stra == wstrb)
//         return true;
//
//      /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
//         return false;
//      if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
//         return false;*/
//      return stra == wstrb;
//
//   }
//
//
//   bool file_system::path::eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator)
//   {
//
//      strsize iLast = str.length() - 1;
//
//      if(iLast < 0)
//         return iLevelCount <= 0;
//
//      while(str[iLast] == '/' || str[iLast] == '\\')
//         iLast--;
//
//      for(int32_t i = 0; i < iLevelCount; i++)
//      {
//
//         strsize iFind1 = str.reverse_find('/', iLast);
//
//         strsize iFind2 = str.reverse_find('\\', iLast);
//
//         strsize iFind = MAX(iFind1, iFind2);
//
//         if(iFind >= iLast)
//            return false;
//
//         if(iFind < 0)
//            return false;
//
//         iLast = iFind;
//
//         while(str[iLast] == '/' || str[iLast] == '\\')
//            iLast--;
//
//      }
//
//      str.Truncate(iLast + 1);
//
//      return true;
//
//   }
//
//   bool file_system::path::is_relative(const char * psz)
//   {
//      string strPath(psz);
//      if(strPath.find(':') != -1 && strPath.find(':') < 10)
//         return false;
//      if(strPath.find('/') == 0 || strPath.find('\\') == 0)
//         return false;
//      return true;
//   }
      ::file::buffer_sp file_system::get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp)
      {
         
         ::file::buffer_sp spfile;
         
         spfile = ::file::axis::system::get_file(varFile,nOpenFlags,pfesp,papp);
         
         if(spfile.is_set())
         {
            
            return spfile;
            
         }
         
         spfile = ::windows::file_system::get_file(varFile,nOpenFlags,pfesp,papp);
         
         if(spfile.is_set())
         {
            
            return spfile;
            
         }
         
         return NULL;
         
      }


   } // namespace axis
   

} // namespace linux






