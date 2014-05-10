#pragma once


namespace user
{

   class CLASS_DECL_CORE network_configuration :
      virtual public ::object
//      public ::user::form_callback,
  //    public ::user::view_creator
   {
   public:


      /*sp(::form_document)               m_pdoc;
      sp(form_view)                   m_pview;*/


      network_configuration(sp(::base::application) papp);
      virtual ~network_configuration();


      bool initialize(sp(::user::interaction) puiParent);
      bool initialize_child(sp(::user::interaction) puiParent);

      void on_show();

      //bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   };


} // namespace user


