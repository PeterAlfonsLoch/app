#include "framework.h"


namespace ca2
{


   install::install()
   {
      m_hmutexBoot = NULL;
   }

   install::~install()
   {
   }

   void install::add_spa_start(const char * pszType, const char * pszId)
   {
      
      string strPath;

      strPath = System.dir().appdata("spa_start.xml");

      string strContents;

      strContents = Application.file().as_string(strPath);

      ::xml::document doc(get_app());

      doc.load(strContents);

      doc.get_root()->set_name("spa");

      stringa straName;
      stringa straValue;

      straName.add("type");
      straValue.add(pszType);

      straName.add("id");
      straValue.add(pszId);

      ::xml::node * lpnode = doc.get_root()->GetChildByAttr("start", straName, straValue);

      if(lpnode == NULL)
      {

         lpnode = doc.get_root()->add_child("start");

         lpnode->add_attr("type", pszType);

         lpnode->add_attr("id", pszId);

         Application.file().put_contents(strPath, doc.get_xml());

      }

   }

   void install::remove_spa_start(const char * pszType, const char * pszId)
   {

      string strPath;

      strPath = System.dir().appdata("spa_start.xml");

      string strContents;

      strContents = Application.file().as_string(strPath);

      ::xml::document doc(get_app());

      doc.load(strContents);

      doc.get_root()->set_name("spa");

      stringa straName;
      stringa straValue;

      straName.add("type");
      straValue.add(pszType);

      straName.add("id");
      straValue.add(pszId);

      ::xml::node * lpnode = doc.get_root()->GetChildByAttr("start", straName, straValue);

      if(lpnode != NULL)
      {

         doc.get_root()->remove_child(lpnode);

         Application.file().put_contents(strPath, doc.get_xml());

      }

   }

   void install::add_app_install(const char * pszType, const char * pszId)
   {

      string strPath;

      strPath = System.dir().appdata("spa_install.xml");

      System.dir().mk(System.dir().name(strPath), get_app());

      ::xml::document doc(get_app());

      doc.load(Application.file().as_string(strPath));

      if(doc.get_root()->get_name().is_empty())
      {
         doc.get_root()->set_name("install");
      }

      ::xml::node * lpnodeInstalled = doc.get_root()->get_child("installed");
      if(lpnodeInstalled == NULL)
      {
         lpnodeInstalled = doc.get_root()->add_child("installed");
      }
      ::xml::node * lpnodeType = doc.get_root()->get_child(pszType);
      if(lpnodeType == NULL)
      {
         lpnodeType = doc.get_root()->add_child(pszType);
      }
      ::xml::node * lpnode = lpnodeType->GetChildByAttr(pszType, "id", pszId);
      if(lpnode == NULL)
      {
         lpnode = lpnodeInstalled->add_child(pszType);
         lpnode->add_attr("id", pszId);
      }
      ::xml::disp_option opt = *System.m_poptionDefault;
      opt.newline = true;
      Application.file().put_contents(strPath, doc.get_xml(&opt));

   }

   bool install::is(const char * pszType, const char * pszId)
   {

      string strPath;
      
      strPath = System.dir().appdata("spa_install.xml");
      
      string strContents;
      
      strContents = Application.file().as_string(strPath);
      
      ::xml::document doc(get_app());
      
      doc.load(strContents);

      ::xml::node * lpnodeInstalled = doc.get_root()->get_child("installed");

      if(lpnodeInstalled == NULL)
         return false;
      
      ::xml::node * lpnodeType = doc.get_root()->get_child(pszType);
      
      if(lpnodeType == NULL)
         return false;
      
      ::xml::node * lpnode = lpnodeType->GetChildByAttr(pszType, "id", pszId);

      if(lpnode == NULL)
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



