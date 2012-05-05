#pragma once


namespace filehandler
{


   class CLASS_DECL_ca tree_item :
      public ex1::tree_item_data
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


      string get_text(ex1::tree * ptree);
      index get_image(ex1::tree * ptree);



   };


} // namespace filehandler






