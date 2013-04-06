#pragma once

namespace fs
{


   class CLASS_DECL_ca2 tree_item :
      virtual public ::ca::tree_item_data,
      virtual public ::fs::item

   {
   public:
      
      
      string                                 m_strName;
      int32_t                                m_iIdentation;
      string                                 m_strFolder;
      int32_t                                m_iImage;
      int32_t                                m_iIndex;
      int32_t                                m_iImageSelected;


      tree_item();

      string get_text(::ca::tree * ptree);
      index get_image(::ca::tree * ptree);

      static int32_t CompareArrangeByName(::ca::tree_item * pitema, ::ca::tree_item * pitemb, ::ca::tree_data * pdata);
      int32_t get_index() const;
      bool is_folder() const;


   };


} // namespace fs
