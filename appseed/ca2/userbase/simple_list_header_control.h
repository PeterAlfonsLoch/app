#pragma once


class CLASS_DECL_ca2 simple_list_header_control :
   virtual public ::user::list_header
{
public:


   static const int32_t         s_iDividerWidth;



   simple_list_header_control(::ca::application * papp);
   virtual ~simple_list_header_control();



   using ::user::list_header::create;
   virtual bool create(UINT nStyle, LPCRECT lpcrect, ::user::interaction * pwndParent, UINT nID);

   virtual void install_message_handling(::ca::message::dispatch * pinterface);



   DECL_GEN_SIGNAL(_001OnEndTrack)
   DECL_GEN_SIGNAL(_001OnTrack)
   DECL_GEN_SIGNAL(_001OnEndDrag)
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnMove);



};

