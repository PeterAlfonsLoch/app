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

      ::xml::node * lpnode = doc.get_root()->GetChildByAllAttr("start", straName, straValue);

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

      ::xml::node * lpnode = doc.get_root()->GetChildByAllAttr("start", straName, straValue);

      if(lpnode != NULL)
      {

         doc.get_root()->remove_child(lpnode);

         Application.file().put_contents(strPath, doc.get_xml());

      }

   }

   void install::add_app_install(const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
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

      string strBuild(pszBuild);

#if CA2_PLATFORM_VERSION == CA2_BASIS

      ::xml::node * lpnodeVersion = doc.get_root()->get_child("basis");

#else
         
      ::xml::node * lpnodeVersion = doc.get_root()->get_child("stage");

#endif

      if(lpnodeVersion == NULL)
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         lpnodeVersion = doc.get_root()->add_child("basis");

#else
         
         lpnodeVersion = doc.get_root()->add_child("stage");

#endif
         
      }

      ::xml::node * lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", strBuild);

      if(lpnodeInstalled == NULL)
      {

         lpnodeInstalled = lpnodeVersion->add_child("installed");

         lpnodeInstalled->add_attr("build", pszBuild);

      }

      ::xml::node * lpnodeType = lpnodeInstalled->get_child(pszType);

      if(lpnodeType == NULL)
      {

         lpnodeType = lpnodeInstalled->add_child(pszType);

      }

      ::xml::node * lpnode = lpnodeType->GetChildByAttr(pszType, "id", pszId);

      if(lpnode == NULL)
      {

         lpnode = lpnodeType->add_child(pszType);

         lpnode->add_attr("id", pszId);

      }

      stringa straName;
      stringa straValue;

      straName.add("locale");
      straValue.add(pszLocale);


      straName.add("schema");
      straValue.add(pszSchema);

      ::xml::node * lpnodeLocalization = lpnode->GetChildByAllAttr("localization", straName, straValue);

      if(lpnodeLocalization == NULL)
      {

         lpnodeLocalization = lpnode->add_child("localization");

         lpnodeLocalization->add_attr("locale", pszLocale);

         lpnodeLocalization->add_attr("schema", pszSchema);

      }

      ::xml::disp_option opt = *System.m_poptionDefault;

      opt.newline = true;

      Application.file().put_contents(strPath, doc.get_xml(&opt));

   }

   bool install::is(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema)
   {

      string strPath;
      
      strPath = System.dir().appdata("spa_install.xml");
      
      string strContents;
      
      strContents = Application.file().as_string(strPath);
      
      ::xml::document doc(get_app());

      if(strContents.is_empty())
         return false;

      try
      {
      
         if(!doc.load(strContents))
            return false;

      }
      catch(...)
      {

         return false;

      }

      if(doc.get_root() == NULL)
         return false;


      if(string(pszVersion).is_empty())
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS

         pszVersion = "basis";


#else
         
         pszVersion = "basis";

#endif

      }

      ::xml::node * lpnodeVersion = doc.get_root()->get_child(pszVersion);

      if(lpnodeVersion == NULL)
         return false;

      string strBuildNumber(pszBuild);

      if(strBuildNumber == "latest")
      {

         strBuildNumber = get_latest_build_number(pszVersion);

      }

      ::xml::node * lpnodeInstalled = lpnodeVersion->GetChildByAttr("installed", "build", strBuildNumber);

      if(lpnodeInstalled == NULL)
         return false;
      
      ::xml::node * lpnodeType = lpnodeInstalled->get_child(pszType);
      
      if(lpnodeType == NULL)
         return false;
      
      ::xml::node * lpnode = lpnodeType->GetChildByAttr(pszType, "id", pszId);

      if(lpnode == NULL)
         return false;

      stringa straName;
      stringa straValue;

      straName.add("locale");
      straValue.add(pszLocale);


      straName.add("schema");
      straValue.add(pszSchema);

      ::xml::node * lpnodeLocalization = lpnode->GetChildByAllAttr("localization", straName, straValue);

      if(lpnodeLocalization == NULL)
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



