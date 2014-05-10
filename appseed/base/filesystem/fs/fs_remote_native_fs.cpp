#include "framework.h"


namespace fs
{


   remote_native::remote_native(sp(::base::application) papp, const char * pszRoot) :
      element(papp),
      ::data::data(papp),
      ::fs::data(papp)
   {

      m_strRoot = pszRoot;

   }


   remote_native::~remote_native()
   {

   }


   bool remote_native::fast_has_subdir(const char * pszPath)
   {

      return true;

   }


   bool remote_native::has_subdir(const char * pszPath)
   {

      defer_initialize();

      xml::document doc(get_app());

      string strUrl;

      strUrl = "http://fs.veriwell.net/fs/ls?path=" + System.url().url_encode(pszPath);

      string strSource;

      property_set set(get_app());

      strSource = Application.http().get(strUrl, set);

      if(strSource.is_empty())
         return false;

      if(!doc.load(strSource))
         return false;

      if(doc.get_root()->get_name() != "folder")
         return false;

      sp(::xml::node) pnode = doc.get_child("folder");

      if(pnode == NULL)
         return false;

      if(pnode->get_children_count("folder") <= 0)
         return false;

      return true;

   }

   void remote_native::root_ones(stringa & straPath, stringa & straTitle)
   {
      straPath.add("fs://");
      straTitle.add("File System");
   }



   bool remote_native::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle, int64_array * piaSize)
   {

      try
      {
         defer_initialize();
      }
      catch(string & str)
      {
         if(str == "You have not logged in! Exiting!")
         {
            throw string("uifs:// You have not logged in!");
         }
         return false;
      }

      xml::document doc(get_app());

      string strUrl;

      strUrl = "http://fs.veriwell.net/fs/ls?path=" + System.url().url_encode(System.url().get_script(pszDir))
         + "&server=" + System.url().url_encode(System.url().get_server(pszDir));

      string strSource;

      property_set set(get_app());

      strSource = Application.http().get(strUrl, set);

      if(strSource.is_empty())
         return false;

      if(!doc.load(strSource))
         return false;

      if(doc.get_root()->get_name() != "folder")
         return false;

      sp(::xml::node) pnode = doc.get_root()->get_child("folder");

      if(pnode != NULL)
      {
         for(int32_t i = 0; i < pnode->get_children_count(); i++)
         {
            string strName = pnode->child_at(i)->attr("name");
            if(pnode->child_at(i)->get_name() != "folder")
               continue;
            string strPath = dir_path(pszDir, strName);
            m_mapdirTimeout[strPath] = ::get_tick_count() + (15 * 1000);
            m_mapfileTimeout.remove_key(strPath);
            if(pstraPath != NULL)
            {
               pstraPath->add(strPath);
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(strName);
            }
         }
      }

      pnode = doc.get_root()->get_child("file");

      if(pnode != NULL)
      {
         for(int32_t i = 0; i < pnode->get_children_count(); i++)
         {
            string strName = pnode->child_at(i)->attr("name");
            //string strExtension = pnode->child_at(i)->attr("extension");
            if(pnode->child_at(i)->get_name() != "file")
               continue;
            string strPath = dir_path(pszDir, strName);
            string strSize = pnode->child_at(i)->attr("size");
            m_mapfileTimeout[strPath] = ::get_tick_count() + (15 * 1000);
            m_mapdirTimeout.remove_key(strPath);
            if(pstraPath != NULL)
            {
               pstraPath->add(strPath);
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(strName);
            }
            if (piaSize != NULL)
            {
               piaSize->add(::str::to_int64(strSize));
            }
         }
      }

      return true;
   }

   bool remote_native::is_dir(const char * pszPath)
   {


      //xml::node node(get_app());

      if(pszPath == NULL || strlen(pszPath) == 0)
      {
         return true;
      }

      if(stricmp_dup(pszPath, "fs://") == 0)
      {
         return true;
      }

      if(System.url().get_script(pszPath).is_empty() ||
         System.url().get_script(pszPath) == "/")
      {
         return true;
      }


      defer_initialize();


      uint32_t dwTimeout;

      if(m_mapfileTimeout.Lookup(pszPath, dwTimeout))
      {
         if(::get_tick_count() > dwTimeout)
         {
            stringa straPath;
            stringa straTitle;
            int64_array iaSize;
            ls(System.dir().name(pszPath), &straPath, &straTitle, &iaSize);
         }
         else
         {
            return false;
         }
      }

      if(m_mapdirTimeout.Lookup(pszPath, dwTimeout))
      {
         if(::get_tick_count() > dwTimeout)
         {
            stringa straPath;
            stringa straTitle;
            int64_array iaSize;
            ls(System.dir().name(pszPath), &straPath, &straTitle, &iaSize);
         }
         else
         {
            return true;
         }
      }

      if(m_mapfileTimeout.Lookup(pszPath, dwTimeout))
      {
         if(::get_tick_count() > dwTimeout)
         {
            return false;
         }
         else
         {
            return true;
         }
      }
      else
      {
         return false;
      }



      /*string strUrl;

      strUrl = "http://fs.veriwell.net/fs/ls?path=" + System.url().url_encode(pszPath);

      string strSource;

      strSource = Application.http().get(strUrl);

      if(strSource.is_empty())
      return false;

      if(!node.load(strSource))
      return false;

      if(node.m_strName != "folder")
      return false;

      return true;*/

   }

   string remote_native::file_name(const char * pszPath)
   {

      string strPath(pszPath);

      if(!::str::begins_eat_ci(strPath, "fs://"))
      {
         return "";
      }

      strsize iFind = strPath.reverse_find("/");

      if(iFind < 0)
         iFind = -1;

      return strPath.Mid(iFind + 1);

   }

   bool remote_native::file_move(const char * pszDst, const char * pszSrc)
   {
      UNREFERENCED_PARAMETER(pszDst);
      UNREFERENCED_PARAMETER(pszSrc);
      return true;
   }


   ::file::buffer_sp remote_native::get_file(var varFile, UINT nOpenFlags)
   {

      ::file::buffer_sp spfile;

      spfile = new remote_native_file(get_app(), varFile);

      if(!spfile->open(varFile.get_string(), nOpenFlags))
      {
         throw ::file::exception(get_app(), ::file::exception::none, -1, varFile.get_string());
      }

      return spfile;

   }

   bool remote_native::file_exists(const char * pszPath)
   {
      return ::fs::data::file_exists(pszPath);
   }


   void remote_native::defer_initialize()
   {

      if(!m_bInitialized)
      {
         //Application.http().get("http://file.veriwell.net/");
         m_bInitialized = true;
      }

   }


} // namespace fs


