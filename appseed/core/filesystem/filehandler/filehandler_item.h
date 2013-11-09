#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE item :
      public ::data::item
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


      string data_item_get_text(object * pobject) const;
      index data_item_get_image(object * pobject) const;



   };


} // namespace filehandler






