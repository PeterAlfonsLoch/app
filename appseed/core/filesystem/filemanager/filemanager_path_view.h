#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE path_view :
      virtual public ::user::edit_plain_text_view,
      virtual public  data_interface
   {
   public:

      bool m_bVoidSync;



       path_view(sp(base_application) papp);


      virtual void _001OnAfterChangeText(::action::context actioncontext);


      void _017Synchronize(::action::context actioncontext);
      void on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

   };




} // namespace filemanager




