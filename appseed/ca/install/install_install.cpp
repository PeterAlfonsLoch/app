#include "StdAfx.h"

//void initialize_http_dup();


namespace ca2
{


   install::install()
   {
      m_hmutexBoot = NULL;
   }

   install::~install()
   {
   }

   void install::add_spa_start(const char * pszId)
   {
      string strPath;
      strPath = System.dir().appdata("spa_start.xml");
      string strContents;
      strContents = Application.file().as_string(strPath);
      ::xml::node node(get_app());
      node.load(strContents);
      node.m_strName = "spa";
      ::xml::node * lpnode = node.GetChildByAttr("start", "id", pszId);
      if(lpnode == NULL)
      {
         lpnode = node.add_child("start");
         lpnode->add_attr("id", pszId);
         Application.file().put_contents(strPath, node.get_xml());
      }
   }

   void install::remove_spa_start(const char * pszId)
   {
      string strPath;
      strPath = System.dir().appdata("spa_start.xml");
      string strContents;
      strContents = Application.file().as_string(strPath);
      ::xml::node node(get_app());
      node.load(strContents);
      node.m_strName = "spa";
      ::xml::node * lpnode = node.GetChildByAttr("start", "id", pszId);
      if(lpnode != NULL)
      {
         node.remove_child(lpnode);
         Application.file().put_contents(strPath, node.get_xml());
      }
   }

   void install::add_app_install(const char * pszId)
   {
      string strPath;
      strPath = System.dir().appdata("spa_install.xml");
      System.dir().mk(System.dir().name(strPath), get_app());
      ::xml::node node(get_app());
      node.load(Application.file().as_string(strPath));
      if(node.m_strName.is_empty())
      {
         node.m_strName = "install";
      }
      ::xml::node * lpnodeInstalled = node.get_child("installed");
      if(lpnodeInstalled == NULL)
      {
         lpnodeInstalled = node.add_child("installed");
      }
      ::xml::node * lpnodeApp = lpnodeInstalled->GetChildByAttr("application", "id", pszId);
      if(lpnodeApp == NULL)
      {
         lpnodeApp = lpnodeInstalled->add_child("application");
         lpnodeApp->add_attr("id", pszId);
      }
      ::xml::disp_option opt = *System.m_poptionDefault;
      opt.newline = true;
      Application.file().put_contents(strPath, node.get_xml(&opt));
   
   }

   bool install::is(const char * pszId)
   {

      string strPath;
      strPath = System.dir().appdata("spa_install.xml");
      string strContents;
      strContents = Application.file().as_string(strPath);
      ::xml::node node(get_app());
      node.load(strContents);
      ::xml::node * lpnodeInstalled = node.get_child("installed");
      if(lpnodeInstalled == NULL)
         return false;
      ::xml::node * lpnodeApp = lpnodeInstalled->GetChildByAttr("application", "id", pszId);
      if(lpnodeApp == NULL)
         return false;
      return true;
   }


   







   

   int install::start(const char * pszCommandLine)
   {
      return ::start_ca2_cube_install(pszCommandLine);
   }


   int install::synch(const char * pszCommandLine)
   {
      return ::ca2_cube_install(pszCommandLine);
   }










} // namespace ca2