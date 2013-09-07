#pragma once


class CLASS_DECL_ca2 simple_printer_list_view :
   virtual public simple_list_view
{
public:

      
   ::user::simple_list_data   m_listdata;
   sp(::user::view)                   m_pview;


   simple_printer_list_view(sp(base_application) papp);
   virtual ~simple_printer_list_view();


   virtual void install_message_handling(::message::dispatch * pdispatch);

   virtual void _001OnClick(UINT nFlags, point point);

   DECL_GEN_SIGNAL(_001OnCreate)


};

