#pragma once

namespace whiteboard
{

   class CLASS_DECL_CA2_CUBE registry :
      public xml::exportable,
      public xml::importable,
      virtual public ::radix::object
   {
   public:
      registry(::ca::application * papp);
      virtual ~registry(void);

     gen::property_set      m_propertysetSites;

     void AddWhiteboardSitesProperties(sites & sites);

     virtual void xml_export(xml::output_tree & xmlot);
     virtual void xml_import(xml::input_tree & xmlit);
      bool LoadFile(const char * lpcszFileName);
      bool WriteFile(const char * lpcszFileName);
      bool LoadFile();
      bool WriteFile();

     string GetRegistryFilePath();

   };

} // namespace whiteboard