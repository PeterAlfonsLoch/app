//
//  core_static_start
//



namespace core
{



   namespace static_start
   {


      CLASS_DECL_CORE void init()
      {


         #ifdef LINUX


            ::user::initialize_edesktop();


         #endif


      }














































      CLASS_DECL_CORE void term()
      {




      }



   } // namespace static_start


} // namespace base





