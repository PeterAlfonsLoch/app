#pragma once


namespace user
{


   class CLASS_DECL_CA2_TESSERACT printer_list_view :
      virtual public simple_list_view
   {
   public:

      
      ::user::simple_list_data m_listdata;


      printer_list_view(::ca::application * papp);
      virtual ~printer_list_view();


      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);


      DECL_GEN_SIGNAL(_001OnCreate)


   };


} // namespace user