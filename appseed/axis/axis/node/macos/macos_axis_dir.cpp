#include "framework.h"
#include "macos.h"



namespace macos
{

   
   namespace axis
   {

      
      dir::dir(::aura::application *   papp) :
         ::object(papp),
         ::file::dir::system(papp),
         ::file_watcher::file_watcher(papp),
         ::file_watcher::listener_thread(papp),
         ::file::dir::axis::system(papp),
         ::macos::dir(papp)
      {


      }
      
      
      ::file::listing & dir::ls(::aura::application * papp, ::file::listing & listing)
      {
         
         
         if(::file::dir::axis::system::ls(papp, listing).succeeded())
         {
            
            return listing;
            
         }
         
         return ::macos::dir::ls(papp,listing);
         
      }
      
      
      bool dir::initialize()
      {
         
         if(!::macos::dir::initialize())
            return false;
         
         return true;
         
      }

      
      bool dir::is(const ::file::path & lpcszPath, ::aura::application * papp)
      {
         
         if(lpcszPath.m_iDir > 0)
         {
         
            return true;
            
         }
         
         if(lpcszPath.m_iDir == 0)
         {
            
            return false;
            
         }
         
         if(::macos::dir::is(lpcszPath,papp))
            return true;
         
         if(::file::dir::axis::system::is(lpcszPath, papp))
            return true;
         
         return false;
         
      }
      
      
      bool dir::name_is(const ::file::path & str, ::aura::application * papp)
      {

         strsize iLast = str.get_length() - 1;

         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               break;
            iLast--;
         }
         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
               break;
            iLast--;
         }
         if(iLast >= 0)
         {
            while(iLast >= 0)
            {
               if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               {
                  iLast++;
                  break;
               }
               iLast--;
            }
         }
         else
         {
            return true; // assume empty string is root_ones directory
         }
         
         
         bool bIsDir;
         
         
         uint32_t uiLastError;
         
         if(m_isdirmap.lookup(str, bIsDir, uiLastError, (int32_t) iLast))
         {
            if(!bIsDir)
            {
               ::SetLastError(uiLastError);
            }
            return bIsDir;
         }
         
         
         if(::get_thread() != NULL && ::get_thread()->m_bZipIsDir && iLast >= 3 && !strnicmp_dup(&((const char *)str)[iLast - 3],".zip",4))
         {
            m_isdirmap.set(str.Left(iLast + 1), true, 0);
            return true;
         }
         
         strsize iFind = ::str::find_ci(".zip:", str);
         
         if(::get_thread() != NULL && ::get_thread()->m_bZipIsDir && iFind >= 0 && iFind < iLast)
         {
            bool bHasSubFolder;
            if(m_isdirmap.lookup(str, bHasSubFolder, uiLastError))
            {
               if(!bHasSubFolder)
               {
                  ::SetLastError(uiLastError);
               }
               return bHasSubFolder;
            }
            bHasSubFolder = m_pziputil->has_sub_folder(papp, str);
            m_isdirmap.set(str.Left(iLast + 1), bHasSubFolder, bHasSubFolder ? 0 : ::GetLastError());
            return bHasSubFolder;
         }
         
         
         bIsDir = ::dir::is(str.Left(iLast));
         
         m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());
         
         return bIsDir;

      }


   } // namespace axis

} // namespace macos
