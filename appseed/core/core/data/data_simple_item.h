#pragma once


namespace data
{


   class CLASS_DECL_CORE simple_item :
      public item
   {
   public:


      index                      m_iImage;
      index                      m_iImageSelected;
      string                     m_str;


      simple_item();
      virtual ~simple_item();

      virtual string data_item_get_text(object * pobject);
      virtual index data_item_get_image(::user::interaction * pui);


   };


} // namespace core


