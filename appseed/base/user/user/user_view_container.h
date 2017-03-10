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
      virtual ::user::interaction * get_view();
      virtual ::user::document * get_view_document();


      virtual bool on_prepare_view_creator_data(view_creator_data * pcreatordata);
      virtual bool on_after_create_view_creator_data(view_creator_data * pcreatordata);


   };


} // namespace user


