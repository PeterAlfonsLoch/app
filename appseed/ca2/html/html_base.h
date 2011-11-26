#pragma once


namespace html
{


   enum emessage
   {
      message_on_image_loaded = WM_USER + 200,
   };


   class tag;


   class base
   {
   public:


      class tag *             m_ptagParent;


      base(tag * pparent);
      virtual ~base();

      enum type
      {
         type_value,
         type_tag,
      };

      virtual type get_type() const = 0;


      class tag * parent();

      class tag * tag();

      class value * value();




   };


   class base_ptr_array : public base_array < base * , base * >
   {
   public:


   };


} // namespace html

