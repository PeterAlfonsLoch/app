#pragma once


namespace userfs
{


   class CLASS_DECL_CORE tree_item_data :
      virtual public ::data::tree_item_data,
      virtual public ::fs::item

   {
   public:
      
      
      string                                 m_strName;
      int32_t                                m_iIdentation;
      string                                 m_strFolder;
      int32_t                                m_iImage;
      int32_t                                m_iIndex;
      int32_t                                m_iImageSelected;


      tree_item_data();

      string get_text(sp(::data::tree) ptree);
      index get_image(sp(::data::tree) ptree);

      static index CompareArrangeByName(sp(::data::tree_item) & pitema, sp(::data::tree_item) & pitemb);
      int32_t get_index() const;
      bool is_folder() const;


   };


} // namespace userfs





