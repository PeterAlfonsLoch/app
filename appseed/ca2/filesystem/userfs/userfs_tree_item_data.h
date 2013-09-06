#pragma once


namespace userfs
{


   class CLASS_DECL_ca2 tree_item_data :
      virtual public ::ca2::tree_item_data,
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

      string get_text(sp(::ca2::tree) ptree);
      index get_image(sp(::ca2::tree) ptree);

      static index CompareArrangeByName(sp(::data::tree_item) & pitema, sp(::data::tree_item) & pitemb);
      int32_t get_index() const;
      bool is_folder() const;


   };


} // namespace userfs





