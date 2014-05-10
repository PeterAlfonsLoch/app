#include "framework.h"


namespace fs
{


   set::set(sp(::base::application) papp) :
      element(papp),
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


   void set::root_ones(stringa & straPath, stringa & straTitle)
   {
      
      m_fsdatamap.remove_all();

      stringa straFsPath;
      stringa straFsTitle;

      for(int32_t i = 0; i < m_spafsdata.get_count(); i++)
      {
         straFsPath.remove_all();
         straFsTitle.remove_all();
         m_spafsdata[i].root_ones(straFsPath, straFsTitle);
         straPath.add(straFsPath);
         straTitle.add(straFsTitle);
         for(int32_t j = 0; j < straFsPath.get_size(); j++)
         {
            m_fsdatamap[straFsPath[j]] = m_spafsdata(i);
         }
      }

   }

   sp(data) set::path_data(const char * psz)
   {
      POSITION pos = m_fsdatamap.get_start_position();

      string strRoot;
      sp(::fs::data) pdata;

      while(pos != NULL)
      {
         m_fsdatamap.get_next_assoc(pos, strRoot, pdata);
         if(::str::begins_ci(psz, strRoot))
         {
            return pdata;
         }
      }
      
      return NULL;

   }

   sp(data) set::node_path_data(const char * psz)
   {

      sp(data) pdata = path_data(psz);

      if(pdata == NULL)
         return this;

      return pdata->node_path_data(psz);

   }

   bool set::ls(const char * psz, stringa * pstraPath, stringa * pstraTitle, int64_array * piaSize)
   {

      if(psz == NULL || strlen(psz) == 0)
      {
         stringa straPath;
         stringa straTitle;
         root_ones(straPath, straTitle);
         for(int32_t i = 0; i < straPath.get_size(); i++)
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(straPath[i]);
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(straTitle[i]);
            }
            if (piaSize != NULL)
            {
               piaSize->add(0); // don't tell size of root folders
            }
         }
         return true;
      }
      
      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->ls(psz, pstraPath, pstraTitle, piaSize);
      }
      
      return false;

   }

   bool set::is_dir(const char * psz)
   {
      
      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->is_dir(psz);
      }

      return false;

   }


   string set::file_name(const char * psz)
   {

      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->file_name(psz);
      }

      return "";

   }


   bool set::file_move(const char * pszDst, const char * pszSrc)
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


   bool set::has_subdir(const char * psz)
   {
      
      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->has_subdir(psz);
      }

      return false;

   }


   bool set::tree_show_subdir(const char * psz)
   {

      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->tree_show_subdir(psz);
      }

      return false;

   }

   bool set::fast_has_subdir(const char * psz)
   {
      
      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->fast_has_subdir(psz);
      }

      return false;

   }

   bool set::is_link(const char * psz)
   {

      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->is_link(psz);
      }

      return false;

   }

   void set::get_ascendants_path(const char * psz,stringa & stra)
   {

      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         pdata->get_ascendants_path(psz, stra);
      }

   }


   string set::eat_end_level(const char * psz, int32_t iLevel)
   {
      
      ::fs::data * pdata = path_data(psz);

      if(pdata != NULL)
      {
         return pdata->eat_end_level(psz, iLevel);
      }

      return "";

   }


   string set::dir_path(const char * pszPath1, const char * pszPath2)
   {

      ::fs::data * pdata = path_data(pszPath1);

      if(pdata != NULL)
      {
         return pdata->dir_path(pszPath1, pszPath2);
      }

      return System.dir().path(pszPath1, pszPath2);

   }


} // namespace fs

