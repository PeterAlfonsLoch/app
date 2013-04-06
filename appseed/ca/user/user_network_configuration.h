#pragma once


namespace user
{

   class CLASS_DECL_ca network_configuration :
      virtual public ::ca::object
//      public ::user::form_callback,
  //    public ::user::view_creator
   {
   public:


      /*sp(::form_document)               m_pdoc;
      form_view *                   m_pview;*/


      network_configuration(sp(::ca::application) papp);
      virtual ~network_configuration();


      bool initialize(sp(::user::interaction) puiParent);
      bool initialize_child(sp(::user::interaction) puiParent);

      void on_show();

      //bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   };


} // namespace user


