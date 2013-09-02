#include "framework.h"


namespace ca2
{


   class ::id system::idEmpty;
   class ::id_space system::s_idspace;


   system::system()
   {

      idEmpty = "";

   }


   system::~system()
   {

   }



   bool system::assert_failed_line(const char * lpszFileName, int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const char * lpszFileName, int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return true;
   }

   void system::discard_to_factory(sp(element) pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

   sp(element) system::clone(sp(element) pca)
   {
      UNREFERENCED_PARAMETER(pca);
      return NULL;
   }





   sp(element) system::on_alloc(sp(::application) papp, sp(type) info)
   {
/*      if(info == System.type_info < class ::ca2::log > ())
      {
         return new class ::ca2::log(this); // NULL log implementation
      }*/
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      on_allocation_error(papp, info);
      return NULL;
   }

   sp(element) system::alloc(sp(::application) papp, sp(type) info)
   {
      return on_alloc(papp, info);
   }

   sp(element) system::alloc(sp(::application) papp, const std_type_info & info)
   {
      return on_alloc(papp, canew(type(info)));
   }

   void system::on_allocation_error(sp(::application) papp, sp(type) info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }




} // namespace ca2



