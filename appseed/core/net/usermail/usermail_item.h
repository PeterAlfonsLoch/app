#pragma once


namespace usermail
{


   class CLASS_DECL_CORE item :
      public ::data::item
   {
   public:
      
      
      string         m_strName;
      int32_t        m_iIdentation;
      account      * m_paccount;
      string         m_strFolder;

      string data_item_get_text(object * pobject);
      index data_item_get_image(::user::interaction * pui);



   };


} // namespace usermail