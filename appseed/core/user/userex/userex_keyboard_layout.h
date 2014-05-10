#pragma once


namespace userex // ca8 + cube
{


   class CLASS_DECL_CORE keyboard_layout :
      virtual public ::user::split_view,
      virtual public ::user::form_callback,
      public ::user::list_data
   {
   public:



      sp(::form_document)               m_pdoc;
      sp(form_view)                   m_pview;
      sp(simple_list_view)            m_plistview;
      ::user::keyboard_layout_ida   m_layoutida;

      keyboard_layout(sp(::base::application) papp);
      virtual ~keyboard_layout();

      bool CreateViews();

      void on_show();

      bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

      virtual void _001GetItemText(::user::list_item * pitem);

      virtual int_ptr _001GetItemCount();


   private:


      keyboard_layout(const keyboard_layout & ) :
         ::user::place_holder_container(NULL),
         ::user::split_layout(NULL),
         ::user::split_view(NULL),
         ::user::list_data(NULL)
      {
      }


   };


} // namespace core // ca8 + cube



