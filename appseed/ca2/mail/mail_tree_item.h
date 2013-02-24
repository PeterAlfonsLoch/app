#pragma once


namespace mail
{


   class CLASS_DECL_ca2 tree_item :
      public ::ca::tree_item_data
   {
   public:
      
      
      string         m_strName;
      int32_t        m_iIdentation;
      account      * m_paccount;
      string         m_strFolder;

      string get_text(::ca::tree * ptree);
      index get_image(::ca::tree * ptree);



   };


} // namespace mail