#pragma once


namespace usermail
{


   class CLASS_DECL_ca2 tree_item_data :
      public ::ca2::tree_item_data
   {
   public:
      
      
      string         m_strName;
      int32_t        m_iIdentation;
      account      * m_paccount;
      string         m_strFolder;

      string get_text(sp(::ca2::tree) ptree);
      index get_image(sp(::ca2::tree) ptree);



   };


} // namespace usermail