#pragma once


namespace userbase
{

   
   class combo_box;


   class CLASS_DECL_ca2 combo_list : 
      virtual public ::user::combo_list
   {
   public:


      combo_list();
      virtual ~combo_list();


      virtual void install_message_handling(::gen::message::dispatch * pdispatch);


      virtual void _001OnDraw(::ca::graphics * pdc);



   };


} //  namespace user



