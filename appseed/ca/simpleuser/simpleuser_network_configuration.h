#pragma once


namespace simpleuser
{

   class CLASS_DECL_ca network_configuration :
      virtual public ::radix::object
//      public ::user::form_callback,
  //    public ::user::view_creator
   {
   public:


      /*form_document *               m_pdoc;
      form_view *                   m_pview;*/


      network_configuration(::ca::application * papp);
      virtual ~network_configuration();


      bool initialize(::user::interaction * puiParent);
      bool initialize_child(::user::interaction * puiParent);

      void on_show();

      //bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);

   };


} // namespace simpleuser


