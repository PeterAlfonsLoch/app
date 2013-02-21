#include "framework.h"

namespace gen
{

   system::system()
   {
   }

   system::~system()
   {
   }

} // namespace gen


#include "framework.h"



namespace radix
{

   class ::id system::idEmpty;
   class ::id_space system::s_idspace;

   system::system()
   {
   }

   system::~system()
   {
   }

   bool system::initialize()
   {
      idEmpty = "";
      return true;
   }


   ::ca::ca * system::on_alloc(::ca::application * papp, ::ca::type_info & info)
   {
/*      if(info == System.type_info < class ::ca::log > ())
      {
         return new class ::ca2::log(this); // NULL log implementation
      }*/
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      on_allocation_error(papp, info);
      return NULL;
   }

   ::ca::ca * system::alloc(::ca::application * papp, ::ca::type_info & info)
   {
      return on_alloc(papp, info);
   }

   ::ca::ca * system::alloc(::ca::application * papp, const std_type_info & info)
   {
      ::ca::type_info typeinfo(info);
      return on_alloc(papp, typeinfo);
   }

   void system::on_allocation_error(::ca::application * papp, ::ca::type_info & info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
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

   void system::on_delete(::ca::ca * pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

} // namespace radix
