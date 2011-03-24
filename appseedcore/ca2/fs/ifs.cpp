#include "stdafx.h"


ifs::ifs(::ca::application * papp, const char * pszRoot) :
   ca(papp),
   ::ca::data(papp),
   ::fs::data(papp)
{
   m_strRoot = pszRoot;
   Application.http().get("http://file.veriwell.net/");
}

bool ifs::has_subdir(const char * pszPath)
{
   xml::node node(get_app());

   string strUrl;

   strUrl = "http://file.veriwell.net/ls?path=" + System.url().url_encode(pszPath);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!node.load(strSource))
      return false;

   if(node.m_strName != "folder")
      return false;

   xml::node * pnode = node.get_child("folder");

   if(pnode == NULL)
      return false;

   if(pnode->get_children_count("folder") <= 0)
      return false;

   return true;

}

void ifs::root_ones(stringa & stra)
{
   stra.add("uifs://");
}



bool ifs::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle)
{
   xml::node node(get_app());

   string strUrl;
   
   strUrl = "http://file.veriwell.net/ls?path=" + System.url().url_encode(pszDir);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!node.load(strSource))
      return false;

   if(node.m_strName != "folder")
      return false;

   xml::node * pnode = node.get_child("folder");

   if(pnode != NULL)
   {
      for(int i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         if(pnode->child_at(i)->m_strName != "folder")
            continue;
         pstraPath->add(dir_path(pszDir, strName));
         pstraTitle->add(strName);
      }
   }

   pnode = node.get_child("file");

   if(pnode != NULL)
   {
      for(int i = 0; i < pnode->get_children_count(); i++)
      {
         string strName = pnode->child_at(i)->attr("name");
         string strExtension = pnode->child_at(i)->attr("extension");
         if(pnode->child_at(i)->m_strName != "file")
            continue;
         pstraPath->add(dir_path(pszDir, strName + "." + strExtension));
         pstraTitle->add(strName + "." + strExtension);
      }
   }

   return true;
}

bool ifs::is_dir(const char * pszPath)
{
   xml::node node(get_app());

   string strUrl;

   strUrl = "http://file.veriwell.net/ls?path=" + System.url().url_encode(pszPath);

   string strSource;

   strSource = Application.http().get(strUrl);

   if(strSource.is_empty())
      return false;

   if(!node.load(strSource))
      return false;

   if(node.m_strName != "folder")
      return false;

   return true;

}

string ifs::file_name(const char * pszPath)
{
   string strPath(pszPath);

   if(!gen::str::begins_eat(strPath, "ifs://"))
   {
      return "";
   }

   gen::parse parse(strPath);

   parse.getword();

   strPath = parse.getrest();

   gen::str::begins_eat(strPath, "/");

   return strPath;


}

bool ifs::file_move(const char * pszDst, const char * pszSrc)
{
   return true;
}


ex1::filesp * ifs::get_file(const char * pszPath)
{
   
   sockets::http::file * pfile = new sockets::http::file(get_app());

   string strUrl;

   strUrl = "http://file.veriwell.net/get?path=" + System.url().url_encode(pszPath);

   if(!pfile->open(strUrl, ::ex1::file::mode_read | ::ex1::file::shareDenyNone | ::ex1::file::type_binary))
   {
      throw new ex1::file_exception_sp(get_app());
   }

   return pfile;

}

