#pragma once


namespace filehandler
{


   class CLASS_DECL_ca2 tree_item_data :
      public ::ca::tree_item_data
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


      string get_text(sp(::ca::tree) ptree);
      index get_image(sp(::ca::tree) ptree);



   };


} // namespace filehandler






