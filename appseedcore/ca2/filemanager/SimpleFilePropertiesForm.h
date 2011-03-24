#pragma once

namespace filemanager
{

   class CLASS_DECL_ca SimpleFilePropertiesForm :
         virtual public ::user::form_callback,
         virtual public ::user::create_view,
         virtual public ::user::tab_callback
   {
      public:


         ::userbase::single_document_template *  m_ptemplatePane;
         form_document *               m_pdocGeneral;
         form_view *                   m_pviewGeneral;
         ::userex::pane_tab_view *        m_ptabview;
         ::fs::item_array          m_itema;


         SimpleFilePropertiesForm(::ca::application * papp);
         virtual ~SimpleFilePropertiesForm();

#if !core_level_1
      using ::user::tab_callback::on_show_view;
#endif

         ::user::interaction * open(::user::interaction * puieParent, ::fs::item_array & itema);
         void on_show_view();
         void on_create_view(view_data * pviewdata);
         void page1();
         void page2();

         virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   };

} // namespace filemanager
