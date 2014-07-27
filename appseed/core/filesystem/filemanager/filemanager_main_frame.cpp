#include "framework.h"


namespace filemanager
{



   main_frame::main_frame(sp(::base::application) papp) :
      element(papp),
      simple_frame_window(papp)
   {
   }

   main_frame::~main_frame()
   {
   }



   void main_frame::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);


   }


   bool main_frame::on_create_bars()
   {
      
      sp(manager) pmanager = (GetActiveDocument());

      return pmanager->on_create_bars(this);

   }


} // namespace filemanager



