#pragma once

namespace fs
{


   class CLASS_DECL_ca2 tree_item :
      public gen::tree_item_data
   {
   public:
      
      
      string                           m_strName;
      int32_t                              m_iIdentation;
      string                           m_strFolder;
      string                           m_strPath;
      flags < e_flag >                 m_flags;
      int32_t                              m_iImage;
      int32_t                              m_iIndex;
      int32_t                              m_iImageSelected;


      tree_item();

      string get_text(gen::tree * ptree);
      index get_image(gen::tree * ptree);

      static int32_t CompareArrangeByName(gen::tree_item * pitema, ::gen::tree_item * pitemb, gen::tree_data * pdata);
      int32_t get_index() const;
      bool is_folder() const;


   };


} // namespace fs
