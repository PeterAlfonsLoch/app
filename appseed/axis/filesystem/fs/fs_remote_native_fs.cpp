//#include "framework.h" // from "axis/net/net_sockets.h"
//#include "axis/net/net_sockets.h"


namespace fs
{


   remote_native::remote_native(::aura::application * papp, const char * pszRoot) :
      ::object(papp),
      ::data::data(papp),
      ::fs::data(papp)
   {

      m_strRoot = pszRoot;

   }


   remote_native::~remote_native()
   {

   }


   bool remote_native::fast_has_subdir(const ::file::path & pszPath)
   {

      return true;

   }


   bool remote_native::has_subdir(const ::file::path & pszPath)
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

   ::file::listing & remote_native::root_ones(::file::listing & listing)
   {

      listing.add("fs://");

      listing.m_straTitle.add("File System");

      return listing;

   }



   ::file::listing & remote_native::ls(::file::listing & listing)
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

         return listing;

      }

      xml::document doc(get_app());

      string strUrl;

      strUrl = "http://fs.veriwell.net/fs/ls?path=" + System.url().url_encode(System.url().get_script(listing.m_path))
         + "&server=" + System.url().url_encode(System.url().get_server(listing.m_path));

      string strSource;

      property_set set(get_app());

      strSource = Application.http().get(strUrl, set);

      if(strSource.is_empty())
         return listing = failure;

      if(!doc.load(strSource))
         return listing = failure;

      if(doc.get_root()->get_name() != "folder")
         return listing = failure;

      sp(::xml::node) pnode = doc.get_root()->get_child("folder");

      if(pnode != NULL)
      {
         for(auto child : pnode->childrenref())
         {

            if(child.get_name() != "folder")
               continue;
            
            m_mapdirTimeout[listing.m_path] = ::get_tick_count() + (15 * 1000);
            
            m_mapfileTimeout.remove_key(listing.m_path);
            
            ::file::path & path = listing.add_child(child.attr("name"));
            
            path.m_iSize = 0;
            
            path.m_iDir = 1;

         }
      }

      pnode = doc.get_root()->get_child("file");

      if(pnode != NULL)
      {

         for(auto child : pnode->childrenref())
         { 

            if(child.get_name() != "file")
               continue;

            m_mapfileTimeout[listing.m_path] = ::get_tick_count() + (15 * 1000);
            
            m_mapdirTimeout.remove_key(listing.m_path);

            ::file::path & path = listing.add_child(child.attr("name"));

            path.m_iSize = child.attr("size");

            path.m_iDir = 0;

         }
      }

      return listing;

   }


   bool remote_native::is_dir(const ::file::path & path)
   {


      //xml::node node(get_app());

      if(path.is_empty())
      {
         return true;
      }

      if(stricmp_dup(path, "fs://") == 0)
      {
         return true;
      }

      if(System.url().get_script(path).is_empty() ||
         System.url().get_script(path) == "/")
      {
         return true;
      }


      defer_initialize();


      uint32_t dwTimeout;

      if(m_mapfileTimeout.Lookup(path,dwTimeout))
      {
         if(::get_tick_count() > dwTimeout)
         {
            ::file::listing l(this);

            l.ls(path);
         }
         else
         {
            return false;
         }
      }

      if(m_mapdirTimeout.Lookup(path,dwTimeout))
      {
         if(::get_tick_count() > dwTimeout)
         {
            ::file::listing l(this);

            l.ls(path);
         }
         else
         {
            return true;
         }
      }

      if(m_mapfileTimeout.Lookup(path, dwTimeout))
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

   //string remote_native::file_name(const ::file::path & pszPath)
   //{

   //   string strPath(pszPath);

   //   if(!::str::begins_eat_ci(strPath, "fs://"))
   //   {
   //      return "";
   //   }

   //   strsize iFind = strPath.reverse_find("/");

   //   if(iFind < 0)
   //      iFind = -1;

   //   return strPath.Mid(iFind + 1);

   //}

   bool remote_native::file_move(const ::file::path & pszDst,const ::file::path & pszSrc)
   {
      UNREFERENCED_PARAMETER(pszDst);
      UNREFERENCED_PARAMETER(pszSrc);
      return true;
   }


   ::file::buffer_sp remote_native::get_file(const ::file::path & path,UINT nOpenFlags,cres * pfesp)
   {

      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      ::cres cres;

      ::file::buffer_sp spfile;

      spfile = new remote_native_file(get_app(),path);

      cres = spfile->open(path,nOpenFlags);

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

   bool remote_native::file_exists(const ::file::path & pszPath)
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

   bool remote_native::is_zero_latency(const  ::file::path & psz)
   {

      return false;

   }

} // namespace fs


