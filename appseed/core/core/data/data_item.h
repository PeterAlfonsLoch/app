#pragma once


class image_list;


namespace data
{


   class item_data_array;
   class tree;


   class CLASS_DECL_CORE item :
      virtual public simple_data
   {
   public:


      item();
      virtual ~item();

      virtual string data_item_get_text(object * pobject);
      virtual index data_item_get_image(::user::interaction * pobject);
      virtual sp(image_list) data_item_get_image_list(::user::interaction * pui);

   };


   class CLASS_DECL_CORE item_array :
      public spa(item)
   {
   public:


   };


} // namespace core


