#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE handler :
      virtual public ::object,
      virtual public ::file::serializable
   {
   public:
      
      
      sp(tree_interface)         m_sptree;


      handler(sp(::aura::application) papp);
      virtual ~handler();


      enum e_topic_type
      {
         topic_type_root,
         topic_type_extension,
         topic_type_mime_type
      };


      e_topic_type   m_etopictype;
      string         m_strTopic;
      stringa        m_straHandlerLibrary;
      stringa        m_straMenuLibrary;
      stringa        m_straApp;


      string get_text(sp(::data::tree) ptree);
      index get_image(sp(::data::tree) ptree);


      void defer_add_library(::axis::library * plibrary);
      void add_library(::filehandler::library * plibrary);
      void add_menu_library(menu_library * plibrary);


      sp(::data::tree_item) get_extension_tree_item(const char * pszExtension, bool bCreate);
      sp(::data::tree_item) get_mime_type_tree_item(const char * pszMimeType, bool bCreate);


      virtual void get_extension_app(stringa & straAppId, const char * pszExtension);
      virtual void get_mime_type_app(stringa & straAppId, const char * pszMimeType);


      void write(::file::output_stream & ostream);
      void read(::file::input_stream & istream);


   };


} // namespace filehandler





