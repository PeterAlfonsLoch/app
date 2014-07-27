#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class  CLASS_DECL_CORE control_box_button :
            virtual public ::user::interaction
         {
         public:


            control_box *     m_pcontrolbox;


            virtual void UpdateWndRgn();




         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user






