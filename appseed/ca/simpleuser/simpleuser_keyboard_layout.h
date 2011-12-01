#pragma once

namespace simpleuser
{

   class CLASS_DECL_ca keyboard_layout :
      virtual public ::userbase::split_view,
      virtual public ::user::form_callback,
      virtual public ::user::list_data
   {
   public:



      form_document *               m_pdoc;
      form_view *                   m_pview;
      simple_list_view *            m_plistview;
      ::user::keyboard_layout_ida   m_layoutida;

      keyboard_layout(::ca::application * papp);
      virtual ~keyboard_layout();

      bool CreateViews();

      void on_show();

      bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

      virtual void _001GetItemText(::user::list_item * pitem);

      virtual INT_PTR _001GetItemCount();

   };


} // namespace simpleuser