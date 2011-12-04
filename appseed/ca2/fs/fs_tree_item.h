#pragma once

namespace fs
{


   class CLASS_DECL_ca2 tree_item :
      public ex1::tree_item_data
   {
   public:
      
      
      string                           m_strName;
      int                              m_iIdentation;
      string                           m_strFolder;
      string                           m_strPath;
      flags < e_flag >                 m_flags;
      int                              m_iImage;
      int                              m_iIndex;
      int                              m_iImageSelected;


      tree_item();

      string get_text(ex1::tree * ptree);
      index get_image(ex1::tree * ptree);

      static int CompareArrangeByName(ex1::tree_item * pitema, ::ex1::tree_item * pitemb, void * pparam);
      int get_index() const;
      bool is_folder() const;


   };


} // namespace fs
