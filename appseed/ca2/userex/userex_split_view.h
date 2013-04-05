#pragma once


namespace userex
{


   class CLASS_DECL_ca2 split_view :
      virtual public ::userbase::split_view,
      virtual public ::user::view_creator
   {
   public:


      split_view(::ca::applicationsp papp);
      virtual ~split_view();

      virtual void on_new_view_creator_data(::user::view_creator_data * pcreatordata);

      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

      bool _001OnCommand(id id);

      bool create_pane(int32_t iPane, bool bFixedSize, ::id id);


   };


} // namespace userex




