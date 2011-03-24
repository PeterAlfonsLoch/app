#pragma once

class CLASS_DECL_ca simple_list_header_control :
   virtual public ::user::interaction,
   virtual public ::user::list_header
{
public:
   simple_list_header_control(::ca::application * papp);

   static const int         s_iDividerWidth;

   virtual void OnDrawInterfaceDraw(::ca::graphics * pdc);
   virtual 
   bool create(UINT nStyle, LPCRECT lpcrect, ::user::interaction * pwndParent, UINT nID);
   
   virtual ~simple_list_header_control();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);



   DECL_GEN_SIGNAL(_001OnEndTrack)
   DECL_GEN_SIGNAL(_001OnTrack)
   DECL_GEN_SIGNAL(_001OnEndDrag)
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnMove);
   
};

