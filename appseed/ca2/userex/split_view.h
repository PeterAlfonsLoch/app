#pragma once


namespace userex
{


   class CLASS_DECL_ca split_view :
      virtual public ::userbase::split_view,
      virtual public ::user::view_creator
   {
   public:


      split_view(::ax::application * papp);
      virtual ~split_view();


      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);

      virtual void OnDraw(::ax::graphics * pgraphics);


   };


} // namespace userex

