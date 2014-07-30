#pragma once


namespace usermail
{


   class CLASS_DECL_CORE item :
      virtual public ::data::item
   {
   public:
      
      
      tree *         m_ptree;
      string         m_strName;
      int32_t        m_iIdentation;
      account      * m_paccount;
      string         m_strFolder;


      item(tree * ptree);
      virtual ~item();

      string data_item_get_text(object * pobject) const;
      index data_item_get_image(object * pobject) const;
      image_list * data_item_get_image_list(object * pobject) const;



   };


} // namespace usermail