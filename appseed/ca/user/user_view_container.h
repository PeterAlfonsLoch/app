#pragma once


namespace user
{


   class view_creator_data;


   class CLASS_DECL_ca view_container :
      virtual public ::radix::object
   {
   public:


      view_container();
      virtual ~view_container();


      virtual id get_view_id();
      virtual ::user::interaction * get_view();
      virtual ::document * get_view_document();


      virtual void on_new_view_creator_data(view_creator_data * pcreatordata);


   };


} // namespace user


