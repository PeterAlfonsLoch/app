#pragma once


namespace userfs
{

   class tree;

   class CLASS_DECL_CORE item:
      virtual public ::data::item,
      virtual public ::fs::item

   {
   public:


      ::userfs::tree *                       m_ptree;
      string                                 m_strName;
      int32_t                                m_iIdentation;
      string                                 m_strFolder;
      int32_t                                m_iImage;
      int32_t                                m_iIndex;
      int32_t                                m_iImageSelected;


      item(::userfs::tree * ptree);
      virtual ~item();

      string data_item_get_text(object * pobject) const;
      index data_item_get_image(object * pobject) const;
      image_list * data_item_get_image_list(object * pobject) const;

      static index CompareArrangeByName(sp(::data::tree_item) * pitema, sp(::data::tree_item) * pitemb);
      int32_t get_index() const;
      bool is_folder() const;


   };


} // namespace userfs





