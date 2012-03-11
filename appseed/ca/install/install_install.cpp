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
      
      ::xml::document doc(get_app());

      doc.load(strContents);

      doc.set_name("spa");

      ::xml::node * lpnode = doc.GetChildByAttr("start", "id", pszId);
      if(lpnode == NULL)
      {
         lpnode = doc.add_child("start");
         lpnode->add_attr("id", pszId);
         Application.file().put_contents(strPath, doc.get_xml());
      }
   }

   void install::remove_spa_start(const char * pszId)
   {
      string strPath;
      strPath = System.dir().appdata("spa_start.xml");
      string strContents;
      strContents = Application.file().as_string(strPath);
      ::xml::document doc(get_app());
      doc.load(strContents);
      doc.set_name("spa");
      ::xml::node * lpnode = doc.GetChildByAttr("start", "id", pszId);
      if(lpnode != NULL)
      {
         doc.remove_child(lpnode);
         Application.file().put_contents(strPath, doc.get_xml());
      }
   }

   void install::add_app_install(const char * pszId)
   {
      string strPath;
      strPath = System.dir().appdata("spa_install.xml");
      System.dir().mk(System.dir().name(strPath), get_app());
      ::xml::document doc(get_app());
      doc.load(Application.file().as_string(strPath));
      if(doc.get_name().is_empty())
      {
         doc.set_name("install");
      }
      ::xml::node * lpnodeInstalled = doc.get_child("installed");
      if(lpnodeInstalled == NULL)
      {
         lpnodeInstalled = doc.add_child("installed");
      }
      ::xml::node * lpnodeApp = lpnodeInstalled->GetChildByAttr("application", "id", pszId);
      if(lpnodeApp == NULL)
      {
         lpnodeApp = lpnodeInstalled->add_child("application");
         lpnodeApp->add_attr("id", pszId);
      }
      ::xml::disp_option opt = *System.m_poptionDefault;
      opt.newline = true;
      Application.file().put_contents(strPath, doc.get_xml(&opt));
   
   }

   bool install::is(const char * pszId)
   {

      string strPath;
      strPath = System.dir().appdata("spa_install.xml");
      string strContents;
      strContents = Application.file().as_string(strPath);
      ::xml::document doc(get_app());
      doc.load(strContents);
      ::xml::node * lpnodeInstalled = doc.get_child("installed");
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