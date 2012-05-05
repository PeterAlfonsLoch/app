#pragma once


namespace filehandler
{


   class CLASS_DECL_ca handler :
      virtual public ::radix::object,
      virtual public ::ex1::byte_serializable
   {
   public:
      
      
      sp(tree_interface)         m_sptree;


      handler(::ca::application * papp);
      virtual ~handler();


      void defer_add_library(::ca2::library * plibrary);
      void add_library(library * plibrary);
      void add_menu_library(menu_library * plibrary);


      ::ex1::tree_item * get_extension_tree_item(const char * pszExtension, bool bCreate);
      ::ex1::tree_item * get_mime_type_tree_item(const char * pszMimeType, bool bCreate);


      virtual void get_extension_app(stringa & straAppId, const char * pszExtension);
      virtual void get_mime_type_app(stringa & straAppId, const char * pszMimeType);


      void write(::ex1::byte_output_stream & ostream);
      void read(::ex1::byte_input_stream & istream);


   };


} // namespace filehandler





