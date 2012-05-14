#include "framework.h"


namespace ca4
{


    ip_enum::ip_item::ip_item()
    {


    }


    ip_enum::ip_item::ip_item(int nAdapter, const in_addr & addr)
    {

       m_nAdapter    = nAdapter;
       m_addr        = addr;

    }


   ip_enum::ip_enum(::ca::application * papp) :
      ca(papp)
   {
   }


   ip_enum::~ip_enum()
   {
   }


   ::count ip_enum::enumerate(ip_array & ipa)
   {
      
      UNREFERENCED_PARAMETER(ipa);

      throw interface_only_exception();

      return 0;

   }

   ::count ip_enum::enumerate(stringa & stra)
   {
      
      UNREFERENCED_PARAMETER(stra);

      throw interface_only_exception();

      return 0;

   }


} // namespace ca4



