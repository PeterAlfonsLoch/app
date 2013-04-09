#pragma once


namespace filehandler
{


   class CLASS_DECL_ca handler :
      virtual public ::ca::object,
      virtual public ::ca::byte_serializable
   {
   public:
      
      
      sp(tree_interface)         m_sptree;


      handler(sp(::ca::application) papp);
      virtual ~handler();


      void defer_add_library(::ca::library * plibrary);
      void add_library(library * plibrary);
      void add_menu_library(menu_library * plibrary);


      sp(::ca::tree_item) get_extension_tree_item(const char * pszExtension, bool bCreate);
      sp(::ca::tree_item) get_mime_type_tree_item(const char * pszMimeType, bool bCreate);


      virtual void get_extension_app(stringa & straAppId, const char * pszExtension);
      virtual void get_mime_type_app(stringa & straAppId, const char * pszMimeType);


      void write(::ca::byte_output_stream & ostream);
      void read(::ca::byte_input_stream & istream);


   };


} // namespace filehandler





