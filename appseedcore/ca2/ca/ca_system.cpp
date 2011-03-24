#include "StdAfx.h"



namespace ca
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


   ::ca::ca * system::on_alloc(::ca::application * papp, const ::ca::type_info & info)
   {
      if(info == typeid(class log))
      {
         return new class log(); // NULL log implementation
      }
      /*string str;
      str.Format("Could not alloc %s", info.raw_name());
      simple_message_box(str);*/
      on_allocation_error(papp, info);
      return NULL;
   }

   ::ca::ca * system::alloc(::ca::application * papp, const ::ca::type_info & info)
   {
      return on_alloc(papp, info);
   }

   ::ca::ca * system::alloc(::ca::application * papp, const std_type_info & info)
   {
      return on_alloc(papp, ::ca::type_info(info));
   }

   void system::on_allocation_error(::ca::application * papp, const ::ca::type_info & info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }


   bool system::assert_failed_line(const char * lpszFileName, int iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const char * lpszFileName, int iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return true;
   }

   void system::on_delete(::ca::ca * pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }

} // namespace ca