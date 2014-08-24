#include "framework.h"


namespace user
{

   
   namespace wndfrm
   {


      namespace frame
      {

         
         control_box_button::control_box_button(sp(::aura::application) papp) :
            element(papp),
            ::user::button(papp)
         {
            
         }
         
         
         control_box_button::~control_box_button()
         {
            
         }


         void control_box_button::UpdateWndRgn()
         {

         }
         
         void control_box_button::set_stock_icon(e_stock_icon eicon)
         {
            
            UNREFERENCED_PARAMETER(eicon);
            
         }
         
         
         e_stock_icon control_box_button::get_stock_icon()
         {
            
            return stock_icon_none;
            
         }
         
         
         


      } // namespace frame


   } // namespace wndfrm


} // namespace user


















