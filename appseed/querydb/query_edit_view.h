#pragma once


namespace querydb
{


   class CLASS_DECL_CA2_QUERYDB query_edit_view :
      virtual public ::userbase::edit_plain_text_view
   {
   public:


      query_edit_view(::ca::application * papp);
      virtual ~query_edit_view();


      


      virtual void install_message_handling(user::win::message::dispatch * pinterface);


      document * get_document();

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


   };



} // namespace querydb



