#pragma once


namespace userex
{


   class CLASS_DECL_CORE split_view :
      virtual public ::user::split_view,
      virtual public ::user::view_creator
   {
   public:


      split_view(sp(::axis::application) papp);
      virtual ~split_view();

      virtual void on_new_view_creator_data(::user::view_creator_data * pcreatordata);

      bool on_simple_update(cmd_ui * pcmdui);

      bool on_simple_action(id id);

      bool create_pane(int32_t iPane, bool bFixedSize, ::id id);


   };


} // namespace userex




