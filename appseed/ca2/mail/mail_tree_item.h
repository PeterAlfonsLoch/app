#pragma once


namespace mail
{


   class CLASS_DECL_ca2 tree_item :
      public ::gen::tree_item_data
   {
   public:
      
      
      string         m_strName;
      int32_t        m_iIdentation;
      account      * m_paccount;
      string         m_strFolder;

      string get_text(::gen::tree * ptree);
      index get_image(::gen::tree * ptree);



   };


} // namespace mail