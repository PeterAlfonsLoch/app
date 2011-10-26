#include "StdAfx.h"


namespace whiteboard
{

   registry::registry(::ca::application * papp) :
      ca(papp)
   {
      string str;
      char szDir[MAX_PATH * 4];
      ::SHGetSpecialFolderPath(NULL, szDir, CSIDL_LOCAL_APPDATA, TRUE);
      str = szDir;
      str += "\\";
      str += "backlite\\";
      ::CreateDirectory(str, NULL);
      str += "whiteboard\\";
      ::CreateDirectory(str, NULL);
   }

   void registry::AddWhiteboardSitesProperties(sites & sites)
   {
      site * psite;
      int iCount = sites.get_count();
      for(int i = 0; i < iCount; i++)
      {
         psite = sites.get_at(i);
         m_propertysetSites.add(psite->m_strProfileKey, var::type_string);
         m_propertysetSites[psite->m_esite] = psite->m_strDefaultUrl;
      }
   }

   registry::~registry()
   {
   }
   
   void registry::xml_export(xml::output_tree & xmlot)
   {
      xml::property_set_exchange exchange(get_app());
      exchange.m_ppropertyset = &m_propertysetSites;
      exchange.xml_export(xmlot);
   }
  
   void registry::xml_import(xml::input_tree & xmlit)
   {
      xml::property_set_exchange exchange(get_app());
      exchange.m_ppropertyset = &m_propertysetSites;
      exchange.xml_import(xmlit);
   }

   bool registry::LoadFile(const char * lpcszFileName)
   {
      xml::document doc(get_app());

      if(!doc.load(lpcszFileName))
         return false;

      xml::input_tree xmlit(get_app());
      xmlit.m_pdocument = &doc;
      try
      {
         xmlit.import_node("registry", *this);
      }
      catch(const char * psz)
      {
         TRACE("%s", psz);
         return false;
      }
      return true;
   }

   string registry::GetRegistryFilePath()
   {
      string str;
      char szDir[MAX_PATH * 4];
      ::SHGetSpecialFolderPath(NULL, szDir, CSIDL_LOCAL_APPDATA, TRUE);
      str = szDir;
      str += "\\";
      str += "backlite\\whiteboard\\registry.xml";
      return str;
   }

   bool registry::LoadFile()
   {
      return LoadFile(GetRegistryFilePath());
   }

   bool registry::WriteFile()
   {
      return WriteFile(GetRegistryFilePath());
   }

   bool registry::WriteFile(const char * lpcszFileName)
   {
      xml::document doc(get_app());

      xml::output_tree xmlot(get_app());
      xmlot.m_pdocument = &doc;
      xmlot.export_node("registry", *this);

      Application.file().put_contents(lpcszFileName, doc.get_xml());

      return true;
   }

} // namespace whiteboard