#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_properties_form :
         virtual public ::user::form_callback,
         virtual public ::user::view_creator,
         virtual public ::user::tab_callback
   {
   public:


      sp(::user::single_document_template)    m_ptemplatePane;
      sp(::form_document)                           m_pdocGeneral;
      sp(form_view)                               m_pviewGeneral;
      sp(::userex::pane_tab_view)                 m_ptabview;
      ::fs::item_array                          m_itema;


      file_properties_form(sp(::aura::application) papp);
      virtual ~file_properties_form();


      sp(::user::interaction) open(sp(::user::interaction) puieParent, ::fs::item_array & itema);

      void on_show_view();
      void on_create_view(::user::view_creator_data * pcreatordata);
      void page1();
      void page2();

      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   };


} // namespace filemanager




