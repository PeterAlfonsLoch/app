#pragma once

namespace mail
{


   class CLASS_DECL_ca tree_item :
      public ex1::tree_item_data
   {
   public:
      
      
      string      m_strName;
      int         m_iIdentation;
      account *   m_paccount;
      string      m_strFolder;

      string get_text(ex1::tree * ptree);
      index get_image(ex1::tree * ptree);



   };


} // namespace mail