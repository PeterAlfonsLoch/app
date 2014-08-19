#pragma once


namespace user
{


   class view_creator_data;


   class CLASS_DECL_BASE view_container :
      virtual public ::object
   {
   public:


      view_container();
      virtual ~view_container();


      virtual id get_view_id();
      virtual sp(::user::interaction) get_view();
      virtual sp(::user::document) get_view_document();


      virtual void on_new_view_creator_data(view_creator_data * pcreatordata);


   };


} // namespace user


