#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE handler :
      virtual public object,
      virtual public ::file::serializable
   {
   public:
      
      
      sp(tree_interface)         m_sptree;


      handler(sp(base_application) papp);
      virtual ~handler();


      void defer_add_library(::core::library * plibrary);
      void add_library(library * plibrary);
      void add_menu_library(menu_library * plibrary);


      sp(::data::tree_item) get_extension_tree_item(const char * pszExtension, bool bCreate);
      sp(::data::tree_item) get_mime_type_tree_item(const char * pszMimeType, bool bCreate);


      virtual void get_extension_app(stringa & straAppId, const char * pszExtension);
      virtual void get_mime_type_app(stringa & straAppId, const char * pszMimeType);


      void write(::file::output_stream & ostream);
      void read(::file::input_stream & istream);


   };


} // namespace filehandler





