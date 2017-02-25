#pragma once


#include "aura/primitive/collection/collection_file_path_map.h"


namespace file
{


   namespace dir
   {


      class CLASS_DECL_AURA is_dir
      {
      public:

         bool           m_bIsDir;
         uint32_t       m_dwLastCheck;
         uint32_t       m_dwError;


      };


      class CLASS_DECL_AURA is_dir_map :
         virtual public file_path_map < is_dir >
      {
      public:


         mutex                m_mutex;
         uint32_t             m_dwTimeOut;


         is_dir_map(::aura::application * papp);


         bool lookup(const ::file::path & strPath, bool &bIsDir, uint32_t & dwLastError);
         bool lookup(const ::file::path & strPath, bool &bIsDir, uint32_t & dwLastError, int32_t iLast);
         void set(const ::file::path & strPath, bool bIsDir, uint32_t dwLastError);


      };


      class CLASS_DECL_AURA dir_system_heap
      {
      public:

         is_dir_map         m_isdirmap;


         ::file::path         m_strCa2;
         ::file::path         m_pathCa2Module;
         ::file::path         m_pathModule;
         ::file::path         m_pathProfile;
         ::file::path         m_pathUser;
         ::file::path         m_pathHome;

         dir_system_heap(::aura::application * papp) :
            m_isdirmap(papp)
         {


         }

      };


   } // namespace dir


} // namespace file



