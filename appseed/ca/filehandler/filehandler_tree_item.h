#pragma once


namespace filehandler
{


   class CLASS_DECL_ca tree_item :
      public gen::tree_item_data
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


      string get_text(gen::tree * ptree);
      index get_image(gen::tree * ptree);



   };


} // namespace filehandler






