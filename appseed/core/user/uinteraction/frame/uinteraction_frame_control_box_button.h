#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class  CLASS_DECL_CORE control_box_button :
            virtual public ::user::button
         {
         public:


            control_box *     m_pcontrolbox;
            
            
            control_box_button(sp(::aura::application) papp);
            virtual ~control_box_button();


            virtual void UpdateWndRgn();
            
            
            virtual void set_stock_icon(e_stock_icon eicon);
            virtual e_stock_icon get_stock_icon();


         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user






