#pragma once


namespace filehandler
{


   class CLASS_DECL_ca2 tree_item_data :
      public ::data::tree_item_data
   {
   public:


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



   };


} // namespace filehandler






