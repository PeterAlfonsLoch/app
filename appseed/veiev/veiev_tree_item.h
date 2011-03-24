#pragma once

namespace veiev
{


   class CLASS_DECL_CA2_VEIEV tree_item :
      public ex1::tree_item_data
   {
   public:
      
      
      string                     m_strName;
      int                        m_iIdentation;
      ::fontopus::user *    m_pprofile;
      string                     m_strFolder;

      string get_text(ex1::tree * ptree);
      index get_image(ex1::tree * ptree);



   };


} // namespace veiev