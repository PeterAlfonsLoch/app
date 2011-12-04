#pragma once


namespace userex
{


   class CLASS_DECL_ca2 split_view :
      virtual public ::userbase::split_view,
      virtual public ::user::view_creator
   {
   public:


      split_view(::ca::application * papp);
      virtual ~split_view();


      bool _001OnUpdateCmdUi(cmd_ui * pcmdui);
      bool _001OnCommand(id id);

      virtual void OnDraw(::ca::graphics * pgraphics);


   };


} // namespace userex

