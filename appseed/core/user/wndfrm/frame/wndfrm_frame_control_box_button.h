#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         class  CLASS_DECL_CORE control_box_button :
            virtual public ::user::button
         {
         public:


            control_box *     m_pcontrolbox;
            
            
            control_box_button(::aura::application * papp);
            virtual ~control_box_button();


            virtual void UpdateWndRgn();
            
            


         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user






