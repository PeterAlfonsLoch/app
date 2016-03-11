//#include "framework.h"


namespace fs
{


   set::set(::aura::application * papp) :
      ::object(papp),
      ::data::data(papp),
      ::fs::data(papp)
   {

   }


   set::~set()
   {

   }


   strsp(::fs::data) & set::fsmap()
   {

      return m_fsdatamap;

   }

   spa(::fs::data) & set::fsa()
   {
      return m_spafsdata;
   }


   ::file::listing & set::root_ones(::file::listing & listing)
   {

      single_lock sl(m_pmutex, true);

      m_fsdatamap.remove_all();

      ::file::listing straFsPath;

      for(int32_t i = 0; i < m_spafsdata.get_count(); i++)
      {

         straFsPath.clear_results();

         data * pdata =  m_spafsdata[i];

         sl.unlock();

         pdata->root_ones(straFsPath);

         sl.lock();

         listing.add(straFsPath);

         listing.m_straTitle.add(straFsPath.m_straTitle);

         for(int32_t j = 0; j < straFsPath.get_size(); j++)
         {

            m_fsdatamap[straFsPath[j]] = m_spafsdata[i];

         }

      }

      return listing;

   }


   sp(data) set::path_data(const ::file::path & psz)
   {

      single_lock sl(m_pmutex, true);

      POSITION pos = m_fsdatamap.get_start_position();

      string strRoot;

      {

         sp(::fs::data) pdata;

         while (pos != NULL)
         {

            m_fsdatamap.get_next_assoc(pos, strRoot, pdata);

            if (pdata.is_set())
            {

               if (::str::begins_ci(psz, strRoot))
               {

                  return pdata;

               }

            }

         }

      }

      {

         sp(::fs::data) pdata;

         while (pos != NULL)
         {

            m_fsdatamap.get_next_assoc(pos, strRoot, pdata);

            if (pdata.is_set())
            {

               if (pdata->is_dir(psz))
               {

                  return pdata;

               }

            }

         }

      }

      return NULL;

   }

   sp(data) set::node_path_data(const  ::file::path & psz)
   {

      sp(data) pdata = path_data(psz);

      if(pdata == NULL)
         return this;

      return pdata->node_path_data(psz);

   }

   ::file::listing & set::ls(::file::listing & listing)
   {

      if(listing.m_path.is_empty())
      {

         return root_ones(listing);

      }

      ::fs::data * pdata = path_data(listing.m_path);

      if(pdata != NULL)
      {

         return pdata->ls(listing);

      }

      return listing = failure;

   }

   bool set::is_dir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != NULL)
      {

         return pdata->is_dir(path);

      }

      return false;

   }


   //string set::file_name(const ::file::path & psz)
   //{

   //   ::fs::data * pdata = path_data(psz);

   //   if(pdata != NULL)
   //   {
   //      return pdata->file_name(psz);
   //   }

   //   return "";

   //}


   bool set::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
   {

      ::fs::data * pdataDst = path_data(pszDst);
      ::fs::data * pdataSrc = path_data(pszSrc);

      if(pdataDst != NULL && pdataSrc == pdataDst)
      {
         return pdataDst->file_move(pszDst, pszSrc);
      }
      else
      {
         try
         {
            Application.file().copy(pszDst, pszSrc);
         }
         catch(...)
         {
            return false;
         }
         return true;
      }

   }


   bool set::has_subdir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != NULL)
      {
         return pdata->has_subdir(path);
      }

      return false;

   }


   bool set::tree_show_subdir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != NULL)
      {
         return pdata->tree_show_subdir(path);
      }

      return false;

   }

   bool set::fast_has_subdir(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != NULL)
      {
         return pdata->fast_has_subdir(path);
      }

      return false;

   }

   bool set::is_link(const ::file::path & path)
   {

      ::fs::data * pdata = path_data(path);

      if(pdata != NULL)
      {
         return pdata->is_link(path);
      }

      return false;

   }

   //void set::get_ascendants_path(const ::file::path & psz,::file::patha & stra)
   //{

   //   ::fs::data * pdata = path_data(psz);

   //   if(pdata != NULL)
   //   {
   //      pdata->get_ascendants_path(psz, stra);
   //   }

   //}


   //string set::eat_end_level(const char * psz, int32_t iLevel)
   //{

   //   ::fs::data * pdata = path_data(psz);

   //   if(pdata != NULL)
   //   {
   //      return pdata->eat_end_level(psz, iLevel);
   //   }

   //   return "";

   //}


   //string set::dir_path(const char * pszPath1, const char * pszPath2)
   //{

   //   ::fs::data * pdata = path_data(pszPath1);

   //   if(pdata != NULL)
   //   {
   //      return pdata->dir_path(pszPath1, pszPath2);
   //   }

   //   return ::file::path(pszPath1) / pszPath2;

   //}


   bool set::is_zero_latency(const ::file::path & psz)
   {

      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->is_zero_latency(psz);
      }

      return ::fs::data::is_zero_latency(psz);

   }


} // namespace fs

