#include "framework.h"


namespace ca
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

   void system::discard_to_factory(sp(::ca::ca) pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

   sp(::ca::ca) system::clone(sp(::ca::ca) pca)
   {
      UNREFERENCED_PARAMETER(pca);
      return ::null();
   }





   sp(::ca::ca) system::on_alloc(sp(::ca::application) papp, sp(::ca::type_info) info)
   {
/*      if(info == System.type_info < class ::ca::log > ())
      {
         return new class ::ca::log(this); // ::null() log implementation
      }*/
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      on_allocation_error(papp, info);
      return ::null();
   }

   sp(::ca::ca) system::alloc(sp(::ca::application) papp, sp(::ca::type_info) info)
   {
      return on_alloc(papp, info);
   }

   sp(::ca::ca) system::alloc(sp(::ca::application) papp, const std_type_info & info)
   {
      return on_alloc(papp, canew(::ca::type_info(info)));
   }

   void system::on_allocation_error(sp(::ca::application) papp, sp(::ca::type_info) info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }



   void system::on_delete(sp(::ca::ca) pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

} // namespace ca



